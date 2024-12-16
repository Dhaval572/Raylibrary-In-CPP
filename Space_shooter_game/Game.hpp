#include "Space_ship.hpp"
#include "Obstacle.hpp"
#include "Enemy.hpp"
#include "Mystery_ship.hpp"
#pragma once

class Game
{
public:

	Game();
	~Game();
	void draw();
	void update();
	void handleInput();
	bool run;
	int lives;
	int score;
	int highScore;
	Music music;

private:

	void deleteInactiveLasers();
	std::vector<Obstacle> createObstacle();
	std::vector<Enemy> createEnemy();
	void moveEnemies();
	void moveDownEnemies(int distance);
	void enemyShootLaser();
	void checkForCollision();
	void gameOver();
	void reset();
	void initGame();
	void checkForHighScore();
	void saveHighScoreFile(int highScore);
	int loadHighScoreFromFile();
	SpaceShip spaceship; // Making object
	std::vector<Obstacle> obstacles;
	std::vector<Enemy> enemies;
	int enemyDirection;
	std::vector<Laser> enemyLaser;
	constexpr static float enemyLaserShootInterval = 0.35;
	float timeLastEnemyFired;
	MysteryShip mysteryShip;
	float mysteryShipSpawnInterval;
	float timeLastSpawn;
	Sound explosionSound;
};