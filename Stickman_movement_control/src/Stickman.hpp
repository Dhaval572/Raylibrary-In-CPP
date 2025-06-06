#pragma once
#include <raylib.h>
#include <cmath>

constexpr float JUMP_VELOCITY = -9.0f;
constexpr float GRAVITY = 0.6f;
constexpr float TERMINAL_VELOCITY = 15.0f;
constexpr _Float16 MAX_HEALTH_POINT = 100;

class Stickman
{
    Vector2 position;
    const Color color;
    float walkTime;
    float verticalVelocity;
    float groundLevel;
    _Float16 currHealth;
    bool isMoving;
    bool isLookingRight;
    bool isJumping; 
    bool isSneaking;

    void DrawHealthBar();

public:

    Stickman(Vector2 pos, Color col);
    void Update();
    void Draw();
};