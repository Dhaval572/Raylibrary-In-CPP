#include <raylib.h>
#include "Stickman.hpp"

int main()
{
    InitWindow(600, 500, " ");

    Stickman player({10, 250}, MAGENTA);

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