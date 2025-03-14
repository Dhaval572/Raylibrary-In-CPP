// Realistic Sunset Crying Scene
#include <raylib.h>
#include <vector>
#include <algorithm>
#include <raymath.h>
#include <string>
using namespace std;

// Compile-time constants
constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;
constexpr int TEAR_LIFETIME = 180;
constexpr float GRAVITY = 0.1f;
constexpr float SUN_SPEED = 0.05f;
constexpr float CHARACTER_RADIUS = 20.0f;
constexpr float TEXT_SPEED = 0.05f;
constexpr float TEAR_MAX_DISTANCE = 40.5f;

// Compile-time color definitions
constexpr Color SKY_TOP{255, 140, 0, 255};
constexpr Color SKY_BOTTOM{30, 10, 50, 255};
constexpr Color SUN_COLOR{250, 180, 50, 255};
constexpr Color HILL_DARK{100, 50, 15, 255};
constexpr Color HILL_LIGHT{139, 69, 19, 255};
constexpr Color TEAR_COLOR{230, 230, 255, 255};
constexpr Color PERSON_COLOR{112, 128, 144, 255};

// Typing effect variables
const string FULL_TEXT = "Why am I so alone... even my shadow disappears with the sunset.";
float startTime;

struct Tear
{
    float x, y;
    float startY;
    float velocityY{0.5f};
    float velocityX;
    int life{TEAR_LIFETIME};

    Tear(float startX, float startY) : x(startX), y(startY), startY(startY)
    {
        if (startX < SCREEN_WIDTH / 2.0f)
            velocityX = -0.8f; // Left eye tear falls diagonally left (/)
        else
            velocityX = 0.8f; // Right eye tear falls diagonally right (\)
    }
};

// Update tears with gravity effect
void UpdateTears(vector<Tear> &tears)
{
    for (auto &tear : tears)
    {
        tear.x += tear.velocityX;
        tear.y += tear.velocityY;
        tear.velocityY += GRAVITY;
        --tear.life;
    }

    tears.erase(remove_if(tears.begin(), tears.end(), [](const Tear &t)
                          { return t.life <= 0 || ((t.y - t.startY) > TEAR_MAX_DISTANCE); }),
                tears.end());
}

void DrawSkyGradient()
{
    for (int i = 0; i < SCREEN_HEIGHT; ++i)
    {
        float factor = static_cast<float>(i) / SCREEN_HEIGHT;
        Color blendedColor{
            static_cast<unsigned char>(SKY_TOP.r * (1 - factor) + SKY_BOTTOM.r * factor),
            static_cast<unsigned char>(SKY_TOP.g * (1 - factor) + SKY_BOTTOM.g * factor),
            static_cast<unsigned char>(SKY_TOP.b * (1 - factor) + SKY_BOTTOM.b * factor),
            255};
        DrawRectangle(0, i, SCREEN_WIDTH, 1, blendedColor);
    }
}

void DrawCharacter(const Vector2 &pos)
{
    // Head
    DrawCircle(pos.x, pos.y, CHARACTER_RADIUS, PERSON_COLOR);

    // Body
    DrawRectangle(pos.x - 12, pos.y + CHARACTER_RADIUS, 24, 50, PERSON_COLOR);

    // Eyes
    DrawCircle(pos.x - 8, pos.y - 5, 4, BLACK); // Left eye
    DrawCircle(pos.x + 8, pos.y - 5, 4, BLACK); // Right eye

    // Legs
    DrawLine(pos.x - 8, pos.y + CHARACTER_RADIUS + 50, pos.x - 16, pos.y + CHARACTER_RADIUS + 80, PERSON_COLOR); // Left leg
    DrawLine(pos.x + 8, pos.y + CHARACTER_RADIUS + 50, pos.x + 16, pos.y + CHARACTER_RADIUS + 80, PERSON_COLOR); // Right leg

    // Arms
    DrawLine(pos.x - 12, pos.y + CHARACTER_RADIUS + 15, pos.x - 30, pos.y + CHARACTER_RADIUS + 40, PERSON_COLOR); // Left arm
    DrawLine(pos.x + 12, pos.y + CHARACTER_RADIUS + 15, pos.x + 30, pos.y + CHARACTER_RADIUS + 40, PERSON_COLOR); // Right arm
}

// Display text with a typing effect in a speech format
void DrawTypingText(const Vector2 &charPos, int fontSize, Color color)
{
    // Get elapsed time and calculate visible character count
    int visibleChars = Clamp((GetTime() - startTime) / TEXT_SPEED, 0, FULL_TEXT.length());

    // Extract only the visible part of the text
    string displayedText = TextSubtext(FULL_TEXT.c_str(), 0, visibleChars);

    // Center text above the character
    int textX = charPos.x - MeasureText(displayedText.c_str(), fontSize) / 2;
    int textY = charPos.y - 70;

    // Draw Speech connector line
    DrawLine(charPos.x, charPos.y - 20, charPos.x - 10, charPos.y - 50, color);
    DrawText(displayedText.c_str(), textX, textY, fontSize, color);
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunset of a Broken Soul");
    vector<Tear> tears;

    // Adjusted position for larger character
    constexpr Vector2 CHARACTER_POS{SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 180};

    float sunY = 100.0f;
    startTime = GetTime();

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        if (sunY < 200)
            sunY += SUN_SPEED;

        // Generate tears from both eyes simultaneously
        if (GetRandomValue(0, 100) < 50)
        {
            tears.emplace_back(Tear{CHARACTER_POS.x - 8, CHARACTER_POS.y - 5}); // Left eye tear
            tears.emplace_back(Tear{CHARACTER_POS.x + 8, CHARACTER_POS.y - 5}); // Right eye tear
        }

        UpdateTears(tears);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawSkyGradient();
        DrawCircle(SCREEN_WIDTH - 150, sunY, 50, SUN_COLOR);
        DrawEllipse(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50, 420, 140, HILL_DARK);
        DrawEllipse(SCREEN_WIDTH / 2 + 20, SCREEN_HEIGHT - 55, 400, 130, HILL_LIGHT);
        DrawCharacter(CHARACTER_POS);

        for (const auto &tear : tears)
            DrawCircle(tear.x, tear.y, 2, TEAR_COLOR);

        DrawTypingText(CHARACTER_POS, 20, {180, 180, 180, 255});

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
