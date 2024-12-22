// Make retro paddle game
#include <raylib.h>

// Colors for game
Color Green = Color{38, 185, 154, 255};
Color Dark_Green = Color{20, 160, 133, 255};
Color Light_Green = Color{129, 204, 184, 255};
Color Yellow = Color{243, 213, 91, 255};

// Scores
int playerScore = 0;
int botScore = 0;

class Ball
{
public:
	float ballX, ballY;
	int xSpeed, ySpeed;
	int radius;

	void drawBall()
	{
		DrawCircle(ballX, ballY, radius, Yellow);
	}

	void updateBallPos()
	{
		ballX += xSpeed;
		ballY += ySpeed;

		// If ball gone off screen ( at up or down side )
		if (ballY + radius >= GetScreenHeight() || ballY - radius <= 0)
		{
			ySpeed *= -1;
		}

		// If ball gone off screem ( at left or right side )
		if (ballX + radius >= GetScreenWidth()) // Bot wins
		{
			botScore++;
			resetTheBall();
		}

		if (ballX - radius <= 0) // Player wins
		{
			playerScore++;
			resetTheBall();
		}
	}

	void resetTheBall()
	{
		ballX = GetScreenWidth() / 2;
		ballY = GetScreenHeight() / 2;

		// Assign ball moving direction randomly either -1 or 1
		int speedchoices[2] = {-1, 1};
		xSpeed *= speedchoices[GetRandomValue(0, 1)];
		ySpeed *= speedchoices[GetRandomValue(0, 1)];
	}
};

Ball ball; // Creating a ball object

class Paddle
{
protected:
	void limitMovementOfpaddle()
	{
		// If paddle gone off the screen at up side
		if (paddleY <= 0)
			paddleY = 0;

		// If paddle gone off the screen at up side
		if (paddleY + height >= GetScreenHeight())
			paddleY = GetScreenHeight() - height;
	}

public:
	float paddleX, paddleY;
	float width, height;
	int speed;

	void drawPaddle()
	{
		DrawRectangleRounded(Rectangle{paddleX, paddleY, width, height}, 0.8, 0, WHITE);
	}

	void updateThePlayerPaddle()
	{
		if (IsKeyDown(KEY_UP))
			paddleY -= speed; // Move the paddle up

		if (IsKeyDown(KEY_DOWN))
			paddleY += speed; // Move the paddle down

		limitMovementOfpaddle();
	}
};

Paddle player; // Crating the player paddle object

class BotPaddle : public Paddle
{
public:
	void updateTheBotPaddle(int ballY)
	{
		// If paddle middle is greater than ball middle
		if (paddleY + height / 2 > ballY)
			paddleY -= speed; // Move up the paddle of bot

		// If paddle middle is less than or equal to ball middle
		if (paddleY + height / 2 <= ballY)
			paddleY += speed; // Move down the paddle of bot

		limitMovementOfpaddle();
	}
};

BotPaddle bot; // Creating the bot paddle object

int main()
{
	const int sWidth = 800, sHeight = 600;
	InitWindow(sWidth, sHeight, "Retro Paddle");

	// Ball properties
	ball.radius = 20;
	ball.ballX = sWidth / 2;
	ball.ballY = sHeight / 2;
	ball.xSpeed = 7;
	ball.ySpeed = 7;

	// Player properties
	player.width = 25;
	player.height = 100;
	player.paddleX = sWidth - player.width - 10;
	player.paddleY = sHeight / 2 - player.height / 2;
	player.speed = 8;

	// Bot properties
	bot.width = 25;
	bot.height = 100;
	bot.paddleX = 10;
	bot.paddleY = sWidth / 2 - bot.height / 2;
	bot.speed = 8;

	SetTargetFPS(60);

	// Main game loop
	while (!WindowShouldClose())
	{
		BeginDrawing();

		// Updating objects
		ball.updateBallPos();
		player.updateThePlayerPaddle();
		bot.updateTheBotPaddle(ball.ballY);

		// Checking for collision ( player paddle )
		if (CheckCollisionCircleRec(Vector2{ball.ballX, ball.ballY}, ball.radius, Rectangle{player.paddleX, player.paddleY, player.width, player.height}))
		{
			ball.xSpeed *= -1;
		}

		// Checking for collision ( bot paddle )
		if (CheckCollisionCircleRec(Vector2{ball.ballX, ball.ballY}, ball.radius, Rectangle{bot.paddleX, bot.paddleY, bot.width, bot.height}))
		{
			ball.xSpeed *= -1;
		}

		ClearBackground(Dark_Green);

		DrawRectangle(sWidth / 2, 0, sWidth / 2, sHeight, Green);
		DrawCircle(sWidth / 2, sHeight / 2, 100, Light_Green);
		DrawLine(sWidth / 2, 0, sWidth / 2, sHeight, WHITE); // Separate two parts

		// Drawing objects
		ball.drawBall();
		bot.drawPaddle();
		player.drawPaddle();

		// Display the score
		DrawText(TextFormat("%i", botScore), sWidth / 4 - 20, 20, 80, WHITE);
		DrawText(TextFormat("%i", playerScore), 3 * sWidth / 4 - 20, 20, 80, WHITE);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
