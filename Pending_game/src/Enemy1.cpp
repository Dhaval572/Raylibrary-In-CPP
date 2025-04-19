#include <raylib.h>
#include "Player.hpp"
#include "Enemy1.hpp"

Enemy1::Enemy1()
{
	// Initialize enemy properties
	enemyPos = {0.0f, 380.0f};
	isMoving = false;
	speed = 1.0f;
	maxHealth = 100;
	currentHealth = maxHealth;
	healthBar = {enemyPos.x, enemyPos.y - 30, 50, 5};
	frame = 0;
	animationTime = 0.0f;

	// Load walking textures
	walk1 = loadTextureFromResizedImage("Sprites/Enemy walking/Sprite1.png", 100, 100);
	walk2 = loadTextureFromResizedImage("Sprites/Enemy walking/Sprite2.png", 100, 100);
	walk3 = loadTextureFromResizedImage("Sprites/Enemy walking/Sprite3.png", 100, 100);
	walk4 = loadTextureFromResizedImage("Sprites/Enemy walking/Sprite4.png", 100, 100);
	walk5 = loadTextureFromResizedImage("Sprites/Enemy walking/Sprite5.png", 100, 100);
	walk6 = loadTextureFromResizedImage("Sprites/Enemy walking/Sprite6.png", 100, 100);

	// Load attacking textures
	attack1 = loadTextureFromResizedImage("Sprites/Enemy Attack/Sprite1.png", 100, 100);
	attack2 = loadTextureFromResizedImage("Sprites/Enemy Attack/Sprite2.png", 100, 100);
	attack3 = loadTextureFromResizedImage("Sprites/Enemy Attack/Sprite3.png", 100, 100);
	attack4 = loadTextureFromResizedImage("Sprites/Enemy Attack/Sprite4.png", 100, 100);
}

Enemy1::~Enemy1()
{
	// Unload textures
	UnloadTexture(walk1);
	UnloadTexture(walk2);
	UnloadTexture(walk3);
	UnloadTexture(walk4);
	UnloadTexture(walk5);
	UnloadTexture(walk6);

	UnloadTexture(attack1);
	UnloadTexture(attack2);
	UnloadTexture(attack3);
	UnloadTexture(attack4);
}

void Enemy1::draw()
{
	// Choose the current frame based on whether the enemy is moving or attacking
	Texture2D currentFrame;

	if (isMoving)
	{
		switch (frame)
		{
		case 0:
			currentFrame = walk1;
			break;
		case 1:
			currentFrame = walk2;
			break;
		case 2:
			currentFrame = walk3;
			break;
		case 3:
			currentFrame = walk4;
			break;
		case 4:
			currentFrame = walk5;
			break;
		case 5:
			currentFrame = walk6;
			break;
		default:
			currentFrame = walk1;
			break;
		}
	}
	else
	{
		switch (frame)
		{
		case 0:
			currentFrame = attack1;
			break;
		case 1:
			currentFrame = attack2;
			break;
		case 2:
			currentFrame = attack3;
			break;
		case 3:
			currentFrame = attack4;
			break;
		default:
			currentFrame = attack1;
			break;
		}
	}

	// Draw the current frame
	DrawTexture(currentFrame, (int)enemyPos.x, (int)enemyPos.y, WHITE);
	drawHealthBar();
}

void Enemy1::update(Player &player)
{
	// Handle movement logic based on collision with player and screen boundaries
	handleMovement(player);
	// Handle animation logic
	handleAnimation();
}

Image Enemy1::resizeTextureForWalk(const char *path, int width, int height)
{
	Image img = LoadImage(path);
	ImageResize(&img, width, height); // Resize the image
	return img;						  // Return the resized image
}

Texture2D Enemy1::loadTextureFromResizedImage(const char *path, int width, int height)
{
	// Resize the image to the desired dimensions
	Image resizedImage = resizeTextureForWalk(path, width, height);

	// Convert the resized image to a texture
	Texture2D texture = LoadTextureFromImage(resizedImage);

	// Unload the temporary image as we no longer need it
	UnloadImage(resizedImage);

	return texture; // Return the created texture
}

void Enemy1::drawHealthBar()
{
	healthBar.x = enemyPos.x + (walk1.width / 2) - (healthBar.width / 2);
    healthBar.y = enemyPos.y - 10;
	DrawRectangleRec(healthBar, RED);  
}

void Enemy1::updateHealthBar()
{
	float healthPercentage = currentHealth / maxHealth;

	healthBar.width = 200 * healthPercentage; // 200 is maximum width of  health bar
}

void Enemy1::handleMovement(Player &player)
{
	// Define the enemy's hitbox
	Rectangle enemyRect = {enemyPos.x, enemyPos.y, (float)walk1.width, (float)walk1.height};
	Rectangle playerRect = player.playerRect(); // Assuming playerRect() gives the bounding box of the player

	// Check for collision with player
	if (CheckCollisionRecs(enemyRect, playerRect))
	{
		isMoving = false; // Stop moving if colliding with the player
	}
	else if (enemyPos.x < playerRect.x)
	{
		isMoving = true;	 // Continue moving towards the player
		enemyPos.x += speed; // Move right
	}

	// Wrap around screen if it goes off the right edge
	if (enemyPos.x > GetScreenWidth() + walk1.width)
	{
		enemyPos.x = 0; // Reset position to the left side of the screen
	}
}

void Enemy1::handleAnimation()
{
	// Update the animation time based on the frame time
	animationTime += GetFrameTime();

	if (isMoving)
	{
		// If moving, change frame every 0.3 seconds (6 frames total)
		if (animationTime >= 0.3f)
		{
			frame = (frame + 1) % 6; // Cycle through walking frames
			animationTime = 0.0f;	 // Reset the animation time
		}
	}
	else
	{
		// If attacking or idle, change frame every 0.3 seconds (4 frames total)
		if (animationTime >= 1.0f)
		{
			frame = (frame + 1) % 4; // Cycle through attack frames
			animationTime = 0.0f;	 // Reset the animation time
		}
	}
}

const Rectangle Enemy1::enemyRect()
{
	return {enemyPos.x, enemyPos.y, (float)(walk1.width), (float)(walk1.height)};
}
