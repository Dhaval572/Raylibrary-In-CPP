#include "SpriteAnimation.hpp"
using namespace std;

SpriteAnimation::SpriteAnimation(const string &pattern, int count, float speed)
	: currentFrame(0), timer(0.0f), frameSpeed(speed)
{
	frames.reserve(count);
	for (int i = 1; i <= count; ++i)
	{
		string path = pattern;
		path.replace(path.find("{}"), 2, to_string(i));
		frames.emplace_back(LoadTexture(path.c_str()));
	}
}

SpriteAnimation::~SpriteAnimation()
{
	for (auto &tex : frames)
	{
		UnloadTexture(tex);
	}
}

void SpriteAnimation::Update()
{
	timer += GetFrameTime();
	if (timer >= frameSpeed)
	{
		timer = 0.0f;
		currentFrame = (currentFrame + 1) % frames.size(); // Updates the current frame
	}
}

void SpriteAnimation::Draw(Vector2 position) const
{
	const Texture2D &tex = frames[currentFrame];
	DrawTexture(tex,
				static_cast<int>(position.x - tex.width / 2),
				static_cast<int>(position.y - tex.height / 2),
				WHITE);
}
