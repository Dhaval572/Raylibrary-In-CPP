// Check the response time
#include <raylib.h>

int main()
{
    InitWindow(600, 500, "Response time check");
    
    SetTargetFPS(60);

    bool start = false;
    bool colorChanged = false;
    float startTime = 0.0f;
    float endTime = 0.0f;
    float responseTime = 0.0f;
    int delay = 0;

    while (!WindowShouldClose())
    {
        if (!start)
        {
            if (IsKeyPressed(KEY_SPACE))
            {
                start = true;
                colorChanged = false;
                responseTime = 0.0f;
                delay = GetRandomValue(1, 5); // Random delay between 1 to 5 seconds
                startTime = GetTime();
            }
        }
        else 
        {
            if (!colorChanged && (GetTime() - startTime) >= delay)
            {
                colorChanged = true;
                startTime = GetTime(); // Reset start time to measure response time
            }

            if (colorChanged && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                endTime = GetTime();

                // ( Note: endTime - startTime = time in second )
                responseTime = (endTime - startTime) * 1000.0f; // Convert to milliseconds
                start = false;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        if (!start)
        {
            DrawText("Press SPACE to start", 150, 200, 20, GREEN);
            if (responseTime > 0.0f)
            {
                DrawText(TextFormat("Response Time: %.0f ms", responseTime), 150, 250, 20, PURPLE);
            }
        }
        else
        {
            if (!colorChanged)
            {
                DrawText("Wait for it...", 200, 200, 20, BLUE);
            }
            else
            {
                ClearBackground(RED);
                DrawText("Click Now!", 180, 200, 20, BLACK);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
