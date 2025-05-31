// Generate responsive image in window
#include <raylib.h>
#include <string>

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "Full Window Image Viewer");
    SetTargetFPS(60);

    Texture2D image = LoadTexture("assets/Mahayami.png");

    Rectangle src = {0, 0, static_cast<float>(image.width), static_cast<float>(image.height)};
    Vector2 origin = {0, 0};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        if (image.id != 0)
        {
            Rectangle dest = {0, 0, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())};
            DrawTexturePro(image, src, dest, origin, 0.0f, WHITE);
        }
        else
        {
            const char *msg = "Failed to load image!";
            int fontSize = 20;
            int textWidth = MeasureText(msg, fontSize);
            int x = (GetScreenWidth() - textWidth) / 2;
            int y = GetScreenHeight() / 2 - fontSize / 2;
            DrawText(msg, x, y, fontSize, RED);
        }

        EndDrawing();
    }

    if (image.id != 0)
        UnloadTexture(image);

    CloseWindow();
    return 0;
}
