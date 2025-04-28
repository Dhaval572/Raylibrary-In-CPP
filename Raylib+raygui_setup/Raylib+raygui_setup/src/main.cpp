#define RAYGUI_IMPLEMENTATION
#include <raylib.h>
#include <raygui.h>

int main()
{
    InitWindow(800, 600, " ");

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Update
        BeginDrawing();
        ClearBackground(BLUE);

        // Draw

        EndDrawing();
    }

    CloseWindow();
    return 0;
}