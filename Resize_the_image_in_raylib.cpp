// Resize image by dimensions
#include <raylib.h>

Image resizeImageByDimensions(const char *imagePath, int newWidth, int newHeight)
{
    Image image = LoadImage(imagePath);

    ImageResize(&image, newWidth, newHeight);

    return image;
}

int main()
{
    InitWindow(600, 500, " ");

    SetTargetFPS(60);

    Image croppedImage = resizeImageByDimensions("Assets/background.png", 600, 500);

    Texture2D texture = LoadTextureFromImage(croppedImage);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        DrawTexture(texture, 0, 0, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
