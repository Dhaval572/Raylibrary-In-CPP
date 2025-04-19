#pragma once

#include <raylib.h>
#include <vector>
#include <string>
using namespace std;

class SpriteAnimation
{
public:
	SpriteAnimation(const string &pattern, int count, float speed);
	~SpriteAnimation();

	void Update();
	void Draw(Vector2 position) const;

private:
	vector<Texture2D> frames;
	int currentFrame;
	float timer;
	float frameSpeed;
};