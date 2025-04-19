#include "Game.hpp"

Game::Game()
    : damageDelayTimer(0.0f) // Initialize the timer
{
    // Constructor can initialize additional elements if needed
}

Game::~Game()
{
    // Destructor, clean up any resources if necessary
}

void Game::Draw()
{
    if (!gameOver)
    {
        player.draw(); // Draw the player
        enemy1.draw(); // Draw the enemy
    }
    else
    {
        // Clear the background
        ClearBackground(BLACK);

        const char* Text = "GAME OVER";

        int textWidth = MeasureText(Text, 40);

        int xPos = (GetScreenWidth() - textWidth) / 2;
        int yPos = GetScreenHeight() / 2 - 20;

        DrawText(Text, xPos, yPos, 40, RED);
    }
}

void Game::Update()
{
    handleInput();

    player.update();       // Update the player's state (position, logic, etc.)
    enemy1.update(player); // Pass the player object to the enemy for movement and collision detection

    damageDelayTimer += GetFrameTime(); // GetFrameTime() is from Raylib or similar frameworks

    // Check for collision and if the delay has passed
    if (CheckCollisionRecs(player.playerRect(), enemy1.enemyRect()) && damageDelayTimer >= damageDelayTime)
    {
        player.talkDamage(10.0f); // Apply damage to the player
        damageDelayTimer = 0.0f;  // Reset the timer after applying damage
    }

    if(player.getHealth() <= 0.0f)
        gameOver = true;

    updateAnimation();
}

void Game::handleInput()
{
    player.handleMovement();       // Handle player input and movement
    enemy1.handleMovement(player); // Handle enemy movement (if necessary)
}

void Game::updateAnimation()
{
    player.updateAnimation(); // Update the player's animation
    enemy1.handleAnimation(); // Update the enemy's animation
}
