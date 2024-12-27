#pragma once 
#include <raylib.h>

class Enemy1
{
public:

	Enemy1();
	~Enemy1();
	void draw();
	void update();
	void handleMovement();
	void handleAnimation();

private:

	Image resizeImage(const char *path, int width, int height);
	Texture2D loadTextureFromResizedImage(const char *path, int width, int height);
	Vector2 position;
	bool isMoving;
	float speed;
	int frame;
	float animationTime;
	Texture2D walk1, walk2, walk3, walk4, walk5, walk6;
	void Attack();
};
