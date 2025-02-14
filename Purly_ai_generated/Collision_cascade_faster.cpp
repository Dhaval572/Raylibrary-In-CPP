#include <raylib.h>
#include <stdio.h>
#include <math.h>

#define MAX_BALLS 15
#define PROJECT_NAME "Collision Cascade"
#define DEACTIVATION_THRESHOLD 2.5f
#define GROUND_FRICTION 0.93f
#define WALL_FRICTION 0.85f

typedef struct Ball
{
    Vector2 position;
    Vector2 velocity;
    float radius;
    Color color;
    bool active;
    bool was_active; // For tracking state changes
} Ball;

// Function prototypes
void ResolveBallCollision(Ball *ball1, Ball *ball2);
void UpdateBallPhysics(Ball *ball, float gravity, float friction, float groundLevel, int screenWidth, int screenHeight);
void InitializeBalls(Ball balls[], int screenWidth, int screenHeight);
void ResetBalls(Ball balls[], int screenWidth, int screenHeight);
void DrawActiveCounter(int activeCount, int screenWidth);
void DrawCompletionMessage(int screenWidth, int screenHeight);

// Collision resolution
void ResolveBallCollision(Ball *ball1, Ball *ball2)
{
    Vector2 delta = {ball2->position.x - ball1->position.x,
                     ball2->position.y - ball1->position.y};
    float distance = sqrtf(delta.x * delta.x + delta.y * delta.y);
    float minDistance = ball1->radius + ball2->radius;

    if (distance < minDistance)
    {
        Vector2 normal = {delta.x / distance, delta.y / distance};
        float overlap = (minDistance - distance) / 2.0f;

        // Position correction
        ball1->position.x -= normal.x * overlap;
        ball1->position.y -= normal.y * overlap;
        ball2->position.x += normal.x * overlap;
        ball2->position.y += normal.y * overlap;

        // Elastic collision response
        Vector2 relativeVelocity = {ball1->velocity.x - ball2->velocity.x,
                                    ball1->velocity.y - ball2->velocity.y};
        float velocityAlongNormal = relativeVelocity.x * normal.x + relativeVelocity.y * normal.y;

        if (velocityAlongNormal > 0)
            return;

        float restitution = 0.8f;
        float impulse = (-(1.0f + restitution) * velocityAlongNormal) /
                        (1.0f / ball1->radius + 1.0f / ball2->radius);

        ball1->velocity.x += impulse * normal.x / ball1->radius;
        ball1->velocity.y += impulse * normal.y / ball1->radius;
        ball2->velocity.x -= impulse * normal.x / ball2->radius;
        ball2->velocity.y -= impulse * normal.y / ball2->radius;
    }
}

// Physics update with proper state tracking
void UpdateBallPhysics(Ball *ball, float gravity, float friction,
                       float groundLevel, int screenWidth, int screenHeight)
{
    if (!ball->active)
        return;

    ball->was_active = ball->active;

    // Apply forces
    ball->velocity.y += gravity;
    ball->position.x += ball->velocity.x;
    ball->position.y += ball->velocity.y;

    // Ground collision
    if (ball->position.y + ball->radius >= groundLevel)
    {
        ball->position.y = groundLevel - ball->radius;
        ball->velocity.y *= -0.7f;
        ball->velocity.x *= GROUND_FRICTION;
    }

    // Ceiling collision
    if (ball->position.y - ball->radius <= 0)
    {
        ball->position.y = ball->radius;
        ball->velocity.y *= -0.7f;
    }

    // Wall collisions
    if (ball->position.x - ball->radius <= 0)
    {
        ball->position.x = ball->radius;
        ball->velocity.x *= -WALL_FRICTION;
    }
    if (ball->position.x + ball->radius >= screenWidth)
    {
        ball->position.x = screenWidth - ball->radius;
        ball->velocity.x *= -WALL_FRICTION;
    }

    // Air resistance
    ball->velocity.x *= friction;

    // Speed-based deactivation
    float speed_sq = ball->velocity.x * ball->velocity.x +
                     ball->velocity.y * ball->velocity.y;
    if (speed_sq < DEACTIVATION_THRESHOLD * DEACTIVATION_THRESHOLD)
    {
        ball->active = false;
    }
}

