#include "Block.hpp"

Block::Block()
{
	cellSize = 30;
	rotationState = 0;
	rowOffset = 0;
	columnOffset = 0;
	colors = getCellColors();
}

void Block::draw(int offSetX, int OffSetY)
{
	std::vector<Position> tiles = getCellPosition();

	// Draw the tiles
	for(Position item : tiles)
	{
		DrawRectangle(item.column * cellSize + offSetX, item.row * cellSize + OffSetY, cellSize - 1, cellSize - 2, colors[id]);
	}
}

void Block::move(int rows, int columns)
{
	rowOffset += rows;
	columnOffset += columns;
}

void Block::rotate()
{
	rotationState++;

	if(rotationState == (int)cells.size())
	{
		rotationState = 0; 
	}
}

void Block::undoRotation()
{
	rotationState--;

	if(rotationState == -1)
	{
		rotationState = cells.size() -1;
	}
}

std::vector<Position> Block::getCellPosition()
{
	std::vector<Position> tiles = cells[rotationState];
	std::vector<Position> moveTiles;

	for(Position item : tiles)
	{
		Position  newPos = Position{item.row + rowOffset, item.column + columnOffset};
		moveTiles.push_back(newPos);
	}

	return moveTiles;
}