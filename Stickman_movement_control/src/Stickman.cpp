#include "Stickman.hpp"

Stickman::Stickman(Vector2 pos, Color col)
	: position(pos), color(col), walkTime(0.0f)
{
	walkTime = false;
	isJumping = false;
	groundLevel = position.y;
}

void Stickman::Update()
{
	isMoving = false;
	isSneaking = false;

	if (IsKeyDown(KEY_DOWN))
	{
		isSneaking = true;
		if (!isJumping)
		{
			position.y += 8.0f;
			if (position.y > groundLevel + 8.0f)
				position.y = groundLevel + 8.0f;
		}
	}
	else if (!isJumping)
	{
		position.y = groundLevel;
	}

	if (IsKeyDown(KEY_RIGHT))
	{
		isLookingRight = true;
		isMoving = true;

		if (isSneaking)
			position.x += 1.0f;
		else
			position.x += 3.0f;
	}

	if (IsKeyDown(KEY_LEFT))
	{
		isLookingRight = false;
		isMoving = true;

		if (isSneaking)
			position.x -= 1.0f;
		else
			position.x -= 3.0f;
	}

	if (IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_RIGHT))
		isMoving = false;

	if (isMoving)
		walkTime += GetFrameTime();

	if (IsKeyPressed(KEY_SPACE) && !isJumping)
	{
		isJumping = true;
		verticalVelocity = JUMP_VELOCITY;
	}

	if (isJumping)
	{
		position.y += verticalVelocity;
		verticalVelocity += GRAVITY;

		// Clamp falling speed
		verticalVelocity = fminf(verticalVelocity, TERMINAL_VELOCITY);

		// Ground collision
		if (position.y >= groundLevel)
		{
			position.y = groundLevel;
			verticalVelocity = 0.0f;
			isJumping = false;
		}
	}

	// Boundary
	if (position.x < 10)
		position.x = 10; // 10 is head radius

	if (position.x > GetScreenWidth() - 10)
		position.x = GetScreenWidth() - 10;
}

void Stickman::Draw()
{
	float legMove = isMoving ? sin(walkTime * 8) * 5 : 0;

	// Head
	DrawCircle(position.x, position.y, 10, color);

	// Body
	DrawLine(position.x, position.y + 10, position.x, position.y + 30, color);

	// Eye
	if (isLookingRight)
		DrawCircle(position.x + 3, position.y - 2, 2, BLACK);
	else
		DrawCircle(position.x - 3, position.y - 2, 2, BLACK);

	if (isJumping && !isSneaking)
	{
		// Arms raised higher when jumping
		DrawLine(position.x, position.y + 15, position.x - 15, position.y + 10, color);
		DrawLine(position.x, position.y + 15, position.x + 15, position.y + 10, color);

		// Legs bent upward for jump pose
		DrawLine(position.x, position.y + 30, position.x - 10, position.y + 35, color);
		DrawLine(position.x, position.y + 30, position.x + 10, position.y + 35, color);
	}
	else if (isSneaking && !isJumping)
	{
		// Arms bent down for sneaking pose
		DrawLine(position.x, position.y + 15, position.x - 10, position.y + 25, color);
		DrawLine(position.x, position.y + 15, position.x + 10, position.y + 25, color);

		// Legs spread wider for sneaking pose
		DrawLine(position.x, position.y + 30, position.x - 15 + legMove, position.y + 45, color);
		DrawLine(position.x, position.y + 30, position.x + 15 - legMove, position.y + 45, color);
	}
	else
	{
		// Arms
		DrawLine(position.x, position.y + 15, position.x - 10, position.y + 20, color);
		DrawLine(position.x, position.y + 15, position.x + 10, position.y + 20, color);

		// Legs ( animated when moving )
		DrawLine(position.x, position.y + 30, position.x - 5 + legMove, position.y + 45, color);
		DrawLine(position.x, position.y + 30, position.x + 5 - legMove, position.y + 45, color);
	}

	// Ground
	DrawRectangle(0, 400, GetScreenWidth(), 100, GREEN);
}