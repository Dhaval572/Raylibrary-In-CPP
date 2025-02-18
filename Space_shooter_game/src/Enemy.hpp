#include <raylib.h>
#pragma once

class Enemy
{


public:

	Enemy(int type, Vector2 enemyPos);
	void update(int);
	void draw();
	int getType();
	static void unloadimg();
	Rectangle getRect();
	static Texture2D enemyImg[3];
	int type;
	Vector2 enemyPos;

};