#include "Game.hpp"

Game::Game() : player("Sprites/Player walking/monster_right_1.png", 
					  "Sprites/Player walking/monster_right_2.png",
					  "Sprites/Player walking/monster_left_1.png", 
					  "Sprites/Player walking/monster_left_2.png", 
					  GetScreenWidth() / 2, 325, 2.0f)
{
	// Constructor can initialize additional elements if needed
}

Game::~Game()
{
	// Destructor, clean up any resources if necessary
}

void Game::Draw()
{
	player.draw(); // Draw the player
	enemy1.draw(); // Draw the enemy
}

void Game::Update()
{
	player.update();	   // Update the player's state (position, logic, etc.)
	enemy1.update(player); // Pass the player object to the enemy for movement and collision detection
}

void Game::handleInput()
{
	player.handleMovement();	   // Handle player input and movement
	enemy1.handleMovement(player); // Handle enemy movement (if necessary)
}

void Game::updateAnimation()
{
	player.updateAnimation(); // Update the player's animation
	enemy1.handleAnimation(); // Update the enemy's animation
}
