// Functionallities of spaceships
#include "Space_ship.hpp"
#include "Laser.hpp"

SpaceShip::SpaceShip()
{
	image = LoadTexture("src/pixel_ship.png"); // display space ship in window

	// Fix the ship position in center 
	shipPos.x = (GetScreenWidth() - image.width) / 2; 
	shipPos.y = (GetScreenHeight() - image.height - 100);
	lastFireTime =  0.0;
	laserSound = LoadSound("src/laser.ogg");
}

// Deallocate the memories
SpaceShip::~SpaceShip()
{
	UnloadTexture(image); // Unload image for memory Deallocation
	UnloadSound(laserSound); // Unload the sound for deallocate the memory   
}

void SpaceShip::draw()
{
	DrawTextureV(image, shipPos, WHITE); // Displaying textures
}

void SpaceShip::moveLeft()
{
	// Prevent the ship from moving off the left side of the screen
	if(shipPos.x < 25)
		shipPos.x = 25;

	shipPos.x -= 7; 
}

void SpaceShip::moveRight()
{
	// Prevent the ship from moving off the right side of the screen
	if(shipPos.x > GetScreenWidth() - image.width - 25)
		shipPos.x = GetScreenWidth() - image.width - 25;

	shipPos.x += 7;	
}

void SpaceShip::fireLaser()
{
	if(GetTime() - lastFireTime >= 0.35)
	{
		// Fix the position of bullet to middle of space ship
		lasers.push_back(Laser({shipPos.x + image.width / 2 - 2, shipPos.y}, -6));
		lastFireTime = GetTime(); // To add delay between bullet fire
		PlaySound(laserSound);
	}
}

// To check collision
Rectangle SpaceShip::getRect()
{
	return {shipPos.x, shipPos.y, float(image.width), float(image.height)};
}

void SpaceShip::reset()
{
	shipPos.x = (GetScreenWidth() - image.width) / 2.0f;
	shipPos.y = GetScreenHeight() - image.height - 100;
	lasers.clear();
}
