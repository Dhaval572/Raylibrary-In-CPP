// Aim practice
#include <raylib.h>

// To draw the crosshair
void drawCrosshair(int crosshairSize, Color crosshairColor)
{
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();

    // Horizontal line
    DrawLine(mouseX - crosshairSize, mouseY, mouseX + crosshairSize, mouseY, crosshairColor);

    // Vertical line
    DrawLine(mouseX, mouseY - crosshairSize, mouseX, mouseY + crosshairSize, crosshairColor);
}

int main()
{
    InitWindow(1200, 700, "Switching target");

    SetTargetFPS(60);

    int score = 0;
    const int gameTime = 30; // Time duration in second
    float timeRemaining = gameTime;

    Color backgroundColor = {255, 255, 255, 55};
    Vector2 targetPos = {(float)GetRandomValue(20, GetScreenWidth() - 20), (float)GetRandomValue(20, GetScreenHeight() - 20)};

    while (!WindowShouldClose())
    {
        timeRemaining -= GetFrameTime(); // update the timer
        BeginDrawing();

        if (timeRemaining > 0)
        {
            ClearBackground(backgroundColor);

            HideCursor();

            if (CheckCollisionPointCircle(GetMousePosition(), targetPos, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                // Spawn target at random position
                targetPos.x = GetRandomValue(20, GetScreenWidth() - 20);
                targetPos.y = GetRandomValue(20, GetScreenHeight() - 20);
                score++;
            }

            DrawCircle(targetPos.x, targetPos.y, 20, GREEN);
            drawCrosshair(5, BLACK);

            DrawText(TextFormat("Score: %i", score), 10, 10, 20, DARKBLUE);
            DrawText(TextFormat("Time: %.1f", timeRemaining), 10, 40, 20, DARKBLUE);
        }
        else // Game over
        {
            DrawText("GAME OVER", GetScreenWidth() / 2 - MeasureText("GAME OVER", 40) / 2, GetScreenHeight() / 2 - 20, 40, RED);

            DrawText(TextFormat("Your last score was: %i", score), GetScreenWidth() / 2 - MeasureText(TextFormat("Your last score was: %i", score), 20) / 2, GetScreenHeight() / 2 + 20, 20, GREEN);

            DrawText("Press escape to close", GetScreenWidth() / 2 - MeasureText(TextFormat("Your last score was: %i", score), 30) / 2, 200, 30, PURPLE);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
