#include "Car.hpp"

Car::Car(Vector2 startPosition, const string &texturePath)
	: position(startPosition), texture(LoadTexture(texturePath.c_str()))
{
	InitializeCarProperties();
}

Car::~Car()
{
	UnloadTexture(texture);
}

void Car::Update(const float deltaTime)
{
	HandleInput(deltaTime);
	UpdatePhysics(deltaTime);
	UpdateSkidmarks();
}

void Car::Draw() const
{
	DrawSkidmarks();
	DrawCar();
}

Vector2 Car::GetPosition() const
{
	return position;
}

Vector2 Car::CalculateTirePosition(float offsetAngle) const
{
	const float radians = (angle + offsetAngle) * DEG2RAD;
	return {position.x + (size.y / 2.6f) * cos(radians),
			position.y + (size.y / 2.6f) * sin(radians)};
}

void Car::InitializeCarProperties()
{
	size = {80.0f, 150.0f};
	speed = 0.0f;
	angle = 0.0f;
	steering = 0.0f;
	driftAngle = 0.0f;
	maxSpeed = 700.0f;
	acceleration = 1150.0f;
	slowdown = 0.98f;
	steeringSpeed = 1.1f;
	maxSteering = 5.0f;
	steerBackSpeed = 0.1f;
	driftBias = 15.0f;
}

void Car::HandleInput(float deltaTime)
{
	if (IsKeyDown(KEY_W))
	{
		speed = min(speed + acceleration * deltaTime, maxSpeed);
	}

	else if (IsKeyDown(KEY_S))
	{
		speed = max(speed - acceleration * deltaTime, -maxSpeed);
	}

	else
	{
		speed *= slowdown;
	}

	if (IsKeyDown(KEY_A))
	{
		steering = max(steering - steeringSpeed * deltaTime * abs(speed), -maxSteering);
	}

	else if (IsKeyDown(KEY_D))
	{
		steering = min(steering + steeringSpeed * deltaTime * abs(speed), maxSteering);
	}

	steering *= (1 - steerBackSpeed);
}

void Car::DrawCar() const
{
	const Rectangle destRect = {position.x, position.y, size.x, size.y};
	const Vector2 origin = {size.x / 2, size.y / 2};

	DrawTexturePro(texture, {0, 0, (float)texture.width, (float)texture.height},
				   destRect, origin, angle, WHITE);
}

void Car::DrawSkidmarks() const
{
	for (const auto &skidmark : skidmarks)
	{
		DrawCircleV(skidmark.Tires[0], 6, BLACK);
		DrawCircleV(skidmark.Tires[1], 6, BLACK);
	}
}

void Car::RemoveOldSkidmarks()
{
	const double currentTime = GetTime();
	skidmarks.erase(remove_if(skidmarks.begin(), skidmarks.end(),
							  [currentTime](const auto &skidmark)
							  {
								  return currentTime > skidmark.creationTime + SKIDMARK_LIFETIME;
							  }),
					skidmarks.end());
}

void Car::UpdateSkidmarks()
{
	if (IsDrifting())
	{
		skidmarks.push_back({CalculateTirePosition(-240), CalculateTirePosition(-300), GetTime()});
	}
	RemoveOldSkidmarks();
}

void Car::UpdatePhysics(float deltaTime)
{
	angle += steering;
	driftAngle = (angle + driftAngle * driftBias) / (1 + driftBias);

	const float radians = (angle - 90) * DEG2RAD;
	position.x += speed * deltaTime * cos(radians);
	position.y += speed * deltaTime * sin(radians);
}

bool Car::IsDrifting() const
{
	return abs(driftAngle - angle) > 30 && abs(speed) > 50;
}