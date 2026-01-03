#include <raylib.h>
#pragma once

class Laser
{
	Vector2 bullet_pos;
	int speed;

public:

	explicit Laser(Vector2 bullet_pos, int speed);
	void Draw();
	void Update();
	Rectangle Rect();
	bool active;
};