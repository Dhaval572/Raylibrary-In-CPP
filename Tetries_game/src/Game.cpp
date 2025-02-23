#include "Game.hpp"
#include <random>

// Constructor
Game::Game()
{
	grid = Grid();
	blocks = getAllBlocks();
	currentBlock = getRandomBlock();
	nextBlock = getRandomBlock();
	gameOver = false;
	score = 0;
	InitAudioDevice();
	music = LoadMusicStream("Game_Sound/music.mp3");
	PlayMusicStream(music);
	rotateSound = LoadSound("Game_Sound/rotate.mp3");
	clearSound = LoadSound("Game_Sound/clear.mp3");
}

Game::~Game()
{
	UnloadMusicStream(music);
	UnloadSound(rotateSound);
	UnloadSound(clearSound);
	CloseAudioDevice();
}

// Public Methods
void Game::Reset()
{
	grid.initialize();
	blocks = getAllBlocks();
	currentBlock = getRandomBlock();
	nextBlock = getRandomBlock();
	score = 0;
}

void Game::draw()
{
	grid.draw();
	currentBlock.draw(11, 11);

	// To draw next block in center
	switch (nextBlock.id)
	{
	case 3:
		nextBlock.draw(255, 290);
		break;

	case 4:
		nextBlock.draw(255, 280);
		break;

	default:
		nextBlock.draw(270, 270);
		break;
	}
}

void Game::handleInput()
{
	int keyPressed = GetKeyPressed();

	if (gameOver && keyPressed != 0)
	{
		gameOver = false;
		Reset();
	}

	switch (keyPressed)
	{
	case KEY_LEFT:
		moveBlockLeft();
		break;

	case KEY_RIGHT:
		moveBlockRight();
		break;

	case KEY_DOWN:
		moveBlockDown();
			updateScore(0, 1);
			
		break;

	case KEY_UP:
		rotateBlock();
		break;
	}
}

// Private Methods
bool Game::isBlockOutSide()
{
	std::vector<Position> tiles = currentBlock.getCellPosition();

	// Checks for all tiles
	for (Position item : tiles)
	{
		if (grid.isCellOutSide(item.row, item.column))
			return true;
	}
	return false;
}

void Game::rotateBlock()
{
	if (!gameOver)
	{
		currentBlock.rotate();

		if (isBlockOutSide() || !blockFits())
		{
			currentBlock.undoRotation();
		}
		else
		{
			PlaySound(rotateSound);
		}
	}
}

void Game::lockBlock()
{
	std::vector<Position> tiles = currentBlock.getCellPosition();

	for (Position item : tiles)
	{
		grid.grid[item.row][item.column] = currentBlock.id;
	}

	currentBlock = nextBlock;
	if (!blockFits())
	{
		gameOver = true;
	}
	nextBlock = getRandomBlock();
	int rowCleared = grid.clearFullRows(); // Remove the row which fully filled

	if (rowCleared > 0)
	{
		PlaySound(clearSound);
		updateScore(rowCleared, 0);
	}
}

bool Game::blockFits()
{
	std::vector<Position> tiles = currentBlock.getCellPosition();

	// Iterate through all the tiles of the current block
	for (Position item : tiles)
	{
		// If any tile is not empty, the block does not fit
		if (!grid.isCellEmpty(item.row, item.column))
		{
			return false;
		}
	}

	// All tiles are empty, the block fits
	return true;
}

Block Game::getRandomBlock()
{
	// Check if blocks vector is empty
	if (blocks.empty())
	{
		blocks = getAllBlocks();
	}

	int randomIndex = rand() % blocks.size();
	Block block = blocks[randomIndex];

	// Erase the block
	blocks.erase(blocks.begin() + randomIndex);
	return block;
}

std::vector<Block> Game::getAllBlocks()
{
	return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::moveBlockLeft()
{
	if (!gameOver)
	{
		currentBlock.move(0, -1);
		if (isBlockOutSide() || !blockFits())
		{
			currentBlock.move(0, 1); // Move back to the original position
		}
	}
}

void Game::moveBlockRight()
{
	if (!gameOver)
	{
		currentBlock.move(0, 1);
		if (isBlockOutSide() || !blockFits())
		{
			currentBlock.move(0, -1); // Move back to the original position
		}
	}
}

void Game::moveBlockDown()
{
	if (!gameOver)
	{
		currentBlock.move(1, 0);
		if (isBlockOutSide() || !blockFits())
		{
			currentBlock.move(-1, 0); // Move back to the original position
			lockBlock();
		}
	}
}

void Game::updateScore(int linesCleared, int moveDownPoints)
{
	switch (linesCleared)
	{
	case 1:
		score += 100;
		break;

	case 2:
		score += 300;
		break;

	case 3:
		score += 500;
		break;
		
	default:
		break;
	}

	score += moveDownPoints;
}