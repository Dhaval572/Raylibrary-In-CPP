// Game handling methods
#include "Game.hpp"
#include <fstream>

Game::Game()
{
	music = LoadMusicStream("src/music.ogg");
	PlayMusicStream(music);
	explosionSound = LoadSound("src/explosion.ogg");
	initGame();
}

Game::~Game()
{
	Enemy::unloadimg(); // To deallocate memory
	UnloadMusicStream(music);
	UnloadSound(explosionSound);
}

void Game::draw()
{
	spaceship.draw();

	// Range based for loop for draw bullets
	for (auto &lasers : spaceship.lasers)
	{
		lasers.draw();
	}

	// Range based for loop for draw obstacles
	for (auto &obstacle : obstacles)
	{
		obstacle.draw();
	}

	// Range based for loop for draw enemies
	for (auto &enemy : enemies)
	{
		enemy.draw();
	}

	// Range based for loop for draw enemy's laser ( bullets )
	for (auto &laser : enemyLaser)
	{
		laser.draw();
	}

	mysteryShip.draw();
}

void Game::update()
{
	if (run)
	{
		double currentTime = GetTime();

		// Check if enough time has passed since the last mystery ship spawn
		if (currentTime - timeLastSpawn > mysteryShipSpawnInterval)
		{
			mysteryShip.spawn();
			timeLastSpawn = GetTime();						   // Updates the last spawn time
			mysteryShipSpawnInterval = GetRandomValue(10, 20); // Sets new random time for spawn mystery Ship
		}

		// Range based for loop for update each bullet
		for (auto &lasers : spaceship.lasers)
		{
			lasers.update();
		}

		moveEnemies();

		enemyShootLaser();

		// For update each laser
		for (auto &laser : enemyLaser)
		{
			laser.update();
		}

		deleteInactiveLasers(); // To deallocate memory for waste bullet

		mysteryShip.update();

		checkForCollision();
	}
	else
	{
		if (IsKeyPressed(KEY_R)) // If 'R' pressed
		{
			reset();
			initGame();
		}
	}
}

void Game::handleInput()
{
	if (run)
	{
		if (IsKeyDown(KEY_LEFT))
			spaceship.moveLeft(); // Move space ship left

		if (IsKeyDown(KEY_RIGHT))
			spaceship.moveRight(); // Move space ship left

		if (IsKeyDown(KEY_SPACE))
			spaceship.fireLaser(); // Fire the bullet
	}
}

// To Deallocate memory which was used in bullet
void Game::deleteInactiveLasers()
{
	// This for loop is checks all bullets one by one
	for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();)
	{
		// If current bullet is inactive then delete it for Deallocate memory
		if (!it->active)
		{
			it = spaceship.lasers.erase(it); // Deallocate the memory of inactive bullet
		}
		else
		{
			++it; // Check for next bullets
		}
	}

	// For enemy laser deallocation
	for (auto it = enemyLaser.begin(); it != enemyLaser.end();)
	{
		// If current bullet is inactive then delete it for Deallocate memory
		if (!it->active)
			it = enemyLaser.erase(it); // Deallocate the memory of inactive bullet
		else
			++it; // Check for next bullets
	}
}

std::vector<Obstacle> Game::createObstacle()
{
	int obstacleWidth = Obstacle::grid[0].size() * 3;
	float gap = (GetScreenWidth() - (4 * obstacleWidth)) / 5;

	for (int i = 0; i < 4; i++)
	{
		float offSetX = (i + 1) * gap + i * obstacleWidth;
		obstacles.push_back(Obstacle({offSetX, float(GetScreenWidth() - 200)}));
	}

	return obstacles;
}

std::vector<Enemy> Game::createEnemy()
{
	std::vector<Enemy> enemies;

	// For arrange enemies in his position
	for (int row = 0; row < 5; row++)
	{
		for (int column = 0; column < 11; column++)
		{
			int enemyType;

			if (row == 0)
				enemyType = 3;
			else if (row == 1 || row == 2)
				enemyType = 2;
			else
				enemyType = 1;

			float x = 75 + column * 55;
			float y = 110 + row * 55;
			enemies.push_back(Enemy(enemyType, {x, y})); // Spawn next enemies after killing
		}
	}

	return enemies;
}

void Game::moveEnemies()
{
	for (auto &enemy : enemies)
	{
		// If enemy gone off screen at right side or left side
		if (enemy.enemyPos.x + enemy.enemyImg[enemy.type - 1].width > GetScreenWidth() - 25)
		{
			enemyDirection = -1; // Now enemy will move oposite direction
			moveDownEnemies(1);
		}

		if (enemy.enemyPos.x < 25)
		{
			enemyDirection = 1; // Now enemy will move oposite direction
			moveDownEnemies(1);
		}

		enemy.update(enemyDirection);
	}
}

void Game::moveDownEnemies(int distance)
{
	// To move down side each enemy
	for (auto &enemy : enemies)
	{
		enemy.enemyPos.y += distance;
	}
}

