// Bouncing ball animation
#include <raylib.h>

int main()
{
	InitWindow(600, 500, "Bouncing ball");

	int ballX = 100, ballY = 100, radius = 20;
	int xSpeed = 5, ySpeed = 5;

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		ballX += xSpeed;
		ballY += ySpeed;

		if (ballX > GetScreenWidth() - radius || ballX < radius)
			xSpeed = -xSpeed; // Move the ball to oposite x direction

		if (ballY > GetScreenHeight() - radius || ballY < radius)
			ySpeed = -ySpeed; // Move the ball to oposite y direction

		BeginDrawing();

		ClearBackground(BLACK);
		DrawCircle(ballX, ballY, radius, MAGENTA); 

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
