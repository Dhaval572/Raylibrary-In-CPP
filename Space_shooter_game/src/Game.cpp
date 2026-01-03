// Game handling methods
#include "Game.hpp"
#include <fstream>

Game::Game()
{
	music = LoadMusicStream("src/music.ogg");
	PlayMusicStream(music);
	explosion_sound = LoadSound("src/explosion.ogg");
	InitGame();
}

Game::~Game()
{
	Enemy::Unloadimg(); // To deallocate memory
	UnloadMusicStream(music);
	UnloadSound(explosion_sound);
}

void Game::Draw()
{
	spaceship.Draw();

	// Range based for loop for Draw bullets
	for (Laser &lasers : spaceship.lasers)
	{
		lasers.Draw();
	}

	// Range based for loop for Draw obstacles
	for (Obstacle &obstacle : obstacles)
	{
		obstacle.Draw();
	}

	// Range based for loop for Draw enemies
	for (Enemy &enemy : enemies)
	{
		enemy.Draw();
	}

	// Range based for loop for Draw enemy's laser ( bullets )
	for (Laser &laser : enemy_laser)
	{
		laser.Draw();
	}

	mystery_ship.Draw();
}

void Game::Update()
{
	if (run)
	{
		double curr_time = GetTime();

		// Check if enough time has passed since the last mystery ship spawn
		if (curr_time - time_last_spawn > mystery_ship_spawn_interval)
		{
			mystery_ship.Spawn();
			time_last_spawn = GetTime();						   // Updates the last spawn time
			mystery_ship_spawn_interval = GetRandomValue(10, 20); // Sets new random time for spawn mystery Ship
		}

		// Range based for loop for update each bullet
		for (Laser &lasers : spaceship.lasers)
		{
			lasers.Update();
		}

		MoveEnemies();

		EnemyShootLaser();

		// For update each laser
		for (Laser &laser : enemy_laser)
		{
			laser.Update();
		}

		DeleteInactiveLasers(); // To deallocate memory for waste bullet

		mystery_ship.Update();

		CheckForCollision();
	}
	else
	{
		DrawText("Press R to Restart", 100, 97, 50, GREEN);
		if (IsKeyPressed(KEY_R)) // If 'R' pressed
		{
			Reset();
			InitGame();
		}
	}
}

void Game::HandleInput()
{
	if (run)
	{
		if (IsKeyDown(KEY_LEFT))
			spaceship.MoveLeft(); // Move space ship left

		if (IsKeyDown(KEY_RIGHT))
			spaceship.MoveRight(); // Move space ship left

		if (IsKeyDown(KEY_SPACE))
			spaceship.FireLaser(); // Fire the bullet
	}
}

// To Deallocate memory which was used in bullet
void Game::DeleteInactiveLasers()
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
	for (auto it = enemy_laser.begin(); it != enemy_laser.end();)
	{
		// If current bullet is inactive then delete it for Deallocate memory
		if (!it->active)
			it = enemy_laser.erase(it); // Deallocate the memory of inactive bullet
		else
			++it; // Check for next bullets
	}
}

std::vector<Obstacle> Game::CreateObstacle()
{
	int obstacle_w = Obstacle::grid[0].size() * 3;
	float gap = (GetScreenWidth() - (4 * obstacle_w)) / 5;

	for (int i = 0; i < 4; i++)
	{
		float offset_x = (i + 1) * gap + i * obstacle_w;
		obstacles.emplace_back
		(
			Obstacle({offset_x, float(GetScreenWidth() - 200)})
		);
	}

	return obstacles;
}

std::vector<Enemy> Game::CreateEnemy()
{
	std::vector<Enemy> enemies;
	enemies.reserve(60);

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
			enemies.emplace_back(Enemy(enemyType, {x, y}));
		}
	}

	return enemies;
}

void Game::MoveEnemies()
{
	for (Enemy &enemy : enemies)
	{
		// If enemy gone off screen at right side or left side
		if 
		(
			enemy.enemy_pos.x + 
			enemy.enemy_img[enemy.type - 1].width > GetScreenWidth() - 25
		)
		{
			enemy_direction = -1; // Now enemy will move oposite direction
			MoveDownEnemies(1);
		}

		if (enemy.enemy_pos.x < 25)
		{
			enemy_direction = 1; // Now enemy will move oposite direction
			MoveDownEnemies(1);
		}

		enemy.Update(enemy_direction);
	}
}

void Game::MoveDownEnemies(int distance)
{
	// To move down side each enemy
	for (Enemy &enemy : enemies)
	{
		enemy.enemy_pos.y += distance;
	}
}

