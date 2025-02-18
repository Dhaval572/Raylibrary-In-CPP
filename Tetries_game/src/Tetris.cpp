// Tetris game in c++
#include <raylib.h>
#include <iostream>
#include "Game.hpp"
#include "Colors.hpp"

double lastUpdateTime = 0;

bool eventTriggered(int interval)
{
	double currentTime = GetTime();
	if (currentTime - lastUpdateTime >= interval)
	{
		lastUpdateTime = currentTime;
		return true;
	}

	return false;
}

int main()
{
	InitWindow(500, 620, "Tetris");

	SetTargetFPS(60);

	Game game = Game();

	while (!WindowShouldClose())
	{
		// UpdateMusicStream(game.music); // There is some problem 
		game.handleInput();

		if (eventTriggered(1))
			game.moveBlockDown();

		BeginDrawing();

		ClearBackground(backgroundColor);
		DrawText("Score", 365, 15, 38, WHITE);
		DrawText("Next", 370, 175, 38, WHITE);

		if (game.gameOver)
			DrawText("Game Over", 320, 450, 32, WHITE);

		DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);

		char scoreText[10];
		sprintf(scoreText, "%d", game.score);
		Vector2 textSize = MeasureTextEx(GetFontDefault(), scoreText, 38, 0);

		DrawText(scoreText, 320 + (170 - textSize.x) / 2, 65, 38, WHITE);
		DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);
		game.draw();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}