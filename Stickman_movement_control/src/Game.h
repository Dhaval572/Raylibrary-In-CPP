#pragma once

#include <raylib.h>
#include "Fire_partical.h"
#include "Stickman.h"

class Game
{
public:
	Game();		// Constructor
	~Game();	// Destructor
	void Run(); // Main game loop

private:
	void Init();   // Window and setup
	void Update(); // Per-frame logic
	void Draw();   // Per-frame rendering

	Stickman player;
	Fire fire;
};