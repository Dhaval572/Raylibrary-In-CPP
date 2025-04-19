// Walking character animation
#include <raylib.h>
#include <cmath>

void DrawWalkingPerson(float posX, float posY, float walkTime)
{
    float legMove = sin(walkTime * 8) * 5; // Leg swinging animation

    // Head
    DrawCircle(posX, posY, 10, BLUE);

    // Body
    DrawLine(posX, posY + 10, posX, posY + 30, BLUE);

    // Arms
    DrawLine(posX, posY + 15, posX - 10, posY + 20, BLUE);
    DrawLine(posX, posY + 15, posX + 10, posY + 20, BLUE);

    // Legs
    DrawLine(posX, posY + 30, posX - 5 + legMove, posY + 45, BLUE);
    DrawLine(posX, posY + 30, posX + 5 - legMove, posY + 45, BLUE);
}

void UpdateWalking(float &walkTime, float& posX, const int sWidth)
{
    walkTime += GetFrameTime();
    posX += 50 * GetFrameTime();

    if (posX > sWidth + 50)
        posX = -50;
}

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Simple Walking Person");
    SetTargetFPS(60);

    float posX = 100;
    float posY = 305;
    float walkTime = 0.0f;

    while (!WindowShouldClose())
    {
        UpdateWalking(walkTime, posX, screenWidth);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangle(0, 350, screenWidth, 100, GREEN);
        DrawWalkingPerson(posX, posY, walkTime);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
