#include <raylib.h>
#include "Player.hpp"

// Constructor
Player::Player()

	// constructor initializer list
	: speed(2.0f),
	  isMoving(false),
	  isMovingRight(true),
	  frame(0),
	  animationTime(0.0f)
{
	position = {GetScreenWidth() / 2.0f, 325.0f};
	maxHealth = 100;
	currentHealth = 100;
	healthBar = {position.x / 2, position.y - 3, 150, 10};

	// Load textures for walking right and left
	walkRight1 = loadTextureFromResizedImage("Sprites/Player walking/monster_right_1.png", 150, 150);
	walkRight2 = loadTextureFromResizedImage("Sprites/Player walking/monster_right_2.png", 150, 150);
	walkLeft1 = loadTextureFromResizedImage("Sprites/Player walking/monster_Left_1.png", 150, 150);
	walkLeft2 = loadTextureFromResizedImage("Sprites/Player walking/monster_Left_2.png", 150, 150);

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

void Player::talkDamage(float damage)
{
	currentHealth -= damage;
	if (currentHealth < 0)
		currentHealth = 0; // Ensure health doesn't go below 0
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

void Player::drawHealthBar()
{
	updateHealthBar();

	DrawRectangleRec(healthBar, healthColor);
}

void Player::updateHealthBar()
{
	// Calculate the health percentage
	float healthPercentage = currentHealth / maxHealth;

	// Update the width of the health bar based on the health percentage
	healthBar.width = 100 * healthPercentage;

	// Change the color of the health bar based on the health percentage
	if (currentHealth <= maxHealth * 0.25f)
		healthColor = RED;
	else if (currentHealth <= maxHealth * 0.5f)
		healthColor = YELLOW;
	else
		healthColor = GREEN;

	// Set the healthbar mid point to player mid point
	healthBar.x = position.x + (walkRight1.width / 2) - (healthBar.width / 2);

	// Position the health bar just above the player
	healthBar.y = position.y - 20;
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

	drawHealthBar();
}
