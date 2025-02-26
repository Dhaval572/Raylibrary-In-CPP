// Very simple square design
#include <raylib.h>

int main()
{
    const int screenWidth = 600;
    const int screenHeight = 500;
    InitWindow(screenWidth, screenHeight, "");

    int width = 400, height = 300;
    int squareX = (screenWidth - width) / 2;
    int squareY = (screenHeight - height) / 2;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 0; i < 8; i++)
        {
            DrawRectangleLines(
                squareX - i * 10, squareY - i * 10,
                width - i * 10, height - i * 10,
                (i % 2 == 0) ? BLUE : MAGENTA);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
