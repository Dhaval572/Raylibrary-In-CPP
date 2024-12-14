// Open graphic window in full screen.
#include <raylib.h>

int main()
{
    const int width = GetMonitorWidth(0);
    const int height = GetMonitorHeight(0);

    InitWindow(width, height, "Full screen");

    while (!WindowShouldClose())
    {
        BeginDrawing();

        

        EndDrawing();

    }

    CloseWindow();
    return 0;
}
/*
Here i used two functions to find the width and height of device:

    1). For width of screen:

        GetMonitorWidth(0);

        This gives you the maximum width of your device screen.

    2). For height of screen:

        GetMonitorHeight(0);

        This gives you the maximum height of your device screen.

    So, using this functions, you can open your project in full screen.
*/
