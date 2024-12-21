// Pixel Quest game in raylib
#include <raylib.h>
#include <stdlib.h> // For rand() and srand()
#include <time.h>

int main()
{
	const int screenWidth = 600;
	const int screenHeight = 500;
	InitWindow(screenWidth, screenHeight, "Pixel Quest");

	// Player variables
	Vector2 playerPosition = {screenWidth / 2.0f, screenHeight / 2.0f};
	const int playerSize = 20;
	const int playerSpeed = 5;
	const float playerRadius = playerSize / 2.0f;

	// Coin variables
	Vector2 coinPosition;
	const int coinSize = 10;
	const int coinRadius = coinSize / 2.0f;
	bool coinCollected = true;

	// Game variables
	int score = 0;			 // Initialize the score with 0
	const int gameTime = 30; // Game duration in seconds
	float timeRemaining = gameTime;

	// Seed the random number generator
	srand(time(NULL));

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		// Update
		if (timeRemaining > 0)
		{
			// Move the player
			if (IsKeyDown(KEY_RIGHT))
				playerPosition.x += playerSpeed;
			if (IsKeyDown(KEY_LEFT))
				playerPosition.x -= playerSpeed;
			if (IsKeyDown(KEY_UP))
				playerPosition.y -= playerSpeed;
			if (IsKeyDown(KEY_DOWN))
				playerPosition.y += playerSpeed;

			// Boundary checks
			if (playerPosition.x > GetScreenWidth() - playerRadius)
				playerPosition.x = GetScreenWidth() - playerRadius;
			if (playerPosition.x < playerRadius)
				playerPosition.x = playerRadius;
			if (playerPosition.y < playerRadius)
				playerPosition.y = playerRadius;
			if (playerPosition.y > GetScreenHeight() - playerRadius)
				playerPosition.y = GetScreenHeight() - playerRadius;

			// Check for coin collection
			if (coinCollected)
			{
				// Spawn the gold coin at random position in the screen
				coinPosition = {(float)(rand() % (screenWidth - coinSize)), (float)(rand() % (screenHeight - coinSize))};

				coinCollected = false;
			}

			// Checks collision between player and coin
			if (CheckCollisionCircles(playerPosition, playerRadius, coinPosition, coinRadius))
			{
				coinCollected = true;
				score++;
			}

			// Update timer
			timeRemaining -= GetFrameTime(); // GetFrameTime() gets time in second
		}

		BeginDrawing();

		// Clear previous frame
		ClearBackground(BLACK);

		// Draw player
		DrawCircleV(playerPosition, playerRadius, MAGENTA);

		// Draw coin
		if (!coinCollected)
		{
			DrawCircleV(coinPosition, coinRadius, GOLD);
		}

		// Draw score and timer
		DrawText(TextFormat("Score: %i", score), 10, 10, 20, GREEN);
		DrawText(TextFormat("Time: %.1f", timeRemaining), 10, 40, 20, GREEN);

		// Draw game over message
		if (timeRemaining <= 0)
		{
			DrawText("GAME OVER", screenWidth / 2 - MeasureText("GAME OVER", 40) / 2, screenHeight / 2 - 20, 40, RED);
		}

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
