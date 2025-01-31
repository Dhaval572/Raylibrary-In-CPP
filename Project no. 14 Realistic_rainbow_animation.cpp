// Very realistic rainbow animation
#include <raylib.h>

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Real Rainbow Animation");

    SetTargetFPS(60);

    float hue = 0.0f; // Hue value for the rainbow color

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        // Loop through each pixel on the screen
        for (int y = 0; y < screenHeight; y++)
        {
            for (int x = 0; x < screenWidth; x++)
            {
                // Calculate the color based on the hue
                Color color = ColorFromHSV(hue + (x + y) * 0.1f, 1.0f, 1.0f);
                DrawPixel(x, y, color); 
            }
        }

        // Increment the hue to create the rainbow animation effect
        hue += 0.5f;
        if (hue >= 360.0f)
            hue = 0.0f; // Reset hue after a full cycle

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
