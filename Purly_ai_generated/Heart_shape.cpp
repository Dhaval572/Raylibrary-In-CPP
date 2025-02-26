#include <raylib.h>
#include <cmath> // for sin, cos functions

const int screenWidth = 800;
const int screenHeight = 600;

// Function to draw a heart shape using small circles
void DrawHeart(int centerX, int centerY, float scale, Color color)
{
    const int numPoints = 100; // Number of points to approximate the heart shape

    // Generate and draw points for the heart shape
    for (int i = 0; i < numPoints; i++)
    {
        float t = (float)i / numPoints * 2 * PI; // Parameter t from 0 to 2π
        float x = 16 * powf(sinf(t), 3);        // Heart curve equation for x
        float y = -(13 * cosf(t) - 5 * cosf(2 * t) - 2 * cosf(3 * t) - cosf(4 * t)); // Heart curve equation for y

        // Scale and translate the points to the desired position
        Vector2 point = {
            centerX + x * scale,
            centerY + y * scale
        };

        // Draw a small circle at each point
        DrawCircleV(point, 3, color); // Adjust the radius (3) as needed
    }
}

int main()
{
    InitWindow(screenWidth, screenHeight, "Heart Shape in Raylib");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE); // Use a contrasting background color

        // Draw a heart at the center of the screen
        DrawHeart(screenWidth / 2, screenHeight / 2, 10.0f, RED); // Adjust scale and color

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
