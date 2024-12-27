#include <raylib.h>
#pragma once

class Player
{
public:

	Player(const char *walkRight1Path, const char *walkRight2Path,
		   const char *walkLeft1Path, const char *walkLeft2Path,
		   float x, float y, float speed);
	~Player();
	void update();
	void draw();
	void handleMovement();
	void updateAnimation();

private:
	Image resizeImage(const char *path, int width, int height);
	Texture2D loadTextureFromResizedImage(const char *path, int width, int height);
	Vector2 position;
	float speed;
	bool isMoving;
	bool isMovingRight;
	int frame;
	float animationTime;
	Texture2D walkRight1, walkRight2, walkLeft1, walkLeft2, background;
};
