#pragma once
#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

constexpr float SKIDMARK_LIFETIME = 3.0f;

struct Skidmark
{
	Vector2 Tires[2];
	double creationTime;
};

class Car
{
public:
	Car(Vector2 startPosition, const string &texturePath);
	~Car();
	Vector2 GetPosition() const;
	void Update(float deltaTime);
	void Draw() const;

private:
	vector<Skidmark> skidmarks;
	Vector2 position;
	Vector2 size;
	Texture2D texture;
	float speed;
	float angle;
	float steering;
	float driftAngle;
	float maxSpeed;
	float acceleration;
	float slowdown;
	float steeringSpeed;
	float maxSteering;
	float steerBackSpeed;
	float driftBias;
	bool boost;

	Vector2 CalculateTirePosition(float offsetAngle) const;
	void InitializeCarProperties();
	void HandleInput(float deltaTime);
	void DrawCar() const;
	void DrawSkidmarks() const;
	void RemoveOldSkidmarks();
	void UpdateSkidmarks();
	void UpdatePhysics(float deltaTime);
	bool IsDrifting() const;
};