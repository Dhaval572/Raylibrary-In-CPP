// Add text in the graphics window 
#include <raylib.h>

int main()
{
    InitWindow(600, 500, " ");

    Font defaultFont = GetFontDefault();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        DrawText("This is a text sample", 100, 100, 20, GREEN);

        EndDrawing();

    }

    CloseWindow();
    return 0;
}
/*
Explanation:

    In raylib there are many functions to add the text in the graphics window, but only one funtion in mostly usefull😅.

    DrawText():

        Draw basic text with a given font size and color.

        Syntax:

            DrawText("text_to_add", x_pos, y_pos, font_size, color);

    So, this function takes the position to when add text and takes size and color of text.

*/
