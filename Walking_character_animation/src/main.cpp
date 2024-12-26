#include <raylib.h>
#include "Player.hpp"

int main()
{
    const int sWidth = 1200, sHeight = 600;
    InitWindow(sWidth, sHeight, "Walking Animation");

    SetTargetFPS(60);

    // Create player object
    Player player("Images/monster_right_1.png", "Images/monster_right_2.png",
                  "Images/monster_left_1.png", "Images/monster_left_2.png", sWidth / 2, 325, 2.0f);

    while (!WindowShouldClose())
    {
        player.Update(); // Update player movement and animation

        BeginDrawing();
        ClearBackground(BLACK);
        player.Draw(); // Draw the player to the screen
        EndDrawing();
    }

    CloseWindow(); // Close the window and OpenGL context
    return 0;
}