void Game::enemyShootLaser()
{
	double currentTime = GetTime();
	if (currentTime - timeLastEnemyFired >= enemyLaserShootInterval && !enemies.empty())
	{
		int randomIndex = GetRandomValue(0, enemies.size() - 1);
		Enemy &enemy = enemies[randomIndex];

		// Add laser vector data structure
		enemyLaser.push_back(Laser({enemy.enemyPos.x + enemy.enemyImg[enemy.type - 1].width / 2, enemy.enemyPos.y + enemy.enemyImg[enemy.type - 1].height}, 6));

		timeLastEnemyFired = GetTime(); // Upating last fired time
	}
}

void Game::checkForCollision()
{
	// Collision check for ( our space ship ) Spaceship lasers
	for (auto &laser : spaceship.lasers)
	{
		// Checks collisions for every enemy space ships
		auto it = enemies.begin();
		while (it != enemies.end())
		{
			// Checks collision between enemy and our bullets
			if (CheckCollisionRecs(it->getRect(), laser.rect()))
			{

				PlaySound(explosionSound);

				// If you hit type 1 enemy
				if (it->type == 1)
					score += 100;

				if (it->type == 2)
					score += 200;

				if (it->type == 3)
					score += 300;

				checkForHighScore();
				it = enemies.erase(it); // Remove enemies which collided by bullet
				laser.active = false;
			}
			else
			{
				++it; // Check for other enemies
			}
		}

		// Checks collision for every obstacles ( by our )
		for (auto &obstacle : obstacles)
		{
			auto it = obstacle.blocks.begin();
			while (it != obstacle.blocks.end())
			{
				// Checks collision between blocks and our bullets
				if (CheckCollisionRecs(it->getRect(), laser.rect()))
				{
					it = obstacle.blocks.erase(it);
					laser.active = false;
				}
				else
				{
					++it; // Check for next block
				}
			}
		}

		// Checks collision between mystery ship and our bullets
		if (CheckCollisionRecs(mysteryShip.getRect(), laser.rect()))
		{
			mysteryShip.alive = false;
			laser.active = false;
			score += 500;
			checkForHighScore();
			PlaySound(explosionSound);
		}
	}

	// Collision for enemy bullets ( to our )
	for (auto &laser : enemyLaser)
	{
		// Checks collision between enemy bullets and our space ship
		if (CheckCollisionRecs(laser.rect(), spaceship.getRect()))
		{
			laser.active = false;
			lives--;
			if (lives == 0)
			{
				gameOver();
			}
		}
		// Checks collision for every obstacles ( by enemy )
		for (auto &obstacle : obstacles)
		{
			auto it = obstacle.blocks.begin();
			while (it != obstacle.blocks.end())
			{
				// Checks collision between blocks and enemy bullets
				if (CheckCollisionRecs(it->getRect(), laser.rect()))
				{
					it = obstacle.blocks.erase(it);
					laser.active = false;
				}
				else
				{
					++it; // Check for next block
				}
			}
		}
	}

	// Enemy collision with obstacle
	for (auto &enemy : enemies)
	{
		for (auto &obstacle : obstacles)
		{
			auto it = obstacle.blocks.begin();
			while (it != obstacle.blocks.end())
			{
				// Checks collision between blocks and enemy
				if (CheckCollisionRecs(it->getRect(), enemy.getRect()))
				{
					it = obstacle.blocks.erase(it);
				}
				else
				{
					it++; // Check for next enemy
				}
			}
		}

		// Checks collision between enemy and our
		if (CheckCollisionRecs(enemy.getRect(), spaceship.getRect()))
		{
			gameOver();
		}
	}
}

void Game::gameOver()
{
	run = false;
}

void Game::initGame()
{
	obstacles = createObstacle();
	enemies = createEnemy();
	enemyDirection = 1;
	timeLastEnemyFired = 0.0;
	timeLastSpawn = 0.0;
	lives = 3;
	run = true;
	score = 0;
	highScore = loadHighScoreFromFile();
	mysteryShipSpawnInterval = GetRandomValue(10, 20);
}

void Game::checkForHighScore()
{
	if (score > highScore)
	{
		highScore = score;
		saveHighScoreFile(highScore);
	}
}

// To save the high score in permenent storage
void Game::saveHighScoreFile(int highScore)
{
	std::ofstream highScoreFile("High_score.txt");
	if (highScoreFile.is_open())
	{
		highScoreFile << highScore;
		highScoreFile.close();
	}
}

int Game::loadHighScoreFromFile()
{
	int loadedHighScore = 0;
	std::ifstream highScoreFile("High_score.txt");
	if (highScoreFile.is_open())
	{
		highScoreFile >> loadedHighScore;
		highScoreFile.close(); // To deallocate memory
	}

	return loadedHighScore;
}

void Game::reset()
{
	spaceship.reset();
	enemies.clear();	// Remove all enemies
	enemyLaser.clear(); // Remove all lasers
	obstacles.clear();	// Remove all obstacles
}