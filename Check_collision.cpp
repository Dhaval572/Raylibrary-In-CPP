// Collision check in raylib
#include <raylib.h>

int main()
{
    InitWindow(800, 600, "Rectangle Collision Detection");

    Rectangle player = {200, 200, 50, 50};     // Player rectangle
    Rectangle obstacle = {400, 300, 100, 100}; // Static obstacle

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())
    {
        // Move the player rectangle with arrow keys
        if (IsKeyDown(KEY_RIGHT))
            player.x += 5.0f;
        if (IsKeyDown(KEY_LEFT))
            player.x -= 5.0f;
        if (IsKeyDown(KEY_UP))
            player.y -= 5.0f;
        if (IsKeyDown(KEY_DOWN))
            player.y += 5.0f;

        // Check for collision between player and obstacle
        bool isColliding = CheckCollisionRecs(player, obstacle);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        if (isColliding)
            DrawRectangleRec(player, RED);
        else
            DrawRectangleRec(player, GREEN);

        DrawRectangleRec(obstacle, BLUE);

        // Display collision status on screen
        if (isColliding)
            DrawText("Collision Detected!", 10, 10, 20, RED);
        else
            DrawText("No Collision", 10, 10, 20, GREEN);

        // End drawing
        EndDrawing();
    }

    // Close window
    CloseWindow();

    return 0;
}
