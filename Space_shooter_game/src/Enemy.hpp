#include <raylib.h>
#pragma once

class Enemy
{
public:

	explicit Enemy(int type, Vector2 enemy_pos);
	void Update(int);
	void Draw();
	int GetType() const;
	static void Unloadimg();
	Rectangle GetRect();
	static Texture2D enemy_img[3];
	int type;
	Vector2 enemy_pos;

};