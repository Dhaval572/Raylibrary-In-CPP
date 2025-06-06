// #include "Fire_ball.hpp"
// #include <algorithm>

// // FireParticle Implementation
// FireParticle::FireParticle(Vector2 pos)
// 	: position(pos),
// 	  velocity({GetRandomValue(-10, 10) / 10.0f, GetRandomValue(-10, 10) / 10.0f}),
// 	  lifetime(0),
// 	  maxLifetime(GetRandomValue(20, 40) / 10.0f),
// 	  color(ORANGE)
// {
// }

// void FireParticle::Update(float delta)
// {
// 	position.x += velocity.x;
// 	position.y += velocity.y;
// 	lifetime += delta;

// 	float alpha = 1.0f - (lifetime / maxLifetime);
// 	color.a = static_cast<unsigned char>(alpha * 255);
// }

// bool FireParticle::IsDead() const
// {
// 	return lifetime >= maxLifetime;
// }

// void FireParticle::Draw() const
// {
// 	DrawCircleV(position, 3, color);
// }

// // Ball Implementation
// Ball::Ball(Vector2 startPos, Vector2 vel, uint8_t s, Color c)
// 	: position(startPos), velocity(vel), size(s), color(c), active(true)
// {
// }

// void Ball::Update(float delta)
// {
// 	if (!active)
// 		return;

// 	position.x += velocity.x * delta;
// 	position.y += velocity.y * delta;

// 	// Generate fire trail
// 	particles.emplace_back(position);

// 	for (auto &p : particles)
// 		p.Update(delta);

// 	particles.erase(
// 		std::remove_if(particles.begin(), particles.end(),
// 					   [](const FireParticle &p)
// 					   { return p.IsDead(); }),
// 		particles.end());
// }

// void Ball::Draw() const
// {
// 	if (!active)
// 		return;

// 	for (const auto &p : particles)
// 		p.Draw();

// 	DrawCircleV(position, size, color);
// }

// void Ball::Deactivate()
// {
// 	active = false;
// }
