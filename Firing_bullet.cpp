// Bullet fire animation 
#include <raylib.h>

int main()
{
    InitWindow(600, 500, "Gun Animation");

    // Variables for the bullet
    Vector2 bulletPosition = {320, 340};
    Vector2 bulletSpeed = {-10.0f, 0.0f}; // Speed of bullet (move left)
    bool isBulletFired = false;

    // Set FPS to control the speed of the bullet animation
    SetTargetFPS(30);

    while (!WindowShouldClose())
    {
        // Check if space key is pressed to fire bullet
        if (IsKeyPressed(KEY_SPACE) && !isBulletFired)
        {
            // Reset bullet position and set fired state to true
            bulletPosition = (Vector2){320, 340};
            isBulletFired = true;
        }

        // Update bullet position if it's fired
        if (isBulletFired)
        {
            bulletPosition.x += bulletSpeed.x; // Move the bullet to the left

            // If bullet goes out of the screen, stop it
            if (bulletPosition.x < 0) // Bullet goes out of the left side
            {
                isBulletFired = false; // Stop the bullet animation
            }
        }

        // Begin drawing
        BeginDrawing();

        ClearBackground(BLACK);

        // Draw the character
        // Head of man
        DrawCircle(350, 300, 25, MAGENTA);

        // Neck of man
        DrawLine(350, 325, 350, 350, BLUE);

        // Hands of man
        DrawLine(325, 350, 375, 350, BLUE);

        // Leg1 of man
        DrawLine(350, 350, 325, 400, BLUE);

        // Leg2 of man
        DrawLine(350, 350, 375, 400, BLUE);

        // Gun handle
        DrawLine(330, 340, 330, 360, BLUE);

        // Gun upper part
        DrawLine(320, 340, 330, 340, BLUE);

        // Draw bullet if fired
        if (isBulletFired)
        {
            DrawLine(bulletPosition.x, bulletPosition.y, bulletPosition.x + 10, bulletPosition.y, MAGENTA);
        }

        // Display message when the bullet has been fired
        if (!isBulletFired)
        {
            DrawText("Press space to fire", 20, 20, 20, GREEN);
        }

        // End drawing
        EndDrawing();
    }

    // Close the window and OpenGL context
    CloseWindow();

    return 0;
}
