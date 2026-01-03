// Functionallities of spaceships
#include "SpaceShip.hpp"
#include "Laser.hpp"

SpaceShip::SpaceShip()
{
	image = LoadTexture("src/pixel_ship.png"); // display space ship in window

	// Fix the ship position in center 
	ship_pos.x = (GetScreenWidth() - image.width) / 2; 
	ship_pos.y = (GetScreenHeight() - image.height - 100);
	last_fire_time =  0.0;
	laser_sound = LoadSound("src/laser.ogg");
}

// Deallocate the memories
SpaceShip::~SpaceShip()
{
	UnloadTexture(image); // Unload image for memory Deallocation
	UnloadSound(laser_sound); // Unload the sound for deallocate the memory   
}

void SpaceShip::Draw()
{
	DrawTextureV(image, ship_pos, WHITE); // Displaying textures
}

void SpaceShip::MoveLeft()
{
	// Prevent the ship from moving off the left side of the screen
	if(ship_pos.x < 25) ship_pos.x = 25;

	ship_pos.x -= 7; 
}

void SpaceShip::MoveRight()
{
	// Prevent the ship from moving off the right side of the screen
	if(ship_pos.x > GetScreenWidth() - image.width - 25)
	{
		ship_pos.x = GetScreenWidth() - image.width - 25;
	}

	ship_pos.x += 7;	
}

void SpaceShip::FireLaser()
{
	if(GetTime() - last_fire_time >= 0.35)
	{
		// Fix the position of bullet to middle of space ship
		lasers.emplace_back
		(
			Laser({ship_pos.x + image.width / 2 - 2, ship_pos.y}, -6)
		);
		last_fire_time = GetTime(); // To add delay between bullet fire
		PlaySound(laser_sound);
	}
}

// To check collision
Rectangle SpaceShip::GetRect()
{
	return 
	{
		ship_pos.x, 
		ship_pos.y, 
		static_cast<float>(image.width), 
		static_cast<float>(image.height)
	};
}

void SpaceShip::Reset()
{
	ship_pos.x = (GetScreenWidth() - image.width) / 2.0f;
	ship_pos.y = GetScreenHeight() - image.height - 100;
	lasers.clear();
}
