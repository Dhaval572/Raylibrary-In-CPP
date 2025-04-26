#pragma once
#include <raylib.h>

typedef struct
{
    Vector2 position;
    float radius, speed;
} Circle;

typedef struct
{
    Vector2 position, size;
    float speed;
} Rect;

// Move circle with arrow keys + bounds 
inline void MoveUsingArrowKeys(Circle* c, int w, int h)
{
    if (IsKeyDown(KEY_LEFT))  c->position.x -= c->speed;
    if (IsKeyDown(KEY_RIGHT)) c->position.x += c->speed;
    if (IsKeyDown(KEY_UP))    c->position.y -= c->speed;
    if (IsKeyDown(KEY_DOWN))  c->position.y += c->speed;

    if (c->position.x - c->radius < 0)        c->position.x = c->radius;
    if (c->position.x + c->radius > w)        c->position.x = w - c->radius;
    if (c->position.y - c->radius < 0)        c->position.y = c->radius;
    if (c->position.y + c->radius > h)        c->position.y = h - c->radius;
}

// Move rect with arrow keys + bounds 
inline void MoveUsingArrowKeys(Rect* r, int w, int h)
{
    if (IsKeyDown(KEY_LEFT))  r->position.x -= r->speed;
    if (IsKeyDown(KEY_RIGHT)) r->position.x += r->speed;
    if (IsKeyDown(KEY_UP))    r->position.y -= r->speed;
    if (IsKeyDown(KEY_DOWN))  r->position.y += r->speed;

    if (r->position.x < 0)              r->position.x = 0;
    if (r->position.x + r->size.x > w)  r->position.x = w - r->size.x;
    if (r->position.y < 0)              r->position.y = 0;
    if (r->position.y + r->size.y > h)  r->position.y = h - r->size.y;
}