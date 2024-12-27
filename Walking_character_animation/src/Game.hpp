#pragma once
#include "Player.hpp"
#include "Enemy1.hpp"
#include <raylib.h>

class Game
{
public:

	Game();
	~Game();
	void Draw();
	void Update();
	void updateAnimation();
	void handleInput();

private:

	Player player; // Creating object
	Enemy1 enemy1;	
};
