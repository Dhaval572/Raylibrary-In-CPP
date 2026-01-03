#include <raylib.h>
#pragma once

class Block
{
	Vector2 position;
public:

	explicit Block(Vector2 position);
	void Draw();
	Rectangle GetRect() const;
};