#include "Game.hpp"

void Game::Run()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Run the car");
	SetTargetFPS(60);

	const Texture2D soilTexture = LoadTexture("Images/Soil_Tile.png");
	Car car({SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f}, "Images/Car_1_01.png");

	Camera2D camera = {0};
	camera.offset = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
	camera.zoom = 1.0f;

	const int tileWidth = soilTexture.width;
	const int tileHeight = soilTexture.height;
	const float halfWidth = SCREEN_WIDTH / 2.0f;
	const float halfHeight = SCREEN_HEIGHT / 2.0f;

	while (!WindowShouldClose())
	{
		const float deltaTime = GetFrameTime();
		car.Update(deltaTime);
		camera.target = car.GetPosition();

		BeginDrawing();
		{
			ClearBackground(BLACK);

			BeginMode2D(camera);
			{
				// Calculate visible tile indices
				const int startX = static_cast<int>((camera.target.x - halfWidth) / tileWidth) - 1;
				const int endX = static_cast<int>((camera.target.x + halfWidth) / tileWidth) + 1;
				const int startY = static_cast<int>((camera.target.y - halfHeight) / tileHeight) - 1;
				const int endY = static_cast<int>((camera.target.y + halfHeight) / tileHeight) + 1;

				// Draw visible tiles
				for (int x = startX; x <= endX; ++x)
				{
					for (int y = startY; y <= endY; ++y)
					{
						DrawTexture(soilTexture, x * tileWidth, y * tileHeight, WHITE);
					}
				}

				car.Draw();
			}
			EndMode2D();
			DrawFPS(0, 10);
		}
		EndDrawing();
	}

	UnloadTexture(soilTexture);
	CloseWindow();
}