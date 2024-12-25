// Find the fps in graphics window
#include <raylib.h>

int main()
{
    InitWindow(600, 500, "FPS Counter");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        int fps = GetFPS(); //  GetFPS() returns fps
        DrawText(TextFormat("FPS: %i", fps), 10, 10, 30, GREEN);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
