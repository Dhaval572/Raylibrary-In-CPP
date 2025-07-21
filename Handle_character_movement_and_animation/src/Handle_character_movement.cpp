#include "Handle_character_movement.hpp"

Character::Character(const string &pattern, int count, float speed)
	: position({10.0f, 300.0f}), timer(0.0f), frameSpeed(speed), currentFrame(0)
{
	frames.reserve(count);
	for (int i = 1; i <= count; ++i)
	{
		string path(pattern);
		path.replace(path.find("{}"), 2, to_string(i));
		frames.emplace_back(LoadTexture(path.c_str()));
	}
}

void Character::Animate()
{
	timer += GetFrameTime();
	if (timer >= frameSpeed)
	{
		timer = 0.0f;
		currentFrame = (currentFrame + 1) % frames.size();
	}
}

void Character::HandleMovement()
{
	if (IsKeyDown(KEY_RIGHT))
	{
		isFacingRight = true;
		Character::Animate();
		position.x += 4;

		if (position.x + 11.5f > GetScreenWidth())
			position.x = GetScreenWidth() - 11.5f;
	}

	if (IsKeyDown(KEY_LEFT))
	{
		isFacingRight = false;
		Character::Animate();
		position.x -= 4;

		if (position.x < 11.5f)
			position.x = 11.5f;
	}
}

void Character::Draw()
{
	const Texture2D &tex = frames[currentFrame];

	DrawTexturePro
	(
		tex,
		(Rectangle)
		{
			0.0f, 0.0f,
			!isFacingRight ? -(static_cast<float>(tex.width)) : static_cast<float>(tex.width),
			static_cast<float>(tex.height)
		},

		(Rectangle)
		{
			position.x, position.y,
			static_cast<float>(tex.width),
			static_cast<float>(tex.height)
		},

		(Vector2)
		{
			static_cast<float>(tex.width) * 0.5f,
			static_cast<float>(tex.height) * 0.5f
		},
		0.0f,
		WHITE
	);
}

Character::~Character()
{
	for (auto &tex : frames)
		UnloadTexture(tex);
}