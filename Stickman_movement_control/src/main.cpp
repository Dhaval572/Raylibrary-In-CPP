#include <raylib.h>
#include "Stickman.hpp"

int main()
{
    InitWindow(600, 500, "Control stickman");

    Stickman player({10, 355}, MAGENTA);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        player.Update();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        player.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}