#pragma once

#include <raylib.h>
#include <vector>
#include <string>
using namespace std;

class Character
{
public:
	Character(const string &pattern, int count, float speed);
	~Character();
	void Animate();
	void HandleMovement();
	void Draw();

private:
	vector<Texture2D> frames;
	Vector2 position;
	float timer;
	float frameSpeed;
	int currentFrame;
	bool isFacingRight;
};