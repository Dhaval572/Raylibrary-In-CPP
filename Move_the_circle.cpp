// Move the circle
#include <raylib.h>

int main()
{
    InitWindow(600, 500, "Move the circle");

    int x_pos = 300, y_pos = 250, radius = 50;
    int moveSpeed = 5;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(WHITE);

        if(IsKeyDown(KEY_RIGHT) && (x_pos < GetScreenWidth() - radius)) x_pos += moveSpeed;

        if(IsKeyDown(KEY_LEFT) && (x_pos - radius) > 0) x_pos -= moveSpeed;

        if(IsKeyDown(KEY_UP) && (y_pos - radius) > 0) y_pos -= moveSpeed;

        if(IsKeyDown(KEY_DOWN) && (y_pos < GetScreenHeight() - radius)) y_pos += moveSpeed;

        DrawCircle(x_pos, y_pos, radius, BLUE);

        EndDrawing();

    }

    CloseWindow();
    return 0;
}
