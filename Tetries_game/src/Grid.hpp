#pragma once
#include <vector>
#include <raylib.h>

class Grid
{
	int numRows;
	int numCols;
	int cellSize;
	bool isRowFull(int row);
	void clearRow(int row);
	void moveRowDown(int row, int numRows);
	std::vector<Color> colors;

public:
	Grid();
	void initialize();
	void print();
	void draw();
	bool isCellOutSide(int row, int column);
	bool isCellEmpty(int row, int column);
	int clearFullRows();
	int grid[20][10];
};