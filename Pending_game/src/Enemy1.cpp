#include <raylib.h>
#include <stdio.h>
#include "Player.hpp"
#include "Enemy1.hpp"

Enemy1::Enemy1()
{
	enemyPos = {0.0f, 300.0f};
	isMoving = false;
	speed = 1.0f;
	maxHealth = 100;
	currentHealth = maxHealth;
	healthBar = {enemyPos.x, enemyPos.y - 30, 50, 5};
	frame = 0;
	animationTime = 0.0f;

	spawnDelay = 1.5f;
	elapsedTime = 0.0f;
	isActive = false;

	for (int i = 0; i < 8; i++)
	{
		char walkPath[64];
		sprintf(walkPath, "Sprites/Enemy walking/Walk_(%d).png", i + 1);
		walkFrames[i] = loadTextureFromResizedImage(walkPath, 240, 240);

		char attackPath[64];
		sprintf(attackPath, "Sprites/Enemy Attack/Attack_(%d).png", i + 8);
		attackFrames[i] = loadTextureFromResizedImage(attackPath, 240, 240);
	}
}

Enemy1::~Enemy1()
{
	for (int i = 0; i < 8; i++)
	{
		UnloadTexture(walkFrames[i]);
		UnloadTexture(attackFrames[i]);
	}
}

void Enemy1::draw()
{
	Texture2D currentFrame = getCurrentAnimationFrame();
	DrawTexture(currentFrame, (int)enemyPos.x, (int)enemyPos.y, WHITE);
	drawHealthBar();
}

Texture2D Enemy1::getCurrentAnimationFrame()
{
	return isMoving ? walkFrames[frame] : attackFrames[frame];
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
	float currentWidth = walkFrames[0].width; // Assuming all frames are same size
	float healthBarWidth = currentWidth * 0.2f;
	float healthBarHeight = 8.0f;
	float healthBarX = enemyPos.x + (currentWidth - healthBarWidth) / 2.0f;
	float healthBarY = enemyPos.y + 60;

	float healthPercentage = (float)currentHealth / (float)maxHealth;
	float filledWidth = healthBarWidth * healthPercentage;

	DrawRectangleRec({healthBarX, healthBarY, filledWidth, healthBarHeight}, RED);

	DrawRectangleLinesEx(
		{healthBarX, healthBarY, healthBarWidth, healthBarHeight},
		1.0f,
		ColorAlpha(WHITE, 0.8f));
}

void Enemy1::handleMovement(Player &player)
{
	Rectangle enemyRect = {enemyPos.x, enemyPos.y, (float)walkFrames[0].width, (float)walkFrames[0].height};
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

	if (enemyPos.x > GetScreenWidth() + walkFrames[0].width)
	{
		enemyPos.x = -walkFrames[0].width;
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
	return {enemyPos.x, enemyPos.y, (float)(walkFrames[0].width), (float)(walkFrames[0].height)};
}
