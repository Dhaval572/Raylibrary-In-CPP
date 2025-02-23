// Open link in raylib
#include <raylib.h>

bool IsMouseHovering(int x, int y, int width, int height)
{
    Vector2 mousePos = GetMousePosition();

    return (mousePos.x >= x && mousePos.x <= x + width &&
            mousePos.y >= y && mousePos.y <= y + height);
}

void DrawHoverEffect(int textX, int textY, int textWidth, int textHeight, Color color)
{
    if (IsMouseHovering(textX, textY, textWidth, textHeight))
        DrawRectangleLines(textX - 2, textY - 2, textWidth + 4, textHeight + 4, color);
}

void CheckAndOpenLink(int textX, int textY, int textWidth, int textHeight, const char *url)
{
    if (IsMouseHovering(textX, textY, textWidth, textHeight) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        OpenURL(url);
}

int main()
{
    const int sWidth = 600;
    const int sHeight = 500;
    InitWindow(sWidth, sHeight, "Open link");

    const char *url = "https://github.com/Dhaval572";
    const char *linkText = "Click me to open link";

    int textHeight = 40;
    int textWidth = MeasureText(linkText, textHeight);
    int textX = (sWidth - textWidth) / 2;
    int textY = (sHeight - textHeight) / 2;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        CheckAndOpenLink(textX, textY, textWidth, textHeight, url);

        BeginDrawing();
        ClearBackground(BLACK);

        DrawText(linkText, textX, textY, textHeight, BLUE);
        DrawHoverEffect(textX, textY, textWidth, textHeight, BLUE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
