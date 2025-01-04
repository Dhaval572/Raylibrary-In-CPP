// Open chatgpt using button
#include <raylib.h>

int main()
{
    InitWindow(600, 500, "Mouse Interaction with Image");

    SetTargetFPS(60);

    Texture2D image = LoadTexture("src/start_button.png"); // Load start button

    Rectangle imageRect = { 100.0f, 100.0f, (float)image.width, (float)image.height };

    while (!WindowShouldClose())
    {
        bool isMouseOverImage = CheckCollisionPointRec(GetMousePosition(), imageRect);
        bool isClicked = isMouseOverImage && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTexture(image, (int)imageRect.x, (int)imageRect.y, WHITE);

        if (isMouseOverImage)
        {
            DrawRectangleRec(imageRect, ColorAlpha(RED, 0.3f));

            if (isClicked)
                OpenURL("https://chatgpt.com/");
        }

        EndDrawing();
    }

    UnloadTexture(image);
    CloseWindow();

    return 0;
}
