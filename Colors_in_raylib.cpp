// Colors in raylib
#include <raylib.h>

int main()
{
    InitWindow(600, 500, "Colors");

    Color customColor = {131, 135, 49, 255};

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(WHITE);
        DrawCircle(100, 200, 50, customColor);

        EndDrawing();

    }

    CloseWindow();
    return 0;
}
/*
Raylib includes a wide range of predefined colors:

    RAYWHITE, DARKBLUE, DARKGREEN, LIGHTGRAY, BLACK BLUE, RED, MAGENTA,
    YELLOW, GREEN, BROWN

You can also make your custom color in raylib using Color structure:

    Color is a structure, which is used to represent a color, specifically using the RGBA format, which includes values for Red, Green, Blue, and Alpha (opacity).

    The alpha channel controls the transparency (or opacity) of a color,

    Syntax:

        Color colorVariableName = {value_for_red, value_for_green, value_for_blue, value_for_alpha};

    Alpha = 0 means fully transparent (invisible).

    Alpha = 255 means fully opaque (solid).

    So, this was colors which are available in raylib.

    Now, if you want to change the background color of the graphics window then ray library provides the ClearBackground() function.

    Syntax:

        ClearBackground(color_name);

    
    So, I hope you understand!!
*/
