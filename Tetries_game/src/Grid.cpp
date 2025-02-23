#include "Grid.hpp"
#include <iostream>
#include "Colors.hpp"

bool Grid::isRowFull(int row)
{
	for (int column = 0; column < numCols; column++)
	{
		if (grid[row][column] == 0)
		{
			return false;
		}
	}

	return true;
}

void Grid::clearRow(int row)
{
	for (int column = 0; column < numCols; column++)
	{
		grid[row][column] = 0;
	}
}

void Grid::moveRowDown(int row, int numRows)
{
	for (int column = 0; column < numCols; column++)
	{
		grid[row + numRows][column] = grid[row][column]; 
		grid[row][column] = 0;
	}
}

Grid::Grid()
{
	numRows = 20;
	numCols = 10;
	cellSize = 30;
	initialize();
	colors = getCellColors();
}

void Grid::initialize()
{
	for (int row = 0; row < numRows; row++)
	{
		for (int column = 0; column < numCols; column++)
		{
			grid[row][column] = 0;
		}
	}
}

void Grid::print()
{
	for (int row = 0; row < numRows; row++)
	{
		for (int column = 0; column < numCols; column++)
		{
			std::cout << grid[row][column] << ' ';
		}

		std::cout << "\n";
	}
}

void Grid::draw()
{
	for (int row = 0; row < numRows; row++)
	{
		for (int column = 0; column < numCols; column++)
		{
			int cellvalue = grid[row][column];

			// Draw each rectangle as grid
			DrawRectangle(column * cellSize + 11, row * cellSize + 11, cellSize - 1, cellSize - 1, colors[cellvalue]);
		}
	}
}

bool Grid::isCellOutSide(int row, int column)
{
	// Check is cell is out side?
	if (row >= 0 && row < numRows && column >= 0 && column < numCols)
	{
		return false;
	}

	// Else part
	return true;
}

bool Grid::isCellEmpty(int row, int column)
{
	if (grid[row][column] == 0)
	{
		return true;
	}

	return false;
}

int Grid::clearFullRows()
{
	int completed = 0;
	for (int row = numRows - 1; row >= 0; row--)
	{
		if (isRowFull(row))
		{
			clearRow(row);
			completed++;
		}

		else if (completed > 0)
		{
			moveRowDown(row, completed);
		}
	}

	return completed;
}