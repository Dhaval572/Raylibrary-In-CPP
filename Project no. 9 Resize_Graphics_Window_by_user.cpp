// Resize graphics window by user
#include <raylib.h>

int main()
{
    int width = 600;
    int height = 500;
    const int minWidth = 410;
    const int minHeight = 200;
    const int maxWidth = 1300;
    const int maxHeight = 700;

    InitWindow(width, height, "Window Size Control");
    SetWindowPosition(0, 25);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Increase window height
        if (IsKeyDown(KEY_UP))
        {
            height += 5;
            if (height > maxHeight)
                height = maxHeight;
            SetWindowSize(width, height);
        }

        // Decrease window height
        if (IsKeyDown(KEY_DOWN))
        {
            height -= 5;
            if (height < minHeight)
                height = minHeight;
            SetWindowSize(width, height);
        }

        // Decrease window width
        if (IsKeyDown(KEY_LEFT))
        {
            width -= 5;
            if (width < minWidth)
                width = minWidth;
            SetWindowSize(width, height);
        }

        // Increase window width
        if (IsKeyDown(KEY_RIGHT))
        {
            width += 5;
            if (width > maxWidth) // Add limit in resizing
                width = maxWidth;
            SetWindowSize(width, height);
        }

        BeginDrawing();

        ClearBackground(BLACK);

        DrawText("Press UP to increase window height", 10, 10, 20, GREEN);
        DrawText("Press DOWN to decrease window height", 10, 40, 20, GREEN);
        DrawText("Press LEFT to decrease window width", 10, 70, 20, GREEN);
        DrawText("Press DOWN to increase window width", 10, 100, 20, GREEN);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
