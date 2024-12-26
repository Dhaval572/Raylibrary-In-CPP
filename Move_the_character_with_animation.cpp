// Moving the character with animation
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
void HandleMovement(Vector2 *pos, float speed)
{
    if (IsKeyDown(KEY_RIGHT))
        pos->x += speed; // Move right

    if (pos->x > GetScreenWidth() - 100)
        pos->x = 0;     // Move left
}

// Function to update animation frame
int UpdateAnimation(float &animTime, int &frame, bool isMoving)
{
    if (isMoving)
    {
        animTime += GetFrameTime(); // GetFrameTime() returns time in seconds

        if (animTime >= 0.2f)
        {
            frame = !frame;     // Swapping frames in 0.2f second
            animTime = 0.0f;    // Reset the animTime 
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
    InitWindow(600, 500, "Walking Animation");

    SetTargetFPS(60);

    // Load background and walking textures
    Texture2D background = LoadTextureFromResizedImage("Images/background.png", 600, 500);
    Texture2D walk1 = LoadTextureFromResizedImage("Images/monster_right_1.png", 100, 100);
    Texture2D walk2 = LoadTextureFromResizedImage("Images/monster_right_2.png", 100, 100);

    Vector2 position = {200.0f, 300.0f}; // Character position
    float animationTime = 0.0f;
    int frame = 0;
    float speed = 1.0f; // Animation speed
    bool isMoving = false;

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_RIGHT))
            isMoving = true;
        else
            isMoving = false;

        // Update animation and movement
        frame = UpdateAnimation(animationTime, frame, true);
        HandleMovement(&position, speed);

        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTexture(background, 0, 0, WHITE);
        
        if(isMoving)
            DrawTexture(frame == 0 ? walk1 : walk2, (int)position.x, (int)position.y, WHITE);
        else
            DrawTexture(walk1, (int)position.x, (int)position.y, WHITE); // Still character in the walk1 position

        EndDrawing();
    }

    // Deallocate the memory
    UnloadTexture(walk1);
    UnloadTexture(walk2);
    UnloadTexture(background);

    CloseWindow();
    return 0;
}
