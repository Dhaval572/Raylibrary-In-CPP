#include "MysteryShip.hpp"

MysteryShip::MysteryShip()
{
	mystery_ship_image = LoadTexture("src/pixel_ship3_green.png");
	alive = false;
}

MysteryShip::~MysteryShip()
{
	UnloadTexture(mystery_ship_image);
}

void MysteryShip::Spawn()
{
	mystery_ship_pos.y = 90;
	int side = GetRandomValue(0, 1);

	if(side == 0)
	{
		mystery_ship_pos.x = 25; // Left side of screen
		speed = 3;
	}
	else
	{
		mystery_ship_pos.x = GetScreenWidth() - mystery_ship_image.width - 25; // Right side of screen
		speed = -3;
	}
	alive = true;
}

Rectangle MysteryShip::GetRect() const
{
	// Make rectangle arround mystery ship to check collision
	if(alive)
	{
		return 
		{
			mystery_ship_pos.x,
			mystery_ship_pos.y,
			static_cast<float>(mystery_ship_image.width), 
			static_cast<float>(mystery_ship_image.height)
		};
	}
	else
	{
		return {mystery_ship_pos.x, mystery_ship_pos.y, 0, 0};
	}
}

void MysteryShip::Update()
{
	if(alive)
	{
		mystery_ship_pos.x += speed;

		// If mystery ship gone off the screen
		if(mystery_ship_pos.x > GetScreenWidth() - mystery_ship_image.width -25
												|| mystery_ship_pos.x < 25)
		{
			alive = false;
		}
	}
}

void MysteryShip::Draw()
{
	if(alive)
	{
		DrawTextureV(mystery_ship_image, mystery_ship_pos, WHITE);
	}
}