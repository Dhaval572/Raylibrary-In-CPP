// Hower effect in button
#include <raylib.h>

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Button Hover Effect");

    Rectangle button = {(screenWidth - 200) / 2, (screenHeight - 50) / 2, 200, 50};

    Color buttonColor = LIGHTGRAY;
    Color afterHover = {128, 130, 127, 255};

    while (!WindowShouldClose())
    {
        Vector2 mousePosition = GetMousePosition();

        // Check if the mouse is over the button
        if (CheckCollisionPointRec(mousePosition, button))
        {
            buttonColor = afterHover; // Change button color when hovered
        }
        else
        {
            buttonColor = LIGHTGRAY; // Default color
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the button
        DrawRectangleRec(button, buttonColor);
        DrawText("Hover Me!", button.x + 50, button.y + 15, 20, BLACK);

        EndDrawing();
    }

    CloseWindow(); 
    return 0;
}
