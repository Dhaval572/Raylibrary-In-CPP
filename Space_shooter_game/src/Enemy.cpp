#include "Enemy.hpp"

Texture2D Enemy::enemy_img[3] = {};
Enemy::Enemy(int type, Vector2 enemy_pos) 
	: type(type)
	, enemy_pos(enemy_pos)
{
	if (enemy_img[type - 1].id == 0)
	{
		switch (type)
		{
		case 1:
			enemy_img[0] = LoadTexture("src/pixel_ship_blue.png"); // Enemy 1
			break;

		case 2:
			enemy_img[1] = LoadTexture("src/pixel_ship_yellow.png"); // Enemy 2
			break;

		case 3:
			enemy_img[2] = LoadTexture("src/pixel_ship_red_small_2.png"); // Enemy 3
			break;

		default:
			enemy_img[0] = LoadTexture("src/pixel_ship_blue.png");
			break;
		}
	}
}

void Enemy::Draw()
{
	DrawTextureV(enemy_img[type - 1], enemy_pos, WHITE);
}

int Enemy::GetType() const
{
	return type;
}

void Enemy::Unloadimg()
{
	for (int i = 0; i < 4; i++)
	{
		UnloadTexture(enemy_img[i]);
	}
}

Rectangle Enemy::GetRect()
{
	// Make rectangle arround image to check collision
	return 
	{
		enemy_pos.x, enemy_pos.y,
		float(enemy_img[type - 1].width),
		float(enemy_img[type - 1].height)
	};	
}

void Enemy::Update(int direction)
{
	enemy_pos.x += direction;
}