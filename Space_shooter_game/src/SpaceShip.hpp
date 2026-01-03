#include "Laser.hpp"
#include <raylib.h>
#include <vector>
#pragma once

class SpaceShip
{
public:
	explicit SpaceShip();
	~SpaceShip();
	void Draw();
	void MoveLeft();
	void MoveRight();
	void FireLaser();
	void Reset();
	Rectangle GetRect();
	std::vector<Laser> lasers;

private:
	Texture2D image;
	Vector2 ship_pos; // Space ship bullet_pos
	double last_fire_time;
	Sound laser_sound;
};