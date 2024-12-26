// Resize image by dimensions
#include <raylib.h>

// Function to resize an image based on new width and height
Image resizeImageByDimensions(const char *imagePath, int newWidth, int newHeight)
{
    // Load the image from file
    Image image = LoadImage(imagePath);

    // Resize the image to the new width and height
    ImageResize(&image, newWidth, newHeight);

    // Return the resized image
    return image;
}

int main()
{
    InitWindow(600, 500, " ");

    SetTargetFPS(60);

    Image croppedImage = resizeImageByDimensions("Images/background.png", 300, 300);

    Texture2D texture = LoadTextureFromImage(croppedImage);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        DrawTexture(texture, 100, 100, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
