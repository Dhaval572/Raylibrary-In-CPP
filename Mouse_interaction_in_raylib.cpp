// Move the object using mouse
#include <raylib.h>

int main()
{
    InitWindow(600, 500, "Move object"); 

    Vector2 cursorPos = { 0, 0 };   // Variable to store the cursor position
    int radius = 50;               

    SetTargetFPS(60);               

    while (!WindowShouldClose())    
    {
        cursorPos = GetMousePosition(); // Get mouse position using Raylib function

        BeginDrawing();
        
        ClearBackground(RAYWHITE);      // Make background white
        // Draw the moving circle at the mouse position
        DrawCircleV(cursorPos, radius, BLUE);

        // Check if the left mouse button is pressed
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
        {
            break; // Exit from game loop 
        }

        EndDrawing();
    }

    CloseWindow(); 
    return 0;
}

/*
Explanation:

    DrawCircleV():

        This function is used to draw the circle.

        This function takes three arguments.

        Syntax:

            DrawCircleV(center_point, radius, color);

        This takes Vector2 for get center point of circle.

        Vector2 is a data structure in Raylib used to represent 2D coordinates or points in a two-dimensional space.

    GetMousePosition():

        This function returns Vector2 as x and y coordinates of mouse cursor.

        In shortly, this is returns x and y positions of mouse.

    IsMouseButtonPressed():

        This function is used to check if given mouse button is pressed or not.

        Syntax:

            IsMouseButtonPressed(mouse_button);

    IsMouseButtonDown():

        This function is used to check if given mouse button is continuously pressed or not.

        Syntax:

            IsMouseButtonDown(mouse_button);

    There are mostly two key is used to check for mouse
    
    1). MOUSE_BUTTON_LEFT  and  2). MOUSE_BUTTON_RIGHT


    So, this was simple functions for mouse interaction in raylib.

    I hope you understand everything.
*/
