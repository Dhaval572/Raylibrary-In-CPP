#include <raylib.h>
#include "movement_control.hpp"

int main()
{
    const int screenWidth = 600;
    const int screenHeight = 500;
    InitWindow(screenWidth, screenHeight, "Movement Demo");
    SetTargetFPS(60);

    // Circle ball = {{0, 0}, 20, 5};
    Rect box = {{300, 200}, {80, 60}, 5};

    while (!WindowShouldClose())
    {
        // MoveUsingArrowKeys(&ball, screenWidth, screenHeight);
        MoveUsingArrowKeys(&box, screenWidth, screenHeight);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        // DrawCircleV(ball.position, ball.radius, RED);
        DrawRectangleV(box.position, box.size, BLUE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
