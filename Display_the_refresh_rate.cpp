#include <raylib.h>

int main()
{
    InitWindow(500, 500, "Refresh Rate");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        DrawText(TextFormat("Refresh Rate: %d Hz", GetMonitorRefreshRate(0)), 10, 10, 20, GREEN);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
