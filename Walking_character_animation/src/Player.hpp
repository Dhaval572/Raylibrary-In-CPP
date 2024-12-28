#include <raylib.h>
#pragma once

class Player
{
public:

	Player();
	~Player();
	void update();
	void draw();
	void handleMovement();
	void updateAnimation();
	const Rectangle playerRect();
	void talkDamage(float damage);

private:

	Image resizeImage(const char *path, int width, int height);
	Texture2D loadTextureFromResizedImage(const char *path, int width, int height);

	// Functions
	void drawHealthBar();
	void updateHealthBar();

	// Player properties
	Vector2 position;
	float speed;
	float currentHealth;
	float maxHealth;
	Rectangle healthBar;
	bool isMoving;
	bool isMovingRight;
	int frame;
	float animationTime;
	Color healthColor;

	// Texture for player walking animation
	Texture2D walkRight1, walkRight2, walkLeft1, walkLeft2, background;
};
