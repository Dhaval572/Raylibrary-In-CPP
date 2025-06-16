#pragma once
#include "Fire_partical.h"

constexpr float JUMP_VELOCITY = -9.0f;
constexpr float GRAVITY = 0.6f;
constexpr float TERMINAL_VELOCITY = 15.0f;
constexpr _Float16 MAX_HEALTH_POINT = 100;

class Stickman
{
    Vector2 position;
    Color color;
    float walkTime;
    float verticalVelocity;
    float groundLevel;
    float damageCooldown;
    _Float16 currHealth;
    bool isMoving;
    bool isLookingRight;
    bool isJumping;
    bool isSneaking;
    bool isAlive;

    void DrawHealthBar();
    Rectangle Rect() const;

public:
    void TakeDamage(const Fire &fire);
    void Update();
    void Draw();
    void Reset(Vector2 pos, Color col);
    bool IsAlive() const;
};