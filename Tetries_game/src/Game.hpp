#pragma once
#include "Grid.hpp"
#include "Blocks.cpp"

class Game
{
	// Data
	std::vector<Block> blocks;
	Block currentBlock;
	Block nextBlock;
	Grid grid;
	Sound rotateSound;
	Sound clearSound;

	// Functions
	Block getRandomBlock();
	std::vector<Block> getAllBlocks();
	bool isBlockOutSide();
	void rotateBlock();
	void lockBlock();
	bool blockFits();
	void updateScore(int lineCleared, int moveDownPoints);
	void Reset();
	void moveBlockLeft();
	void moveBlockRight();

public:
	// Functions
	Game();
	~Game();
	Music music;
	bool gameOver;
	int score;
	void draw();
	void handleInput();
	void moveBlockDown();
};
