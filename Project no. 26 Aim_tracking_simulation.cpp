// Aim Tracking simulation
#include <raylib.h>
#include <ctime>
#include <raymath.h>

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;
constexpr int TARGET_FPS = 144;
constexpr float SMOOTHING_SPEED = 100.0f;

enum Difficulty
{
    MEDIUM,
    HARD
};
enum GameState
{
    SELECT_DIFFICULTY,
    PLAYING,
    EXIT
};

inline float RandomFloat(float min, float max)
{
    return min + static_cast<float>(rand()) / (RAND_MAX / (max - min));
}

inline void DrawCrosshair(Vector2 pos)
{
    DrawLine(pos.x - 5, pos.y, pos.x + 5, pos.y, WHITE);
    DrawLine(pos.x, pos.y - 5, pos.x, pos.y + 5, WHITE);
}

struct Stickman
{
    Vector2 position;
    Vector2 velocity;
    float headRadius;
    Difficulty difficulty;

    void Init(Vector2 pos, Difficulty diff)
    {
        position = pos;
        velocity = {RandomFloat(-300, 300), RandomFloat(-300, 300)};
        headRadius = 10.0f;
        difficulty = diff;
    }

    void Update(float dt, bool isTracking)
    {
        float speedMultiplier = (difficulty == HARD && isTracking) ? 1.0f : 0.5f;

        position.x += velocity.x * dt * speedMultiplier;
        position.y += velocity.y * dt * speedMultiplier;

        if (position.x <= headRadius || position.x >= SCREEN_WIDTH - headRadius)
        {
            position.x = Clamp(position.x, headRadius, SCREEN_WIDTH - headRadius);
            velocity.x *= -1;
        }
        if (position.y <= headRadius || position.y >= SCREEN_HEIGHT - headRadius)
        {
            position.y = Clamp(position.y, headRadius, SCREEN_HEIGHT - headRadius);
            velocity.y *= -1;
        }
    }

    void Draw(bool isAimed) const
    {
        Vector2 neck = {position.x, position.y + headRadius};
        Vector2 hip = {position.x, neck.y + 40};

        DrawCircleV(position, headRadius, isAimed ? GREEN : RED);
        DrawLineV(neck, hip, WHITE);
        DrawLine(neck.x, neck.y + 5, neck.x - 15, neck.y + 25, WHITE);
        DrawLine(neck.x, neck.y + 5, neck.x + 15, neck.y + 25, WHITE);
        DrawLine(hip.x, hip.y, hip.x - 15, hip.y + 25, WHITE);
        DrawLine(hip.x, hip.y, hip.x + 15, hip.y + 25, WHITE);
    }

    bool IsMouseOver(Vector2 mousePos) const
    {
        return Vector2Distance(mousePos, position) <= headRadius + 2.0f;
    }
};

Stickman target;
Difficulty difficulty = MEDIUM;
GameState gameState = SELECT_DIFFICULTY;
float trackingTime = 0.0f;
float totalTime = 0.0f;
Vector2 realMouse = {};
Vector2 virtualMouse = {};

void PollInput()
{
    if (gameState == SELECT_DIFFICULTY)
    {
        if (IsKeyPressed(KEY_H))
            difficulty = HARD;
        if (IsKeyPressed(KEY_M))
            difficulty = MEDIUM;

        if (IsKeyPressed(KEY_H) || IsKeyPressed(KEY_M))
        {
            target.Init({SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f}, difficulty);
            trackingTime = 0.0f;
            totalTime = 0.0f;
            gameState = PLAYING;
        }
    }
}

void UpdateGame(float dt)
{
    if (gameState != PLAYING)
        return;

    realMouse = GetMousePosition();
    virtualMouse = Vector2Lerp(virtualMouse, realMouse, SMOOTHING_SPEED * dt);

    bool isTracking = target.IsMouseOver(virtualMouse);

    target.Update(dt, isTracking);

    totalTime += dt;
    if (isTracking)
        trackingTime += dt;
}

void DrawGame()
{
    BeginDrawing();
    ClearBackground(BLACK);

    if (gameState == SELECT_DIFFICULTY)
    {
        DrawText("Select Difficulty:", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 100, 40, WHITE);
        DrawText("Press [H] for HARD", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 30, 30, RED);
        DrawText("Press [M] for MEDIUM", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 30, 30, GREEN);
    }
    else if (gameState == PLAYING)
    {
        bool isTracking = target.IsMouseOver(virtualMouse);

        target.Draw(isTracking);
        DrawCrosshair(virtualMouse);

        DrawText(TextFormat("Tracking: %.2fs", trackingTime), 10, 10, 24, GREEN);
        DrawText(TextFormat("Accuracy: %.1f%%", (totalTime > 0 ? (trackingTime / totalTime) * 100.0f : 0.0f)), 10, 40, 24, GREEN);

        const char *difficultyText = (difficulty == HARD) ? "HARD" : "MEDIUM";
        Color difficultyColor = (difficulty == HARD) ? RED : PURPLE;
        int textWidth = MeasureText(difficultyText, 30);
        DrawText(difficultyText, (SCREEN_WIDTH - textWidth) / 2, 10, 30, difficultyColor);
    }

    EndDrawing();
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Aim Drift");
    SetTargetFPS(TARGET_FPS);
    HideCursor();
    srand(static_cast<unsigned>(time(0)));

    while (!WindowShouldClose())
    {
        PollInput();
        UpdateGame(GetFrameTime());
        DrawGame();
    }

    CloseWindow();
    return 0;
}
