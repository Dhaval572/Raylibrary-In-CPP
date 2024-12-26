// Move character with animation
#include <raylib.h>

// Function to resize an image
Image resizeImage(const char *path, int width, int height)
{
    Image img = LoadImage(path);
    ImageResize(&img, width, height);
    return img;
}

// Function to load textures
Texture2D LoadTextureFromResizedImage(const char *path, int width, int height)
{
    return LoadTextureFromImage(resizeImage(path, width, height));
}

// Function to handle character movement
void handleMovement(Vector2 *pos, float speed, bool &isMovingRight, int &imageWidth)
{
    if (IsKeyDown(KEY_RIGHT))
    {
        pos->x += speed; // Move right
        isMovingRight = true;
    }
    else if (IsKeyDown(KEY_LEFT))
    {
        pos->x -= speed; // Move left
        isMovingRight = false;
    }

    // Movement limitation
    if (pos->x > GetScreenWidth() - imageWidth)
        pos->x = GetScreenWidth() - imageWidth;

    if (pos->x < 0)
        pos->x = 0;
}

// Function to update animation frame
int UpdateAnimation(float &animTime, int &frame, bool isMoving)
{
    if (isMoving)
    {
        animTime += GetFrameTime(); // GetFrameTime() returns time in seconds

        if (animTime >= 0.2f) // Delay between frame of 0.2 second
        {
            frame = !frame;  // Swapping frames in 0.2f second
            animTime = 0.0f; // Reset the animTime
        }
    }
    else
    {
        frame = 0; // If character is not moving
    }

    return frame;
}

// Main game loop
int main()
{
    const int sWidth = 1200, sHeight = 600;
    InitWindow(sWidth, sHeight, "Walking Animation");

    SetTargetFPS(60);

    // Load background and walking textures
    Texture2D background = LoadTextureFromResizedImage("Images/background.png", 1200, 600);

    Texture2D walkRight1 = LoadTextureFromResizedImage("Images/monster_right_1.png", 150, 150);
    Texture2D walkRight2 = LoadTextureFromResizedImage("Images/monster_right_2.png", 150, 150);

    // Load left-facing walk textures
    Texture2D walkLeft1 = LoadTextureFromResizedImage("Images/monster_left_1.png", 150, 150);
    Texture2D walkLeft2 = LoadTextureFromResizedImage("Images/monster_left_2.png", 150, 150);

    Vector2 position = {sWidth/2, 325}; // Character position at center of screen width
    float animationTime = 0.0f;
    int frame = 0;
    float speed = 1.0f; // Animation speed
    bool isMoving = false;
    bool isMovingRight = true; // True when moving right, false when moving left

    while (!WindowShouldClose())
    {
        // Handle movement direction and update the "isMoving" flag
        isMoving = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT);
        handleMovement(&position, speed, isMovingRight, walkLeft1.width);

        // Update animation and movement
        frame = UpdateAnimation(animationTime, frame, isMoving);

        BeginDrawing();

        ClearBackground(BLACK);
        DrawTexture(background, 0, 0, WHITE);

        // Draw walking animation based on movement direction
        if (isMoving)
        {
            if (isMovingRight)
                DrawTexture(frame == 0 ? walkRight1 : walkRight2, (int)position.x, (int)position.y, WHITE);
            else
                DrawTexture(frame == 0 ? walkLeft1 : walkLeft2, (int)position.x, (int)position.y, WHITE);
        }
        else
        {
            if (isMovingRight)
                DrawTexture(walkRight1, (int)position.x, (int)position.y, WHITE);
            else
                DrawTexture(walkLeft1, (int)position.x, (int)position.y, WHITE);
        }

        EndDrawing();
    }

    // Deallocate the memory
    UnloadTexture(walkRight1);
    UnloadTexture(walkRight2);
    UnloadTexture(walkLeft1);
    UnloadTexture(walkLeft2);
    UnloadTexture(background);

    CloseWindow();
    return 0;
}
