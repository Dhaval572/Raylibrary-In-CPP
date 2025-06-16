#pragma once

#include <raylib.h>
#include "Fire_partical.h"
#include "Stickman.h"

class Game
{
public:
	Game();
	~Game();
	void Run();

private:
	void Init();
	void Update();
	void Draw();
	void GameOver();

	Stickman player;
	Fire fire;
	bool isGameOver = false;
};