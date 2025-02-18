#include "Enemy.hpp"

Texture2D Enemy::enemyImg[3] = {};

Enemy::Enemy(int type, Vector2 enemyPos)
{
	this->type = type;
	this->enemyPos = enemyPos;

	if (enemyImg[type - 1].id == 0)
	{
		switch (type)
		{
		case 1:
			enemyImg[0] = LoadTexture("src/pixel_ship_blue.png"); // Enemy 1
			break;

		case 2:
			enemyImg[1] = LoadTexture("src/pixel_ship_yellow.png"); // Enemy 2
			break;

		case 3:
			enemyImg[2] = LoadTexture("src/pixel_ship_red_small_2.png"); // Enemy 3
			break;

		default:
			enemyImg[0] = LoadTexture("src/pixel_ship_blue.png");
			break;
		}
	}
}

void Enemy::draw()
{
	DrawTextureV(enemyImg[type - 1], enemyPos, WHITE);
}

int Enemy::getType()
{
	return type;
}

void Enemy::unloadimg()
{
	for (int i = 0; i < 4; i++)
	{
		UnloadTexture(enemyImg[i]);
	}
}

Rectangle Enemy::getRect()
{
	// Make rectangle arround image to check collision
	return {enemyPos.x, enemyPos.y,
	float(enemyImg[type - 1].width),
	float(enemyImg[type - 1].height)};	
}

void Enemy::update(int direction)
{
	enemyPos.x += direction;
}