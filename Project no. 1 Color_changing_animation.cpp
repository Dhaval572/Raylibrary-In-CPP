// Color changing animation
#include <iostream>
#include <raylib.h>
#include <time.h> // To use time()

// Return random numbers through given range
int random(int min, int max)
{
    return (min + rand()) % (max - min + 1);
}

// Returns random color
Color randomColor()
{
    Color randomCol = {random(0, 255), random(0, 255), random(0, 255), 255};
    return randomCol;
}

int main()
{
    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), " ");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        _sleep(500); // For delay()

        BeginDrawing();

        ClearBackground(randomColor()); // To change background color

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
