#pragma once
#include <array>
#include <algorithm>
#include <raylib.h>
#include <raymath.h>

struct Particle
{
	Vector2 position;
	Vector2 velocity;
	Color color;
	float lifetime;
	float age;
	float size;
	bool alive;
};

class Fire
{
private:
	std::array<Particle, 80> particles;
	Vector2 emitter;
	float spawn_timer;

	Color GetFireColor(float age_ratio);
	float Lerp(float a, float b, float t);
	void SpawnParticle(Particle &p);

public:

	Rectangle Rect() const;
	void Reset(Vector2 emitterPos);
	void Update(float dt);
	void Draw();
};