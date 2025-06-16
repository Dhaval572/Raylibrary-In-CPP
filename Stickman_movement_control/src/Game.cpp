#include "Game.h"
#include "raylib.h"

Game::Game()
    : player({10, 355}, MAGENTA), fire({400, 399}) // Initialize player and fire
{
    Init();
}

Game::~Game()
{
    CloseWindow(); // Clean up
}

void Game::Init()
{
    InitWindow(600, 500, "Control stickman");
    SetTargetFPS(60);
}

void Game::Run()
{
    while (!WindowShouldClose())
    {
        Update();

        BeginDrawing();
        ClearBackground(BLACK);
        Draw();
        EndDrawing();
    }
}

void Game::Update()
{
    player.Update();
    fire.Update(GetFrameTime());
	player.TakeDamage(fire); 
}

void Game::Draw()
{
    player.Draw();
    fire.Draw();
}
