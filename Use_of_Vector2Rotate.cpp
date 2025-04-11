#include <raylib.h>
#include <raymath.h>

int main()
{
    InitWindow(800, 600, "Vector2Rotate Visual Example");

    Vector2 center = {400, 300}; // Center of screen
    Vector2 dir = {100, 0};      // Initial direction vector (pointing right)
    float rotationSpeed = 90.0f; // Degrees per second

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        // Rotate the direction vector continuously
        dir = Vector2Rotate(dir, (DEG2RAD * rotationSpeed * dt));
        // (Note: DEG2RAD = Degree to radiun)

        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Rotating Vector (Vector2Rotate)", 10, 10, 20, GREEN);

        // Draw center point
        DrawCircleV(center, 3, RED);

        // Draw line showing the rotated vector
        DrawLineV(center, Vector2Add(center, dir), BLUE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
