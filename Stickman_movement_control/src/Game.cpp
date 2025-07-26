#include "Game.h"

Game::Game()
{
	player.Reset({10, 355}, MAGENTA);
	fire.Reset({400, 399});
	Init();
}

Game::~Game()
{
	CloseWindow();
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

void Game::Reset()
{
	player.Reset({10, 355}, MAGENTA);
	fire.Reset({400, 399});
	isGameOver = false;
}

void Game::Update()
{
	if (isGameOver && IsKeyPressed(KEY_R))
	{
		Reset();
		return;
	}

	if (isGameOver)
		return;

	if (!player.IsAlive())
	{
		isGameOver = true;
	}

	player.Update();
	fire.Update(GetFrameTime());
	player.TakeDamageFromFire(fire);
}

void Game::Draw()
{
	if (isGameOver)
	{
		GameOver();
	}
	else
	{
		player.Draw();
		fire.Draw();
	}
}

void Game::GameOver()
{
	ClearBackground(BLACK);
	DrawText("Game Over! Press R to Restart: ", 150, 250, 20, RED);
}