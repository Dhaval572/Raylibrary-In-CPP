// Load images in raylib
#include <raylib.h>

int main()
{
    InitWindow(600, 500, "Image Loading Example");

    SetTargetFPS(60);

    // Load the image as a texture once before the main loop
    Texture2D texture = LoadTexture("Images/background.png");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the loaded texture
        DrawTexture(texture, 0, 0, WHITE);

        EndDrawing();
    }

    // Unload the texture after the main loop ends to deallocate memory
    UnloadTexture(texture);

    CloseWindow();
    return 0;
}
