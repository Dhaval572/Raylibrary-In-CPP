#include <raylib.h>
#include <cstdio>
#include "Flying_enemy.hpp"

FlyingDragon::FlyingDragon()
{
	enemyPos = {(float)GetScreenWidth(), -100.0f};
	isMoving = true;
	speed = 0.5f;
	maxHealth = 150;
	currentHealth = maxHealth;
	frame = 0;
	animationTime = 0.0f;

	// Healing parameters
	healAmount = 5.0f;
	healCooldown = 1.0f;
	healTimer = 0.0f;

	loadAnimationFrames("Sprites/Flying Enemy/Fly/Fly%d.png", flyFrames, 4, 50, 50);
}

FlyingDragon::~FlyingDragon()
{
	unloadTextures(flyFrames, 4);
}

void FlyingDragon::draw()
{
	Texture2D currentFrame = getCurrentAnimationFrame();
	DrawTexture(currentFrame, (int)enemyPos.x + 100, (int)enemyPos.y + 90, WHITE);
}

Texture2D FlyingDragon::getCurrentAnimationFrame()
{
	return flyFrames[frame % 4];
}

void FlyingDragon::update(Player &player)
{
	followPlayer(player);
	handleHealing(player);
	handleAnimation();
}

void FlyingDragon::loadAnimationFrames(const char *pathPattern, Texture2D *frameArray, int frameCount, int width, int height)
{
	for (int i = 0; i < frameCount; i++)
	{
		char path[128];
		snprintf(path, sizeof(path), pathPattern, i);
		Image img = LoadImage(path);
		ImageResize(&img, width, height);
		frameArray[i] = LoadTextureFromImage(img);
		UnloadImage(img);
	}
}

void FlyingDragon::unloadTextures(Texture2D *frameArray, int frameCount)
{
	for (int i = 0; i < frameCount; i++)
	{
		UnloadTexture(frameArray[i]);
	}
}

void FlyingDragon::followPlayer(Player &player)
{
	Rectangle playerRect = player.playerRect();

	// Determine the target position for the enemy (120 pixels to the left of player)
	float targetX = playerRect.x - 120.0f;
	float deltaX = targetX - enemyPos.x;
	enemyPos.x += deltaX * 0.05f;

	// Position above the player
	float targetY = playerRect.y - flyFrames[0].height - 50.0f;
	float deltaY = targetY - enemyPos.y;
	enemyPos.y += deltaY * 0.05f;
}

void FlyingDragon::handleHealing(Player &player)
{
	if (player.currentHealth() < player.maxHealth())
	{
		healTimer += GetFrameTime();

		if (healTimer >= healCooldown)
		{
			player.heal(healAmount);
			healTimer = 0.0f;
		}
	}
	else
	{
		healTimer = 0.0f;
	}
}

void FlyingDragon::handleAnimation()
{
	animationTime += GetFrameTime();

	if (animationTime >= 0.35f)
	{
		frame++;
		animationTime = 0.0f;
	}
}

const Rectangle FlyingDragon::enemyRect()
{
	return {enemyPos.x, enemyPos.y, (float)flyFrames[0].width, (float)flyFrames[0].height};
}