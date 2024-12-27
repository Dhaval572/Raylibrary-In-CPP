#include <raylib.h>
#include "Player.hpp"

// Constructor
Player::Player(const char *walkRight1Path, const char *walkRight2Path,
			   const char *walkLeft1Path, const char *walkLeft2Path,
			   float x, float y, float speed)

	// constructor initializer list
	: position({x, y}),
	  speed(speed),
	  isMoving(false),
	  isMovingRight(true),
	  frame(0),
	  animationTime(0.0f)
{

	// Load textures for walking right and left
	walkRight1 = loadTextureFromResizedImage(walkRight1Path, 150, 150);
	walkRight2 = loadTextureFromResizedImage(walkRight2Path, 150, 150);
	walkLeft1 = loadTextureFromResizedImage(walkLeft1Path, 150, 150);
	walkLeft2 = loadTextureFromResizedImage(walkLeft2Path, 150, 150);

	// Load background texture (fixed size)
	background = loadTextureFromResizedImage("Images/background.png", 1200, 600);
}

// Destructor
Player::~Player()
{
	UnloadTexture(walkRight1);
	UnloadTexture(walkRight2);
	UnloadTexture(walkLeft1);
	UnloadTexture(walkLeft2);
	UnloadTexture(background);
}

// Function to handle movement
void Player::handleMovement()
{
	if (IsKeyDown(KEY_RIGHT))
	{
		position.x += speed; // Move right
		isMovingRight = true;
	}
	else if (IsKeyDown(KEY_LEFT))
	{
		position.x -= speed; // Move left
		isMovingRight = false;
	}

	// Movement limitation
	if (position.x > GetScreenWidth() - walkRight1.width)
		position.x = GetScreenWidth() - walkRight1.width;

	if (position.x < 0)
		position.x = 0;
}

// Function to update animation frame
void Player::updateAnimation()
{
	if (isMoving)
	{
		animationTime += GetFrameTime(); // GetFrameTime() returns time in seconds

		if (animationTime >= 0.7f)
		{						  // Delay between frames of 0.2 second
			frame = !frame;		  // Swapping frames in 0.2f second
			animationTime = 0.0f; // Reset the animTime
		}
	}
	else
	{
		frame = 0; // If character is not moving
	}
}

const Rectangle Player::playerRect() 
{
    return {position.x, position.y, (float)walkRight1.width, (float)walkRight1.height};
}


// Function to update player state (movement + animation)
void Player::update()
{
	isMoving = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT);
	handleMovement();
	updateAnimation();
}

// Function to load textures from resized images
Texture2D Player::loadTextureFromResizedImage(const char *path, int width, int height)
{
	Image resizedImage = resizeImage(path, width, height);
	Texture2D texture = LoadTextureFromImage(resizedImage);
	UnloadImage(resizedImage); // Free image memory after loading the texture
	return texture;
}

// Function to resize an image
Image Player::resizeImage(const char *path, int width, int height)
{
	Image img = LoadImage(path);
	ImageResize(&img, width, height);
	return img;
}

// Function to draw the player
void Player::draw()
{
	DrawTexture(background, 0, 0, WHITE); // Draw background

	// Draw walking animation based on movement direction
	if (isMoving)
	{
		if (isMovingRight)
			DrawTexture(frame == 0 ? walkRight1 : walkRight2, (int)position.x, (int)position.y, WHITE);
		else
			DrawTexture(frame == 0 ? walkLeft1 : walkLeft2, (int)position.x, (int)position.y, WHITE);
	}
	else
	{
		// Draw idle texture based on direction
		if (isMovingRight)
			DrawTexture(walkRight1, (int)position.x, (int)position.y, WHITE);
		else
			DrawTexture(walkLeft1, (int)position.x, (int)position.y, WHITE);
	}
}
