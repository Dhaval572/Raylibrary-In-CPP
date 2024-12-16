// Functionallites of lasers
#include "Laser.hpp"

Laser::Laser(Vector2 bulletPos, int speed)
{
	this->bulletPos = bulletPos;
	this->speed = speed;
	active = true;
}

void Laser::draw()
{
	if (active)
		DrawRectangle(bulletPos.x, bulletPos.y, 4, 15, GREEN); // Draw the bullet
}

void Laser::update()
{
	bulletPos.y += speed; // Move the bullet up
	if (active)
	{
		// Check if the position is off-screen vertically
		if (bulletPos.y > GetScreenHeight() - 100 || bulletPos.y < 25)
		{
			active = false;
		}
	}
}

Rectangle Laser::rect()
{
	Rectangle rect;
	rect.x = bulletPos.x;
	rect.y = bulletPos.y;
	rect.width = 4;
	rect.height = 15;
	return rect;
}
