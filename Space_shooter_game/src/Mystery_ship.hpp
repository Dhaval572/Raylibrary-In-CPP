#include <raylib.h>
#pragma once

class MysteryShip
{
public:

	MysteryShip();
	~MysteryShip();
	void update();
	void draw();
	void spawn();
	Rectangle getRect();
	bool alive;

private:

	Vector2 mysteryShipPos;
	Texture2D mysteryShipImage;
	int speed;
};