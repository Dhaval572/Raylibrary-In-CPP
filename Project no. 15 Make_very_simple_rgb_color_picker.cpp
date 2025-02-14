// Simple color picker
#include <raylib.h>

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Simple Color Picker");

    // Set all color at default value
    int red = 0;
    int green = 0;
    int blue = 0;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Calculate RGB values based on mouse position 
        red = (GetMouseX() * 255) / screenWidth;
        green = (GetMouseY() * 255) / screenHeight;
        blue = ((GetMouseX() + GetMouseY()) * 255) / (screenWidth + screenHeight);

        // Clamp the RGB values to the range 0-255
        if (red < 0) red = 0;
        if (red > 255) red = 255;
        if (green < 0) green = 0;
        if (green > 255) green = 255;
        if (blue < 0) blue = 0;
        if (blue > 255) blue = 255;

        Color currentColor = {(unsigned char)red, (unsigned char)green, (unsigned char)blue, 255};

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Rectangle which displays the current color
        DrawRectangle(10, 10, 200, 200, currentColor);

        // Display the RGB values as integers
        DrawText(TextFormat("R: %d", red), 220, 50, 20, RED);
        DrawText(TextFormat("G: %d", green), 220, 100, 20, GREEN);
        DrawText(TextFormat("B: %d", blue), 220, 150, 20, BLUE);

        DrawText("Move the mouse to change the color!", 10, 220, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
