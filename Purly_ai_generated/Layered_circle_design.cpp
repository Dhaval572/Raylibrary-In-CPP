// Make Layered circle design
#include <raylib.h>

// Design one
void designOne(Vector2 position, float radius, Color baseColor)
{
    // Glow effect (outer transparent layer)
    DrawCircleV(position, radius * 3.5f, ColorAlpha(baseColor, 0.15f)); // 15% opacity

    // Main ball (middle layer, light)
    DrawCircleV(position, radius * 1.4f, ColorAlpha(baseColor, 0.75f)); // 75% opacity

    // Inner ball (Main ball, Dark)
    DrawCircleV(position, radius, baseColor); // 100% opacity
}

// Design two
void designTwo(Vector2 position, float radius, Color baseColor)
{
    // Outer layer (transparent)
    DrawCircleV(position, radius * 1.2f, ColorAlpha(baseColor, 0.3f)); // 30% opacity

    // Middle layer (less dark)
    DrawCircleV(position, radius * 0.8f, Fade(baseColor, 0.7f)); // 70% opacity

    // Inner layer (darkest)
    DrawCircleV(position, radius * 0.4f, Fade(baseColor, 1.0f)); // 100% opacity
}

int main()
{
    InitWindow(600, 500, "Layered Circle Design");

    // Generate a random color using HSV
    Color ballColor = ColorFromHSV(GetRandomValue(0, 360), 0.9f, 0.9f);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw the layered circle
        designOne((Vector2){200, 250}, 15, ballColor);
        designTwo((Vector2){400, 250}, 35, ballColor);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
