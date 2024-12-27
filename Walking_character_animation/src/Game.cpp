#include "Game.hpp"

Game::Game() : player("Images/monster_right_1.png", "Images/monster_right_2.png",
    		          "Images/monster_left_1.png", "Images/monster_left_2.png", GetScreenWidth() / 2, 325, 2.0f)
{
	
}

Game::~Game()
{

}

void Game::Draw()
{
	player.draw();
	enemy1.draw();
}

void Game::Update()
{
	player.update();
	enemy1.update();
}

void Game::handleInput()
{
	player.handleMovement();
	enemy1.handleMovement();
}

void Game::updateAnimation()
{
	player.updateAnimation();
	enemy1.handleAnimation();
}
