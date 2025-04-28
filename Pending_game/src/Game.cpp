#include "Game.hpp"

Game::Game()
    : damageDelayTimer(0.0f)
{
}

Game::~Game()
{
}

void Game::Draw()
{
    if (!gameOver)
    {
        player.draw();
        enemy1.draw();
        dragon.draw();
    }

    else
    {
        ClearBackground(BLACK);

        const char *Text = "GAME OVER";

        int textWidth = MeasureText(Text, 40);

        int xPos = (GetScreenWidth() - textWidth) / 2;
        int yPos = GetScreenHeight() / 2 - 20;

        DrawText(Text, xPos, yPos, 40, RED);
    }
}

void Game::Update()
{
    handleInput();

    player.update(); 
    enemy1.update(player);
    dragon.update(player);

    damageDelayTimer += GetFrameTime(); // GetFrameTime() is from Raylib or similar frameworks

    // Check for collision and if the delay has passed
    if (CheckCollisionRecs(player.playerRect(), enemy1.enemyRect()) && damageDelayTimer >= damageDelayTime)
    {
        player.takeDamage(10.0f); // Apply damage to the player
        damageDelayTimer = 0.0f;  // Reset the timer after applying damage
    }

    if (player.getHealth() <= 0.0f)
        gameOver = true;

    updateAnimation();
}

void Game::handleInput()
{
    player.handleMovement(); 
}

void Game::updateAnimation()
{
    player.updateAnimation(); // Update the player's animation
    enemy1.handleAnimation();
    dragon.handleAnimation();
}