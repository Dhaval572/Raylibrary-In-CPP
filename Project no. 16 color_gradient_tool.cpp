// Interactive Gradient Generator
#include <raylib.h>

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Gradient Generator");

    // Colors for the gradient
    Color color1 = {0, 0, 0, 255}; // First color (controlled by X)
    Color color2 = {0, 0, 0, 255}; // Second color (controlled by Y)

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Update color1 based on mouse X position
        color1.r = (GetMouseX() * 255) / screenWidth; // If cursor move the down than blue color increased
        color1.g = 0;
        color1.b = 0;

        // Update color2 based on mouse Y position
        color2.r = 0;
        color2.g = 0;
        color2.b = (GetMouseY() * 255) / screenHeight; // If cursor move the down than blue color increased

        // Limit the RGB values to the range 0-255
        if (color1.r < 0)
            color1.r = 0;
        if (color1.r > 255)
            color1.r = 255;
        if (color2.b < 0)
            color2.b = 0;
        if (color2.b > 255)
            color2.b = 255;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the gradient rectangle
        for (int i = 0; i < screenWidth; i++)
        {
            // Interpolate between color1 and color2
            float t = (float)i / screenWidth;
            Color gradientColor = {
                (unsigned char)(color1.r + t * (color2.r - color1.r)), // Red
                (unsigned char)(color1.g + t * (color2.g - color1.g)), // Green
                (unsigned char)(color1.b + t * (color2.b - color1.b)), // Blue
                255};
            DrawLine(i, 0, i, screenHeight, gradientColor);
        }

        // Display the RGB values of the two colors
        DrawText(TextFormat("Color 1 (Red): R: %d, G: %d, B: %d", color1.r, color1.g, color1.b), 10, 10, 20, WHITE);
        DrawText(TextFormat("Color 2 (Blue): R: %d, G: %d, B: %d", color2.r, color2.g, color2.b), 10, 40, 20, WHITE);

        DrawText("Move the mouse to adjust the gradient!", 10, screenHeight - 30, 20, GREEN);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
