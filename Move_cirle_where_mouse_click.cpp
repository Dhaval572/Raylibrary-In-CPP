// Move the circle using mouse click
#include <raylib.h>
#include <raymath.h> // To use Vector2Subtract etc
int main()
{
	InitWindow(600, 500, "Move the circle");

	SetTargetFPS(60);

	Vector2 circlePos = {300, 250}; 
	Vector2 targetPos = circlePos; // Set target Position at circle position
	const float moveSpeed = 200.0f;

	while (!WindowShouldClose())
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			targetPos = GetMousePosition();

		// Interpolate the circle's position towards the target position
		Vector2 direction = Vector2Subtract(targetPos, circlePos);
		float distance = Vector2Length(direction);
		if (distance > 0)
		{
			direction = Vector2Scale(direction, moveSpeed * GetFrameTime() / distance);
			circlePos = Vector2Add(circlePos, direction);
		}

		BeginDrawing();

		ClearBackground(BLACK);

		DrawCircleV(circlePos, 20, BLUE);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
