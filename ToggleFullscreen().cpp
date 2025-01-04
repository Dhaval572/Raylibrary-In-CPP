// ToggleFullscreen() and use of IsKeyReleased()
#include <raylib.h>

int main()
{
    InitWindow(1200, 700, "Toggle Example");

    SetTargetFPS(60);

    bool isFullscreen = false;
    while (!WindowShouldClose())
    {
        // Check if the F key is released to toggle fullscreen mode
        if (IsKeyReleased(KEY_F))
        {
            isFullscreen = !isFullscreen; // Toggle fullscreen
            if (isFullscreen)
                ToggleFullscreen();
            else
                ToggleFullscreen();
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (isFullscreen)
            DrawText("Fullscreen mode!", 10, 10, 20, GREEN);
        else
            DrawText("Windowed mode", 10, 10, 20, RED);

        EndDrawing();
    }

    CloseWindow(); 
    return 0;
}
