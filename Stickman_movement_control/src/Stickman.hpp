#pragma once
#include <raylib.h>
#include <cmath>
// #include "Fire_ball.hpp"

#define JUMP_VELOCITY -9.0f
#define GRAVITY 0.6f
#define TERMINAL_VELOCITY 15.0f

class Stickman
{
    Vector2 position;
    const Color color;
    float walkTime;
    float verticalVelocity;
    float groundLevel;
    bool isMoving;
    bool isLookingRight;
    bool isJumping;
    bool isSneaking;

public:
    Stickman(Vector2 pos, Color col);
    void Update();
    void Draw();
};