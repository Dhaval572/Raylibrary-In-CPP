#include <raylib.h>
#include "Player.hpp"
#include "Enemy1.hpp"

Enemy1::Enemy1()
{
	// Initialize enemy properties
	enemyPos = {0.0f, 300.0f};
	isMoving = false;
	speed = 1.0f;
	maxHealth = 100;
	currentHealth = maxHealth;
	healthBar = {enemyPos.x, enemyPos.y - 30, 50, 5};
	frame = 0;
	animationTime = 0.0f;

	// Delay-related setup
	spawnDelay = 1.5f;
	elapsedTime = 0.0f;
	isActive = false;

	// Load walking textures (240x240)
	walk1 = loadTextureFromResizedImage("Sprites/Enemy walking/Walk_(1).png", 240, 240);
	walk2 = loadTextureFromResizedImage("Sprites/Enemy walking/Walk_(2).png", 240, 240);
	walk3 = loadTextureFromResizedImage("Sprites/Enemy walking/Walk_(3).png", 240, 240);
	walk4 = loadTextureFromResizedImage("Sprites/Enemy walking/Walk_(4).png", 240, 240);
	walk5 = loadTextureFromResizedImage("Sprites/Enemy walking/Walk_(5).png", 240, 240);
	walk6 = loadTextureFromResizedImage("Sprites/Enemy walking/Walk_(6).png", 240, 240);
	walk7 = loadTextureFromResizedImage("Sprites/Enemy walking/Walk_(7).png", 240, 240);
	walk8 = loadTextureFromResizedImage("Sprites/Enemy walking/Walk_(8).png", 240, 240);

	// Load attacking textures (also 240x240 for consistency)
	attack1 = loadTextureFromResizedImage("Sprites/Enemy Attack/Attack_(8).png", 240, 240);
	attack2 = loadTextureFromResizedImage("Sprites/Enemy Attack/Attack_(9).png", 240, 240);
	attack3 = loadTextureFromResizedImage("Sprites/Enemy Attack/Attack_(10).png", 240, 240);
	attack4 = loadTextureFromResizedImage("Sprites/Enemy Attack/Attack_(11).png", 240, 240);
	attack5 = loadTextureFromResizedImage("Sprites/Enemy Attack/Attack_(12).png", 240, 240);
	attack6 = loadTextureFromResizedImage("Sprites/Enemy Attack/Attack_(13).png", 240, 240);
	attack7 = loadTextureFromResizedImage("Sprites/Enemy Attack/Attack_(14).png", 240, 240);
	attack8 = loadTextureFromResizedImage("Sprites/Enemy Attack/Attack_(15).png", 240, 240);
}

Enemy1::~Enemy1()
{
	UnloadTexture(walk1);
	UnloadTexture(walk2);
	UnloadTexture(walk3);
	UnloadTexture(walk4);
	UnloadTexture(walk5);
	UnloadTexture(walk6);
	UnloadTexture(walk7);
	UnloadTexture(walk8);

	UnloadTexture(attack1);
	UnloadTexture(attack2);
	UnloadTexture(attack3);
	UnloadTexture(attack4);
	UnloadTexture(attack5);
	UnloadTexture(attack6);
	UnloadTexture(attack7);
	UnloadTexture(attack8);
}

void Enemy1::draw()
{
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
		case 6:
			currentFrame = walk7;
			break;
		case 7:
			currentFrame = walk8;
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
		case 4:
			currentFrame = attack5;
			break;
		case 5:
			currentFrame = attack6;
			break;
		case 6:
			currentFrame = attack7;
			break;
		case 7:
			currentFrame = attack8;
			break;
		default:
			currentFrame = attack1;
			break;
		}
	}

	DrawTexture(currentFrame, (int)enemyPos.x, (int)enemyPos.y, WHITE);
	drawHealthBar();
}

void Enemy1::update(Player &player)
{
	elapsedTime += GetFrameTime();

	if (elapsedTime >= spawnDelay)
		isActive = true;

	if (isActive)
	{
		handleMovement(player);
		handleAnimation();
	}
}

Image Enemy1::resizeTextureForWalk(const char *path, int width, int height)
{
	Image img = LoadImage(path);
	ImageResize(&img, width, height);
	return img;
}

Texture2D Enemy1::loadTextureFromResizedImage(const char *path, int width, int height)
{
	Image resizedImage = resizeTextureForWalk(path, width, height);
	Texture2D texture = LoadTextureFromImage(resizedImage);
	UnloadImage(resizedImage);
	return texture;
}

void Enemy1::drawHealthBar()
{
	// Calculate dimensions based on current frame's texture
	float currentWidth = isMoving ? walk1.width : attack1.width;

	// Health bar dimensions - smaller width but taller height
	float healthBarWidth = currentWidth * 0.2f; // 50% of enemy width
	float healthBarHeight = 8.0f;				// Taller than before (8px)

	float healthBarX = enemyPos.x + (currentWidth - healthBarWidth) / 2.0f;
	float healthBarY = enemyPos.y + 60;

	// Foreground (current health) - bright red
	float healthPercentage = (float)currentHealth / (float)maxHealth;
	float filledWidth = healthBarWidth * healthPercentage;

	DrawRectangleRec(
		{healthBarX, healthBarY, filledWidth, healthBarHeight},
		RED);

	// Add border for better visibility
	DrawRectangleLinesEx(
		{healthBarX, healthBarY, healthBarWidth, healthBarHeight},
		1.0f,
		ColorAlpha(WHITE, 0.8f) // Slightly transparent white border
	);
}

void Enemy1::handleMovement(Player &player)
{
	Rectangle enemyRect = {enemyPos.x, enemyPos.y, (float)walk1.width, (float)walk1.height};
	Rectangle playerRect = player.playerRect();

	if (CheckCollisionRecs(enemyRect, playerRect))
	{
		isMoving = false;
	}
	else if (enemyPos.x < playerRect.x)
	{
		isMoving = true;
		enemyPos.x += speed;
	}

	if (enemyPos.x > GetScreenWidth() + walk1.width)
	{
		enemyPos.x = -walk1.width;
	}
}

void Enemy1::handleAnimation()
{
	animationTime += GetFrameTime();

	if (animationTime >= 0.3f)
	{
		frame = (frame + 1) % 8;
		animationTime = 0.0f;
	}
}

const Rectangle Enemy1::enemyRect()
{
	return {enemyPos.x, enemyPos.y, (float)(walk1.width), (float)(walk1.height)};
}
