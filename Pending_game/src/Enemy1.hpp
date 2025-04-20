#pragma once
#include <raylib.h>
#include "Player.hpp"

class Enemy1
{
private:
	Vector2 enemyPos;
	bool isMoving;
	float speed;
	float maxHealth;
	float currentHealth;
	Rectangle healthBar;
	int frame;
	float animationTime;

	// Use arrays instead of individual textures
	Texture2D walkFrames[8];
	Texture2D attackFrames[8];

	float spawnDelay;
	float elapsedTime;
	bool isActive;

public:
	Enemy1();
	~Enemy1();

	void draw();
	void update(Player &player);
	Image resizeTextureForWalk(const char *path, int width, int height);
	Texture2D loadTextureFromResizedImage(const char *path, int width, int height);
	void drawHealthBar();
	void handleMovement(Player &player);
	void handleAnimation();
	const Rectangle enemyRect();
	Texture2D getCurrentAnimationFrame();
};
