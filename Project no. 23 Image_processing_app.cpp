// PixelMorph: Interactive Image Processing App (Class-Based)
#include <raylib.h>
#include <array>
using namespace std;

enum class ImageProcess
{
    None = 0,
    ColorGrayscale,
    ColorTint,
    ColorInvert,
    ColorContrast,
    ColorBrightness,
    FlipVertical,
    FlipHorizontal,
    Count
};

class PixelMorphApp
{
private:
    // Default app size
    int SCREEN_WIDTH = 1280;
    int SCREEN_HEIGHT = 720;

    const float MENU_X = 20.0f;
    const float MENU_WIDTH = 200.0f;
    const float ITEM_HEIGHT = 40.0f;
    const float ITEM_SPACING = 10.0f;
    const float MENU_Y = 50.0f;

    const array<const char *, static_cast<size_t>(ImageProcess::Count)> PROCESS_TEXT = {
        "NO PROCESSING",
        "COLOR GRAYSCALE",
        "COLOR TINT",
        "COLOR INVERT",
        "COLOR CONTRAST",
        "COLOR BRIGHTNESS",
        "FLIP VERTICAL",
        "FLIP HORIZONTAL"};

    Image originalImage{};
    Image processedImage{};
    Texture2D texture{};

    ImageProcess currentProcess = ImageProcess::None;
    array<Rectangle, static_cast<size_t>(ImageProcess::Count)> menuItems{};

public:
    PixelMorphApp() = default;
    ~PixelMorphApp()
    {
        UnloadResources();
    }

    void Run()
    {
        InitWindow(800, 450, "PixelMorph (initial window)");
        SetupScreen();
        SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
        SetWindowPosition((GetMonitorWidth(GetCurrentMonitor()) - SCREEN_WIDTH) / 2,
                          (GetMonitorHeight(GetCurrentMonitor()) - SCREEN_HEIGHT) / 2);
        SetWindowTitle("PixelMorph");

        SetTargetFPS(60);

        LoadResources();
        SetupMenuItems();

        while (!WindowShouldClose())
        {
            Update();
            Render();
        }
    }

private:
    void SetupScreen()
    {
        int monitor = GetCurrentMonitor();
        int monitorWidth = GetMonitorWidth(monitor);
        int monitorHeight = GetMonitorHeight(monitor);

        const int margin = 160; // Reduced margin for more responsiveness

        SCREEN_WIDTH = monitorWidth - margin;
        SCREEN_HEIGHT = monitorHeight - margin;

        // Ensure minimum window size
        if (SCREEN_WIDTH < 640)
            SCREEN_WIDTH = 640;
        if (SCREEN_HEIGHT < 480)
            SCREEN_HEIGHT = 480;
    }

