#pragma once
#include <array>
#include <algorithm>
#include <raylib.h>
#include <raymath.h>

struct Particle
{
	Vector2 position;
	Vector2 velocity;
	float lifetime;
	float age;
	float size;
	Color color;
	bool alive;
};

class Fire
{
private:
	std::array<Particle, 80> particles;
	Vector2 emitter;
	float spawnTimer;

	void SpawnParticle(Particle &p);
	float Lerp(float a, float b, float t);
	Color GetFireColor(float age_ratio);

public:

	void Reset(Vector2 emitterPos);
	void Update(float dt);
	void Draw();
	Rectangle Rect() const;
};