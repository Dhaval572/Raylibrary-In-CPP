#include "SpaceShip.hpp"
#include "Obstacle.hpp"
#include "Enemy.hpp"
#include "MysteryShip.hpp"
#pragma once

class Game
{
public:

	explicit Game();
	~Game();
	void Draw();
	void Update();
	void HandleInput();
	bool run;
	int lives;
	int score;
	int high_score;
	Music music;

private:

	void DeleteInactiveLasers();
	std::vector<Obstacle> CreateObstacle();
	std::vector<Enemy> CreateEnemy();
	void MoveEnemies();
	void MoveDownEnemies(int distance);
	void EnemyShootLaser();
	void CheckForCollision();
	void GameOver();
	void Reset();
	void InitGame();
	void CheckForHighScore();
	void SaveHighScoreFile(int highScore);
	int LoadHighScoreFromFile();
	SpaceShip spaceship; // Making object
	std::vector<Obstacle> obstacles;
	std::vector<Enemy> enemies;
	int enemy_direction;
	std::vector<Laser> enemy_laser;
	constexpr static float enemy_laser_shoot_interval = 0.35;
	float time_last_enemy_fired;
	MysteryShip mystery_ship;
	float mystery_ship_spawn_interval;
	float time_last_spawn;
	Sound explosion_sound;
};