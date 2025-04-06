// Love Proposal Animation with Happy Jump Effects
#include <raylib.h>
#include <cmath>

// Global variables for Happy jump
float happyJumpOffset = 0.0f;
bool goingUp = true;

void HappyEffects(float posX, float posY, float happyJumpOffset)
{
    // Larger, more visible blush effects
    DrawCircle(posX - 7, posY + 3 + happyJumpOffset, 4, PINK);
    DrawCircle(posX + 7, posY + 3 + happyJumpOffset, 4, PINK);

    // Add slight gradient effect
    DrawCircle(posX - 7, posY + 3 + happyJumpOffset, 2, RED);
    DrawCircle(posX + 7, posY + 3 + happyJumpOffset, 2, RED);

    // Draw Floating Hearts
    DrawCircle(posX - 20, posY - 10 + happyJumpOffset, 3, PINK);
    DrawCircle(posX + 20, posY - 10 + happyJumpOffset, 3, PINK);
    DrawCircle(posX - 15, posY - 20 + happyJumpOffset, 2, RED);
    DrawCircle(posX + 15, posY - 20 + happyJumpOffset, 2, RED);
}

void UpdateHappyJump()
{
    if (goingUp)
    {
        happyJumpOffset -= 60 * GetFrameTime();
        if (happyJumpOffset < -20)
            goingUp = false;
    }
    else
    {
        happyJumpOffset += 60 * GetFrameTime();
        if (happyJumpOffset > 0)
        {
            happyJumpOffset = 0;
            goingUp = true;
        }
    }
}

void DrawHappyGirl(float posX, float posY, float happyJumpOffset, Color color)
{
    // Head
    DrawCircle(posX, posY + happyJumpOffset, 10, color);

    // Body
    DrawLine(posX, posY + 10 + happyJumpOffset, posX, posY + 30 + happyJumpOffset, color);

    // Waving arms
    DrawLine(posX, posY + 15 + happyJumpOffset, posX - 15, posY + 10 + happyJumpOffset, color);
    DrawLine(posX, posY + 15 + happyJumpOffset, posX + 15, posY + 10 + happyJumpOffset, color);

    // Happy legs
    DrawLine(posX, posY + 30 + happyJumpOffset, posX - 7, posY + 40 + happyJumpOffset, color);
    DrawLine(posX, posY + 30 + happyJumpOffset, posX + 7, posY + 40 + happyJumpOffset, color);
}

void DrawHappyEffects(float posX, float posY)
{
    UpdateHappyJump();

    Color color = MAGENTA;

    DrawHappyGirl(posX, posY, happyJumpOffset, color);

    HappyEffects(posX, posY, happyJumpOffset);
}

void DrawGirlIdle(float posX, float posY)
{
    Color color = MAGENTA;

    // Head
    DrawCircle(posX, posY, 10, color);

    // Body
    DrawLine(posX, posY + 10, posX, posY + 30, color);

    // Arms
    DrawLine(posX, posY + 15, posX - 10, posY + 20, color);
    DrawLine(posX, posY + 15, posX + 10, posY + 20, color);

    // Legs
    DrawLine(posX, posY + 30, posX - 5, posY + 45, color);
    DrawLine(posX, posY + 30, posX + 5, posY + 45, color);
}

void DrawWalkingPerson(float posX, float posY, float walkTime, bool hasFlower)
{
    float legMove = sin(walkTime * 8) * 5;

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

    if (hasFlower)
    {
        DrawLine(posX + 10, posY + 18, posX + 10, posY + 10, DARKGREEN);
        DrawCircle(posX + 10, posY + 7, 3, RED);
        DrawCircle(posX + 7, posY + 10, 3, RED);
        DrawCircle(posX + 13, posY + 10, 3, RED);
        DrawCircle(posX + 10, posY + 13, 3, RED);
        DrawCircle(posX + 10, posY + 10, 2, YELLOW);
    }
}

void UpdateWalking(float &walkTime, float &posX, const int sWidth, bool &isProposing, float girlX)
{
    if (!isProposing)
    {
        walkTime += GetFrameTime();
        posX += 50 * GetFrameTime(); // Walking speed

        if (posX >= girlX - 40)
        {
            isProposing = true;
        }

        if (posX > sWidth + 50)
            posX = -50;
    }
}

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Love Proposal Animation");
    SetTargetFPS(60);

    float posX = 100;
    float posY = 305;
    float walkTime = 0.0f;

    float girlX = 600;
    float girlY = 305;

    bool isProposing = false;

    while (!WindowShouldClose())
    {
        UpdateWalking(walkTime, posX, screenWidth, isProposing, girlX);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangle(0, 350, screenWidth, 100, GREEN); // Ground

        if (isProposing)
        {
            DrawHappyEffects(girlX, girlY);
            DrawText("I love you!", screenWidth / 2 - 70, 80, 50, RED);
        }
        else
        {
            DrawGirlIdle(girlX, girlY);
        }

        DrawWalkingPerson(posX, posY, walkTime, true);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
