#pragma once
#include <raylib.h>
#define JUMP_VELOCITY -9.0f
#define GRAVITY 0.6f
#define TERMINAL_VELOCITY 15.0f

class Stickman
{
    Vector2 position;
    Color color;
    float walkTime;
    float verticalVelocity;
    float groundLevel;
    bool isMoving;
    bool isLookingRight;
    bool isJumping;

public:
    Stickman(Vector2 pos, Color col);
    void Update();
    void Draw();
};