void Game::EnemyShootLaser()
{
	double curr_time = GetTime();
	if 
	(
		curr_time - time_last_enemy_fired >= enemy_laser_shoot_interval 
		&& !enemies.empty()
	)
	{
		int randomIndex = GetRandomValue(0, enemies.size() - 1);
		Enemy &enemy = enemies[randomIndex];

		// Add laser vector data structure
		enemy_laser.emplace_back
		(
			Laser
			(
				{enemy.enemy_pos.x + enemy.enemy_img[enemy.type - 1].width / 2, enemy.enemy_pos.y + enemy.enemy_img[enemy.type - 1].height}, 6
			)
		);

		time_last_enemy_fired = GetTime(); // Upating last fired time
	}
}

void Game::CheckForCollision()
{
	// Collision check for ( our space ship ) Spaceship lasers
	for (Laser &laser : spaceship.lasers)
	{
		// Checks collisions for every enemy space ships
		auto it = enemies.begin();
		while (it != enemies.end())
		{
			// Checks collision between enemy and our bullets
			if (CheckCollisionRecs(it->GetRect(), laser.Rect()))
			{

				PlaySound(explosion_sound);

				// If you hit type 1 enemy
				if (it->type == 1)
					score += 100;

				if (it->type == 2)
					score += 200;

				if (it->type == 3)
					score += 300;

				CheckForHighScore();
				it = enemies.erase(it); // Remove enemies which collided by bullet
				laser.active = false;
			}
			else
			{
				++it; // Check for other enemies
			}
		}

		// Checks collision for every obstacles ( by our )
		for (Obstacle &obstacle : obstacles)
		{
			auto it = obstacle.blocks.begin();
			while (it != obstacle.blocks.end())
			{
				// Checks collision between blocks and our bullets
				if (CheckCollisionRecs(it->GetRect(), laser.Rect()))
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
		if (CheckCollisionRecs(mystery_ship.GetRect(), laser.Rect()))
		{
			mystery_ship.alive = false;
			laser.active = false;
			score += 500;
			CheckForHighScore();
			PlaySound(explosion_sound);
		}
	}

	// Collision for enemy bullets ( to our )
	for (Laser &laser : enemy_laser)
	{
		// Checks collision between enemy bullets and our space ship
		if (CheckCollisionRecs(laser.Rect(), spaceship.GetRect()))
		{
			laser.active = false;
			lives--;
			if (lives == 0)
			{
				GameOver();
			}
		}
		// Checks collision for every obstacles ( by enemy )
		for (Obstacle &obstacle : obstacles)
		{
			auto it = obstacle.blocks.begin();
			while (it != obstacle.blocks.end())
			{
				// Checks collision between blocks and enemy bullets
				if (CheckCollisionRecs(it->GetRect(), laser.Rect()))
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
	for (Enemy &enemy : enemies)
	{
		for (Obstacle &obstacle : obstacles)
		{
			auto it = obstacle.blocks.begin();
			while (it != obstacle.blocks.end())
			{
				// Checks collision between blocks and enemy
				if (CheckCollisionRecs(it->GetRect(), enemy.GetRect()))
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
		if (CheckCollisionRecs(enemy.GetRect(), spaceship.GetRect()))
		{
			GameOver();
		}
	}
}

void Game::GameOver()
{
	run = false;
}

void Game::InitGame()
{
	obstacles = CreateObstacle();
	enemies = CreateEnemy();
	enemy_direction = 1;
	time_last_enemy_fired = 0.0;
	time_last_spawn = 0.0;
	lives = 3;
	run = true;
	score = 0;
	high_score = LoadHighScoreFromFile();
	mystery_ship_spawn_interval = GetRandomValue(10, 20);
}

void Game::CheckForHighScore()
{
	if (score > high_score)
	{
		high_score = score;
		SaveHighScoreFile(high_score);
	}
}

// To save the high score in permenent storage
void Game::SaveHighScoreFile(int highScore)
{
	std::ofstream high_score_file("High_score.txt");
	if (high_score_file.is_open())
	{
		high_score_file << highScore;
		high_score_file.close();
	}
}

int Game::LoadHighScoreFromFile()
{
	int loaded_high_score = 0;
	std::ifstream high_score_file("High_score.txt");
	if (high_score_file.is_open())
	{
		high_score_file >> loaded_high_score;
		high_score_file.close(); 
	}

	return loaded_high_score;
}

void Game::Reset()
{
	spaceship.Reset();
	enemies.clear();	
	enemy_laser.clear(); 
	obstacles.clear();	
}
