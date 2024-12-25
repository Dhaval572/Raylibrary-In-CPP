// Catch the red ball
#include <raylib.h>
#include <raymath.h> // To use Vector2Subtract etc
#include <stdlib.h>	 // For rand() and srand()
#include <time.h>

int score = 0;

class Hero
{
	// ( Note: this is bydefault private function )
	void limitMovement()
	{
		// Ensure the circle stays within the window boundaries
		if (heroPos.x < radius)
			heroPos.x = radius;
		if (heroPos.y < radius)
			heroPos.y = radius;
		if (heroPos.x > GetScreenWidth() - radius)
			heroPos.x = GetScreenWidth() - radius;
		if (heroPos.y > GetScreenHeight() - radius)
			heroPos.y = GetScreenHeight() - radius;
	}

public:
	Vector2 heroPos;
	Vector2 targetPos;
	const float moveSpeed = 200.0f;
	const float radius = 20.0f;

	Hero()
	{
		heroPos = {300, 250};
		targetPos = heroPos;
	}

	void Update()
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			targetPos = GetMousePosition();

		// Represents the difference between the two vectors.
		Vector2 direction = Vector2Subtract(targetPos, heroPos);

		// Calculates the length of the vector using the Pythagorean theorem.
		float distance = Vector2Length(direction);

		// If the distance is greater than 0, move the circle towards the target position
		if (distance > 0)
		{
			// Scale the direction vector to move at a constant speed
			direction = Vector2Scale(direction, moveSpeed * GetFrameTime() / distance);

			// Update the circle's position
			heroPos = Vector2Add(heroPos, direction);

			limitMovement();
		}
		else
		{
			// Snap to the target position if very close to avoid flickering
			heroPos = targetPos;
		}
	}

	void Draw()
	{
		DrawCircleV(heroPos, radius, BLUE);
	}
};

class Enemy
{

public:
	Vector2 enemyPos;
	const float radius = 20.0f;
	bool enemyKilled = true;

	void update()
	{
		if (enemyKilled)
		{
			enemyPos = {(float)(rand() % (GetScreenWidth() - (int)radius * 2) + radius), (float)(rand() % (GetScreenHeight() - (int)radius * 2) + radius)};
			enemyKilled = false;
		}
	}

	void checkCollision(Vector2 heroPos, float heroRadius)
	{
		if (CheckCollisionCircles(heroPos, radius, enemyPos, radius))
		{
			enemyKilled = true;
			score++;
		}
	}

	void Draw()
	{
		if (!enemyKilled)
		{
			DrawCircleV(enemyPos, radius, RED);
		}
	}
};

int main()
{
	InitWindow(600, 500, "Circle chaser");

	// TO set time limit
	const int gameTime = 30; // Game duration in seconds
	float timeRemaining = gameTime;
	srand(time(NULL));

	SetTargetFPS(60);

	Hero hero;
	Enemy enemy;

	while (!WindowShouldClose())
	{
		if (timeRemaining > 0)
		{
			hero.Update();
			enemy.update();
			enemy.checkCollision(hero.heroPos, hero.radius);

			// Update the timer
			timeRemaining -= GetFrameTime();
		}

		BeginDrawing();

		ClearBackground(BLACK);

		if (timeRemaining > 0)
		{
			hero.Draw();
			enemy.Draw();

			DrawText(TextFormat("Score: %i", score), 10, 10, 20, GREEN);
			DrawText(TextFormat("Time: %.1f", timeRemaining), 10, 40, 20, GREEN);
		}
		else
		{
			DrawText("GAME OVER", GetScreenWidth() / 2 - MeasureText("GAME OVER", 40) / 2, GetScreenHeight() / 2 - 20, 40, RED);

			DrawText(TextFormat("Your last score was: %i", score), GetScreenWidth() / 2 - MeasureText(TextFormat("Your last score was: %i", score), 20) / 2, GetScreenHeight() / 2 + 20, 20, GREEN);
		}

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
