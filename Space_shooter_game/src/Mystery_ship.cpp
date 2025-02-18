#include "Mystery_ship.hpp"

MysteryShip::MysteryShip()
{
	mysteryShipImage = LoadTexture("src/pixel_ship3_green.png");
	alive = false;
}

MysteryShip::~MysteryShip()
{
	UnloadTexture(mysteryShipImage);
}

void MysteryShip::spawn()
{
	mysteryShipPos.y = 90;
	int side = GetRandomValue(0, 1);

	if(side == 0)
	{
		mysteryShipPos.x = 25; // Left side of screen
		speed = 3;
	}
	else
	{
		mysteryShipPos.x = GetScreenWidth() - mysteryShipImage.width - 25; // Right side of screen
		speed = -3;
	}
	alive = true;
}

Rectangle MysteryShip::getRect()
{
	// Make rectangle arround mystery ship to check collision
	if(alive)
	{
		return {mysteryShipPos.x, mysteryShipPos.y,
		float(mysteryShipImage.width), float(mysteryShipImage.height)};
	}
	else
	{
		return {mysteryShipPos.x, mysteryShipPos.y, 0, 0};
	}
}

void MysteryShip::update()
{
	if(alive)
	{
		mysteryShipPos.x += speed;

		// If mystery ship gone off the screen
		if(mysteryShipPos.x > GetScreenWidth() - mysteryShipImage.width -25
												|| mysteryShipPos.x < 25)
		{
			alive = false;
		}
	}
}

void MysteryShip::draw()
{
	if(alive)
	{
		DrawTextureV(mysteryShipImage, mysteryShipPos, WHITE);
	}
}