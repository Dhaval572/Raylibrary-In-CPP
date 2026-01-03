#include "Block.hpp"

Block::Block(Vector2 position) : position(position) {}

void Block::Draw()
{
	DrawRectangle(position.x, position.y, 3, 3, GREEN);
}

Rectangle Block::GetRect() const
{
	// Draw rectangle arroud block
	Rectangle rect;
	rect.x = position.x;
	rect.y = position.y;
	rect.width = 3;
	rect.height = 3;
	return rect;
}
