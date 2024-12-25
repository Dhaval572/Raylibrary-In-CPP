// Move the circle via mouse click
#include <raylib.h>
#include <raymath.h> // To use Vector2Subtract etc

class Hero
{
	// ( Note: this is bydefault private function )
	void limitMovement()
	{
		// Ensure the circle stays within the window boundaries
		if (circlePos.x < radius)
			circlePos.x = radius;
		if (circlePos.y < radius)
			circlePos.y = radius;
		if (circlePos.x > GetScreenWidth() - radius)
			circlePos.x = GetScreenWidth() - radius;
		if (circlePos.y > GetScreenHeight() - radius)
			circlePos.y = GetScreenHeight() - radius;
	}

public:
	Vector2 circlePos;
	Vector2 targetPos;
	const float moveSpeed = 200.0f;
	const float radius = 20.0f;

	Hero()
	{
		circlePos = {300, 250};
		targetPos = circlePos;
	}

	void Update()
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			targetPos = GetMousePosition();

		// Represents the difference between the two vectors.
		Vector2 direction = Vector2Subtract(targetPos, circlePos);

		// Calculates the length of the vector using the Pythagorean theorem.
		float distance = Vector2Length(direction);

		// If the distance is greater than 0, move the circle towards the target position
		if (distance > 0)
		{
			// Scale the direction vector to move at a constant speed
			direction = Vector2Scale(direction, moveSpeed * GetFrameTime() / distance);

			// Update the circle's position
			circlePos = Vector2Add(circlePos, direction);

			limitMovement();
		}
	}

	void Draw()
	{
		DrawCircleV(circlePos, radius, BLUE);
	}
};

int main()
{
	InitWindow(600, 500, "Move the circle");

	SetTargetFPS(60);

	Hero hero;

	while (!WindowShouldClose())
	{
		hero.Update();

		BeginDrawing();

		ClearBackground(BLACK);
		hero.Draw();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
