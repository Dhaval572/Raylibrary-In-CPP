#include <raylib.h>
#pragma once

class Laser
{
	Vector2 bulletPos;
	int speed;

public:

	Laser(Vector2 bulletPos, int speed);
	void draw();
	void update();
	Rectangle rect();
	bool active;
};