    void LoadResources()
    {
        originalImage = LoadImage("Assets/Example.png");
        ImageFormat(&originalImage, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

        // Resize image if it’s too big compared to screen
        if (originalImage.width > SCREEN_WIDTH / 2 || originalImage.height > SCREEN_HEIGHT / 2)
        {
            float scaleFactorW = (SCREEN_WIDTH / 2.0f) / originalImage.width;
            float scaleFactorH = (SCREEN_HEIGHT / 2.0f) / originalImage.height;
            float scaleFactor = (scaleFactorW < scaleFactorH) ? scaleFactorW : scaleFactorH;

            int newWidth = static_cast<int>(originalImage.width * scaleFactor);
            int newHeight = static_cast<int>(originalImage.height * scaleFactor);

            ImageResize(&originalImage, newWidth, newHeight);
        }

        processedImage = ImageCopy(originalImage);
        texture = LoadTextureFromImage(processedImage);
    }

    void UnloadResources()
    {
        UnloadTexture(texture);
        UnloadImage(originalImage);
        UnloadImage(processedImage);
        CloseWindow();
    }

    void SetupMenuItems()
    {
        for (size_t i = 0; i < menuItems.size(); ++i)
        {
            menuItems[i] = {
                MENU_X,
                MENU_Y + i * (ITEM_HEIGHT + ITEM_SPACING),
                MENU_WIDTH,
                ITEM_HEIGHT};
        }
    }

    void Update()
    {
        int selectedItem = HandleMenu();
        if (selectedItem != -1 && currentProcess != static_cast<ImageProcess>(selectedItem))
        {
            currentProcess = static_cast<ImageProcess>(selectedItem);
            ApplyImageProcessing();
        }
    }

    int HandleMenu()
    {
        Vector2 mousePos = GetMousePosition();
        int selectedItem = -1;

        for (size_t i = 0; i < menuItems.size(); ++i)
        {
            if (CheckCollisionPointRec(mousePos, menuItems[i]) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            {
                selectedItem = static_cast<int>(i);
                break;
            }
        }

        return selectedItem;
    }

    void ApplyImageProcessing()
    {
        UnloadImage(processedImage);
        processedImage = ImageCopy(originalImage);

        switch (currentProcess)
        {
        case ImageProcess::ColorGrayscale:
            ImageColorGrayscale(&processedImage);
            break;
        case ImageProcess::ColorTint:
            ImageColorTint(&processedImage, GREEN);
            break;
        case ImageProcess::ColorInvert:
            ImageColorInvert(&processedImage);
            break;
        case ImageProcess::ColorContrast:
            ImageColorContrast(&processedImage, -40);
            break;
        case ImageProcess::ColorBrightness:
            ImageColorBrightness(&processedImage, -80);
            break;
        case ImageProcess::FlipVertical:
            ImageFlipVertical(&processedImage);
            break;
        case ImageProcess::FlipHorizontal:
            ImageFlipHorizontal(&processedImage);
            break;
        default:
            break;
        }

        Color *pixels = LoadImageColors(processedImage);
        UpdateTexture(texture, pixels);
        UnloadImageColors(pixels);
    }

    void Render()
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawMenu();
        DrawImage();

        EndDrawing();
    }

    void DrawMenu()
    {
        DrawText("IMAGE PROCESSING:", MENU_X, MENU_Y - 30, 20, DARKGRAY);

        Vector2 mousePos = GetMousePosition();

        for (size_t i = 0; i < menuItems.size(); ++i)
        {
            bool isCurrent = static_cast<int>(currentProcess) == static_cast<int>(i);
            bool isHovered = CheckCollisionPointRec(mousePos, menuItems[i]);

            Color bgColor = isCurrent ? SKYBLUE : (isHovered ? LIGHTGRAY : LIGHTGRAY);
            Color borderColor = isCurrent ? BLUE : GRAY;
            Color textColor = isCurrent ? DARKBLUE : DARKGRAY;

            DrawRectangleRec(menuItems[i], bgColor);
            DrawRectangleLinesEx(menuItems[i], 2, borderColor);

            int textWidth = MeasureText(PROCESS_TEXT[i], 14);
            DrawText(PROCESS_TEXT[i],
                     menuItems[i].x + (menuItems[i].width - textWidth) / 2,
                     menuItems[i].y + 10,
                     14,
                     textColor);
        }
    }

    void DrawImage()
    {
        float margin = 20.0f;

        float availableWidth = SCREEN_WIDTH - (MENU_X + MENU_WIDTH + 3 * margin);
        float availableHeight = SCREEN_HEIGHT - 2 * margin;
        float aspectRatio = static_cast<float>(texture.width) / texture.height;

        float drawWidth = availableWidth;
        float drawHeight = drawWidth / aspectRatio;

        if (drawHeight > availableHeight)
        {
            drawHeight = availableHeight;
            drawWidth = drawHeight * aspectRatio;
        }

        Vector2 imagePos = {
            MENU_X + MENU_WIDTH + 2 * margin + (availableWidth - drawWidth) / 2,
            margin + (availableHeight - drawHeight) / 2};

        DrawTexturePro(texture,
                       {0, 0, static_cast<float>(texture.width), static_cast<float>(texture.height)},
                       {imagePos.x, imagePos.y, drawWidth, drawHeight},
                       {0, 0},
                       0.0f,
                       WHITE);

        DrawRectangleLinesEx({imagePos.x, imagePos.y, drawWidth, drawHeight}, 2, BLACK);
    }
};

int main()
{
    PixelMorphApp app;
    app.Run();
    return 0;
}
