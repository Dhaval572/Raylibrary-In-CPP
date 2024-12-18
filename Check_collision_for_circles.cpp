// Check collision between two circles
#include <raylib.h>

int main()
{
    InitWindow(800, 600, "Circle Collision Detection");

    Vector2 playerPosition = {200, 200};
    float playerRadius = 20.0f;

    Vector2 obstaclePosition = {400, 300};
    float obstacleRadius = 50.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_RIGHT)) playerPosition.x += 5.0f;
        if (IsKeyDown(KEY_LEFT)) playerPosition.x -= 5.0f;
        if (IsKeyDown(KEY_UP)) playerPosition.y -= 5.0f;
        if (IsKeyDown(KEY_DOWN)) playerPosition.y += 5.0f;

        bool isColliding = CheckCollisionCircles(playerPosition, playerRadius, obstaclePosition, obstacleRadius);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        if (isColliding)
            DrawCircleV(playerPosition, playerRadius, RED); // Make circle Red
        else
            DrawCircleV(playerPosition, playerRadius, GREEN); // Make circle Green

        DrawCircleV(obstaclePosition, obstacleRadius, BLUE);

        // Provide message to user 
        if (isColliding)
            DrawText("Collision Detected!", 10, 10, 20, RED);
        else
            DrawText("No Collision", 10, 10, 20, GREEN);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
