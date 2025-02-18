#pragma once
#include <vector>
#include <map>
#include "Block_position.hpp"
#include "Colors.hpp"

class Block
{
	int cellSize;
	int rotationState;
	int rowOffset;
	int columnOffset;
	std::vector<Color> colors;

public:

	int id;
	std::map<int, std::vector<Position>> cells;
	Block();
	void draw(int offSetX, int offSetY);
	void move(int rows, int columns);
	void rotate();
	void undoRotation();
	std::vector<Position> getCellPosition();
};