// Ball initialization with better spread
void InitializeBalls(Ball balls[], int screenWidth, int screenHeight)
{
    for (int i = 0; i < MAX_BALLS; i++)
    {
        balls[i] = (Ball){
            .position = {screenWidth / 2.0f + GetRandomValue(-150, 150),
                         (float)GetRandomValue(-screenHeight, -50)},
            .velocity = {(float)GetRandomValue(-250, 250),
                         (float)GetRandomValue(150, 400)},
            .radius = (float)(int(15)) + GetRandomValue(0, 15),
            .color = ColorFromHSV(GetRandomValue(0, 360), 0.9f, 0.9f),
            .active = true,
            .was_active = true};
    }
}

void ResetBalls(Ball balls[], int screenWidth, int screenHeight)
{
    InitializeBalls(balls, screenWidth, screenHeight);
}

// Drawing functions
void DrawActiveCounter(int activeCount, int screenWidth)
{
    char counterText[32];
    snprintf(counterText, sizeof(counterText), "Active Balls: %d", activeCount);
    Vector2 textSize = MeasureTextEx(GetFontDefault(), counterText, 24, 2);
    DrawRectangle(10, 10, textSize.x + 20, textSize.y + 10, Fade(BLACK, 0.5f));
    DrawText(counterText, 20, 15, 24, RAYWHITE);
}

void DrawCompletionMessage(int screenWidth, int screenHeight)
{
    const char *text = "SIMULATION COMPLETE - PRESS R TO RESTART";
    Vector2 textSize = MeasureTextEx(GetFontDefault(), text, 36, 2);
    DrawRectangle(0, screenHeight / 2 - 40, screenWidth, 80, Fade(BLACK, 0.7f));
    DrawText(text, (screenWidth - textSize.x) / 2, screenHeight / 2 - 20, 36, RAYWHITE);
}

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, PROJECT_NAME);
    SetTargetFPS(144);

    Ball balls[MAX_BALLS];
    InitializeBalls(balls, screenWidth, screenHeight);
    const float groundLevel = screenHeight - 60;
    bool allInactive = false;

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_R))
            ResetBalls(balls, screenWidth, screenHeight);

        // Physics update
        for (int i = 0; i < MAX_BALLS; i++)
        {
            if (balls[i].active)
            {
                UpdateBallPhysics(&balls[i], 0.8f, 0.99f,
                                  groundLevel, screenWidth, screenHeight);
            }
        }

        // Collision detection
        for (int i = 0; i < MAX_BALLS; i++)
        {
            if (!balls[i].active)
                continue;
            for (int j = i + 1; j < MAX_BALLS; j++)
            {
                if (balls[j].active)
                {
                    ResolveBallCollision(&balls[i], &balls[j]);
                }
            }
        }

        // State validation
        allInactive = true;
        int activeCount = 0;
        for (int i = 0; i < MAX_BALLS; i++)
        {
            if (balls[i].active)
            {
                allInactive = false;
                activeCount++;
                // Force reactivation if position invalid
                if (balls[i].position.y < -100 || balls[i].position.y > screenHeight + 100)
                {
                    balls[i].active = false;
                }
            }
        }

        // Rendering
        BeginDrawing();
        ClearBackground((Color){25, 25, 35, 255});

        // Draw ground
        DrawRectangle(0, groundLevel, screenWidth, screenHeight - groundLevel,
                      ColorAlpha(LIGHTGRAY, 0.2f));

        // Draw balls
        for (int i = 0; i < MAX_BALLS; i++)
        {
            if (balls[i].active)
            {
                // Glow effect
                DrawCircleV(balls[i].position, balls[i].radius * 2.5f,
                            ColorAlpha(balls[i].color, 0.15f));
                // Main ball
                DrawCircleV(balls[i].position, balls[i].radius, balls[i].color);
                // Highlight
                DrawCircleV(balls[i].position, balls[i].radius * 0.6f,
                            ColorAlpha(WHITE, 0.2f));
            }
        }

        // UI elements
        if (!allInactive)
        {
            DrawActiveCounter(activeCount, screenWidth);
        }
        else
        {
            DrawCompletionMessage(screenWidth, screenHeight);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
