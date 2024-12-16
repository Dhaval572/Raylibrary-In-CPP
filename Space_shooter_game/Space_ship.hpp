#include <raylib.h>
#include "Laser.hpp"
#include <vector>
#pragma once

class SpaceShip
{
public:
	SpaceShip();
	~SpaceShip();
	void draw();
	void moveLeft();
	void moveRight();
	void fireLaser();
	Rectangle getRect();
	void reset();
	std::vector<Laser> lasers;

private:
	Texture2D image;
	Vector2 shipPos; // Space ship bulletPos
	double lastFireTime;
	Sound laserSound;
};