// Add delay in raylib 
#include <raylib.h>

void Delay(float seconds)
{
    float startTime = GetTime();
    while (GetTime() - startTime < seconds)
    {
        // Do nothing, just wait
    }
}

int main()
{
    InitWindow(600, 500, "Window with Delay");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Waiting for 2 seconds...", 150, 200, 20, DARKGRAY);
        EndDrawing();

        Delay(2.0f); // Delay for 2 seconds

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("2 seconds passed!", 150, 200, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
