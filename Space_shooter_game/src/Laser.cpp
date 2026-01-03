// Functionallites of lasers
#include "Laser.hpp"

Laser::Laser(Vector2 bullet_pos, int speed) 
	: bullet_pos(bullet_pos)
	, speed(speed)
	, active(true) {}

void Laser::Draw()
{
	if (active)
	{
		DrawRectangle(bullet_pos.x, bullet_pos.y, 4, 15, GREEN);
	}
}

void Laser::Update()
{
	bullet_pos.y += speed; // Move the bullet up
	if (active)
	{
		// Check if the position is off-screen vertically
		if (bullet_pos.y > GetScreenHeight() - 100 || bullet_pos.y < 25)
		{
			active = false;
		}
	}
}

Rectangle Laser::Rect()
{
	Rectangle rect;
	rect.x = bullet_pos.x;
	rect.y = bullet_pos.y;
	rect.width = 4;
	rect.height = 15;
	return rect;
}
