// IsKeyPressedRepeat() in raylib
#include <raylib.h>

int main()
{
    InitWindow(600, 400, "IsKeyPressedRepeat Example");

    SetTargetFPS(60);

    int counter = 0;

    while (!WindowShouldClose())
    {
        if (IsKeyPressedRepeat(KEY_SPACE))
        {
            counter++; 
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Hold or tap [SPACE] to increase counter", 50, 100, 20, DARKGRAY);
        DrawText(TextFormat("Counter: %d", counter), 50, 150, 30, BLUE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
