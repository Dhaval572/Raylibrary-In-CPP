#include <raylib.h>
#pragma once

class MysteryShip
{
public:

	explicit MysteryShip();
	~MysteryShip();
	void Update();
	void Draw();
	void Spawn();
	Rectangle GetRect() const;
	bool alive;

private:

	Vector2 mystery_ship_pos;
	Texture2D mystery_ship_image;
	int speed;
};