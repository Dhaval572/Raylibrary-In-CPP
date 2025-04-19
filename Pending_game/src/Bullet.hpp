#pragma once
#include <raylib.h>

class Bullet
{
public:

	Bullet(Vector2 bulletPos, int speed);
	void draw();
	void update();
	bool active;

private:

	Vector2 bulletPos;
	int speed;
};