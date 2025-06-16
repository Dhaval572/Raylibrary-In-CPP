#include "Fire_partical.h"

void Fire::Reset(Vector2 emitterPos)
{
	emitter = emitterPos;
	spawnTimer = 0.0f;

	for(auto &p : particles)
		p.alive = true;
}

void Fire::SpawnParticle(Particle &p)
{
	// Generally position of partical
	p.position.x = emitter.x + static_cast<float>(GetRandomValue(-15, 15));
	p.position.y = emitter.y + static_cast<float>(GetRandomValue(-5, 5));

	// Initial upward velocity with spread
	p.velocity.x = static_cast<float>(GetRandomValue(-40, 40)) / 100.0f;
	p.velocity.y = -1.2f - static_cast<float>(GetRandomValue(0, 60)) / 100.0f;

	p.lifetime = 1.0f + static_cast<float>(GetRandomValue(0, 100)) / 100.0f;
	p.age = 0.0f;
	p.size = 3.0f + static_cast<float>(GetRandomValue(0, 40)) / 10.0f;
	p.color = GetFireColor(0.0f);
	p.alive = true;
}

Rectangle Fire::Rect() const
{
	return Rectangle{
		emitter.x - 20, 
		emitter.y - 60, 
		40,				
		60				
	};
}

float Fire::Lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}

Color Fire::GetFireColor(float age_ratio)
{
	Color color;

	if (age_ratio < 0.3f)
	{
		// Yellow-white hot core
		float t = age_ratio / 0.3f;
		color.r = 255;
		color.g = static_cast<unsigned char>(Lerp(255, 200, t));
		color.b = static_cast<unsigned char>(Lerp(100, 0, t));
	}
	else if (age_ratio < 0.7f)
	{
		// Orange flame
		float t = (age_ratio - 0.3f) / 0.4f;
		color.r = 255;
		color.g = static_cast<unsigned char>(Lerp(200, 120, t));
		color.b = 0;
	}
	else
	{
		// Red ember
		float t = (age_ratio - 0.7f) / 0.3f;
		color.r = static_cast<unsigned char>(Lerp(255, 150, t));
		color.g = static_cast<unsigned char>(Lerp(120, 30, t));
		color.b = 0;
	}

	// Fade out over lifetime
	color.a = static_cast<unsigned char>(255 * (1.0f - age_ratio));

	return color;
}

void Fire::Update(float dt)
{
	// Spawn particles more frequently for density
	spawnTimer += dt;
	if (spawnTimer >= 0.015f)
	{
		spawnTimer = 0.0f;

		// Find dead particle to respawn
		for (auto &p : particles)
		{
			if (!p.alive)
			{
				SpawnParticle(p);
				break;
			}
		}
	}

	// Update existing particles
	for (auto &p : particles)
	{
		if (!p.alive)
			continue;

		p.age += dt;

		// Kill old particles
		if (p.age >= p.lifetime)
		{
			p.alive = false;
			continue;
		}

		float age_ratio = p.age / p.lifetime;

		// Realistic fire physics
		float buoyancy = 1.5f * (1.0f - age_ratio * 0.6f); // Strong upward force when young
		p.velocity.y -= buoyancy * dt;					   // Upward buoyancy
		p.velocity.y += 0.2f * dt;						   // Light downward gravity

		// Air resistance
		p.velocity.x *= 0.995f;
		p.velocity.y *= 0.996f;

		// Add slight turbulence
		float time_offset = p.age * 3.0f;
		p.velocity.x += sinf(time_offset) * 0.1f * dt;

		// Update position
		p.position.x += p.velocity.x * dt * 50.0f;
		p.position.y += p.velocity.y * dt * 50.0f;

		// Size evolution - expand then contract
		if (age_ratio < 0.2f)
		{
			// Expand phase
			p.size += dt * 8.0f;
		}
		else
		{
			// Contract phase
			p.size = Lerp(p.size, 0.5f, dt * 1.5f);
		}

		if (p.size < 0.8f)
			p.size = 0.8f;

		// Update color
		p.color = GetFireColor(age_ratio);
	}
}

void Fire::Draw()
{
	BeginBlendMode(BLEND_ADDITIVE);

	for (const auto &p : particles)
	{
		if (p.alive && p.color.a > 5)
		{
			DrawCircleV(p.position, p.size, p.color);

			// Draw soft glow
			Color glow = p.color;
			glow.a = static_cast<unsigned char>(glow.a * 0.3f);
			DrawCircleV(p.position, p.size * 1.8f, glow);
		}
	}

	EndBlendMode();

	// Debug coll rect
	// DrawRectangleLinesEx(Rect(), 1, RED);
}
