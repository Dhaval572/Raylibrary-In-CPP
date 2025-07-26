#pragma once
#include "Fire_partical.h"

constexpr float JUMP_VELOCITY = -9.0f;
constexpr float GRAVITY = 0.6f;
constexpr float TERMINAL_VELOCITY = 15.0f;
constexpr float MAX_HEALTH_POINT = 100;

class Stickman
{
    Vector2 position;
    Color color;
    float walkTime;
    float verticalVelocity;
    float groundLevel;
    float damageCooldown;
    float currHealth;
    float displayHealth;
    bool isMoving;
    bool isLookingRight;
    bool isJumping;
    bool isSneaking;
    bool isAlive;

    Rectangle Rect() const;
    void DrawHealthBar();

public:
    void TakeDamageFromFire(const Fire &fire);
    void Update();
    void SmoothHealthTransition();
    void Draw();
    void Reset(Vector2 pos, Color col);
    bool IsAlive() const;
};