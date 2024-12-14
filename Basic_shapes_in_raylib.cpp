// Basic shapes is ray library
#include <raylib.h>

int main()
{
    InitWindow(600, 500, " ");

    while (!WindowShouldClose())
    {
        BeginDrawing();

        // Will draw filled circle, ractangle and lines
        DrawCircle(50, 50, 20, BLUE);          // Will draw circle
        DrawRectangle(100, 100, 50, 50, BLUE); // Will draw rectangle
        DrawLine(200, 200, 100, 200, BLUE);    // Will draw line

        // Will draw outline of circle, rectangle and lines
        DrawCircleLines(500, 300, 30, MAGENTA);        // Will draw outlines of circle
        DrawRectangleLines(300, 300, 20, 40, MAGENTA); // Will draw outlines of rectangle

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
/*
Explanation:

    ( Note: The coordinates are measured in pixels )
    Syntax of filled circle:

        DrawCircle(x_coordinate, y_coordinate, radius, color);

        here, you have to enter four parameter x coordinate, y coordinate, radius and the color of circle.

    Syntax of circle outline:

        DrawCircleLines(x_coordinate, y_coordinate, radius, color);

        here, you have to enter four parameter x coordinate, y coordinate, radius and the color of circle outline.

    Syntax of filled rectangle:

        DrawRectangle(x_coordinate, y_coordinate, width, height, color);

        Here, you have to enter five parameter x coordinate, y coordinate, width of rectangle, height of rectangle and color;

    Syntax of rectanle outline:

        DrawRectangleLines(x_coordinate, y_coordinate, width, height, color);

        Here, you have to enter five parameter x coordinate, y coordinate, width of rectangle, height of rectangle and outline color;

    Syntax of Line: 

        DrawLine(startX, startY, endX, endY, color);

        Here,

        startX: The X coordinate of the start point of the line.

        startY: The Y coordinate of the start point of the line.

        endX: The X coordinate of the end point of the line.

        endY: The Y coordinate of the end point of the line.

        color: Color of line 

    So, i hope you understand everything!!

*/
