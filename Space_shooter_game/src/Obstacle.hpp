#pragma once
#include "Block.hpp"
#include <vector>

class Obstacle
{
public:

	explicit Obstacle(Vector2 position);
	void Draw();
	Vector2 position;
	std::vector<Block> blocks;
	static std::vector<std::vector<int>> grid;
};