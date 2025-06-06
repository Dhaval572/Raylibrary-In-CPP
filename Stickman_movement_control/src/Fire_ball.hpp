// #pragma once
// #include <stdint.h>
// #include <raylib.h>
// #include <vector>

// class FireParticle
// {
// public:

// 	Vector2 position;
// 	Vector2 velocity;
// 	Color color;
// 	float lifetime;
// 	float maxLifetime;

// 	FireParticle(Vector2 pos);
// 	void Update(float delta);
// 	bool IsDead() const;
// 	void Draw() const;
// };

// class Ball
// {
// public:
// 	std::vector<FireParticle> particles;
// 	Vector2 position;
// 	Vector2 velocity;
// 	Color color;
// 	bool active;
// 	uint8_t size;

// 	Ball(Vector2 startPos, Vector2 vel, uint8_t s, Color c);
// 	void Update(float delta);
// 	void Draw() const;
// 	void Deactivate();
// };
