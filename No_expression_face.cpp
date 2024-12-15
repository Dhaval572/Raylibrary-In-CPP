// Drawing simple face
#include <raylib.h>

int main()
{
    InitWindow(400, 400, "No expression😶");

    while (!WindowShouldClose())
    {
        BeginDrawing();

        DrawCircleLines(200, 200, 200, MAGENTA); // Face
        DrawCircleLines(130, 130, 50, MAGENTA);  // Eye 1
        DrawCircleLines(270, 130, 50, MAGENTA);  // Eye 2

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
