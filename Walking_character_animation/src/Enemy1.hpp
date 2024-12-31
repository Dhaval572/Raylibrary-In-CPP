
#pragma once
#include <raylib.h>

class Enemy1
{
public:

	Enemy1();
	~Enemy1();
	Vector2 enemyPos;
	void draw();
	void update(Player &player);
	void handleMovement(Player &player);
	void handleAnimation();
	const Rectangle enemyRect();

private:
	Image resizeTextureForWalk(const char *path, int width, int height);
	Image resizeTextureForAttack(const char *path, int width, int height);
	Texture2D loadTextureFromResizedImage(const char *path, int width, int height);
	bool isMoving;
	float speed;
	float currentHealth;
	float maxHealth;
	Rectangle healthBar; 
	int frame;
	float animationTime;
	Texture2D walk1, walk2, walk3, walk4, walk5, walk6;
	Texture2D attack1, attack2, attack3, attack4;
	void drawHealthBar();
	void updateHealthBar();

};
