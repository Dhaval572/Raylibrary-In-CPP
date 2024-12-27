#include <raylib.h>
#include "Player.hpp"
#include "Enemy1.hpp"

Enemy1::Enemy1()
{
	// Initialize enemy properties
	position = {0.0f, 400.0f};
	isMoving = false;
	speed = 2.0f;
	frame = 0;
	animationTime = 0.0f;

	// Load texture
	walk1 = loadTextureFromResizedImage("Sprites/Enemy walking/Sprite1.png", 75, 74); 
	walk2 = loadTextureFromResizedImage("Sprites/Enemy walking/Sprite2.png", 75, 74); 
	walk3 = loadTextureFromResizedImage("Sprites/Enemy walking/Sprite3.png", 75, 74); 
	walk4 = loadTextureFromResizedImage("Sprites/Enemy walking/Sprite4.png", 75, 74); 
	walk5 = loadTextureFromResizedImage("Sprites/Enemy walking/Sprite5.png", 75, 74); 
	walk6 = loadTextureFromResizedImage("Sprites/Enemy walking/Sprite6.png", 75, 74); 
}

Enemy1::~Enemy1()
{
	// Unload texture
	UnloadTexture(walk1);
}

void Enemy1::draw()
{
	// Make sprite
	Texture2D currentFrame;
	switch (frame) {
		case 0: currentFrame = walk1; break;
		case 1: currentFrame = walk2; break;
		case 2: currentFrame = walk3; break;
		case 3: currentFrame = walk4; break;
		case 4: currentFrame = walk5; break;
		case 5: currentFrame = walk6; break;
		default: currentFrame = walk1; break; // Fallback to walkRight1 if frame is out of range
	}

	DrawTexture(currentFrame, (int)position.x, (int)position.y, WHITE);
}

void Enemy1::update()
{
	isMoving = true;
	handleMovement();
	handleAnimation();
}

Image Enemy1::resizeImage(const char *path, int width, int height)
{
	Image img = LoadImage(path);
	ImageResize(&img, width, height);
	return img;
}

Texture2D Enemy1::loadTextureFromResizedImage(const char *path, int width, int height)
{
	Image image = resizeImage(path, width, height);
	Texture2D texture = LoadTextureFromImage(image);
	UnloadImage(image);
	return texture;
}

void Enemy1::handleMovement()
{

	position.x += speed; // Move right
	isMoving = true;

	if(position.x > GetScreenWidth() + walk1.width)
		position.x = 0;

}

void Enemy1::handleAnimation()
{
	if (isMoving)
	{
		animationTime += GetFrameTime(); // GetFrameTime() returns time in seconds

		if (animationTime >= 0.2f)
		{						  // Delay between frames of 0.2 second
			frame = (frame + 1) % 6;		  // Swapping frames in 0.2f second
			animationTime = 0.0f; // Reset the animTime
		}
	}
	else
	{
		frame = 0; // If character is not moving
	}
}
