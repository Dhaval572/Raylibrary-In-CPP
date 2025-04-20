#pragma once
#include <raylib.h>
#include "Player.hpp"
#include "Enemy1.hpp"
#include "Flying_enemy.hpp"

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
	FlyingDragon dragon;
	
	float damageDelayTimer;
	const float damageDelayTime = 1.0f;
	bool gameOver;
};