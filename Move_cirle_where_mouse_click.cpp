// Move the circle via mouse click
#include <raylib.h>
#include <raymath.h> // To use Vector2Subtract etc

class Hero
{
public:
    Vector2 circlePos;
    Vector2 targetPos;
    const float moveSpeed = 200.0f;

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
		}
	}

    void Draw()
    {
        DrawCircleV(circlePos, 20, BLUE);
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
