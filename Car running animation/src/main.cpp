// Car moving animation
#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
constexpr float SKIDMARK_LIFETIME = 3.0f; // Skidmarks last for 3 seconds

struct Skidmark
{
    Vector2 leftTire;
    Vector2 rightTire;
    double creationTime;
};

class Car
{
public:
    Car(Vector2 startPosition, const string &texturePath)
        : position(startPosition), texture(LoadTexture(texturePath.c_str()))
    {
        InitializeCarProperties();
    }

    ~Car()
    {
        UnloadTexture(texture);
    }

    void Update(float deltaTime)
    {
        HandleInput(deltaTime);
        UpdatePhysics(deltaTime);
        UpdateSkidmarks();
    }

    void Draw() const
    {
        DrawSkidmarks();
        DrawCar();
    }

    Vector2 GetPosition() const { return position; }

private:
    void InitializeCarProperties()
    {
        // Compromise parameters for an enjoyable, realistic speed:
        size = {80.0f, 150.0f};
        speed = 0.0f;
        angle = 0.0f;
        steering = 0.0f;
        driftAngle = 0.0f;
        maxSpeed = 700.0f;      // Intermediate top speed
        acceleration = 1150.0f; // Intermediate acceleration
        slowdown = 0.98f;
        steeringSpeed = 1.1f; // Slightly increased responsiveness
        maxSteering = 5.0f;
        steerBackSpeed = 0.1f;
        driftBias = 15.0f;
    }

    void HandleInput(float deltaTime)
    {
        if (IsKeyDown(KEY_W))
        {
            speed = min(speed + acceleration * deltaTime, maxSpeed);
        }
        else if (IsKeyDown(KEY_S))
        {
            speed = max(speed - acceleration * deltaTime, -maxSpeed);
        }
        else
        {
            speed *= slowdown;
        }

        if (IsKeyDown(KEY_A))
        {
            steering = max(steering - steeringSpeed * deltaTime * abs(speed), -maxSteering);
        }
        else if (IsKeyDown(KEY_D))
        {
            steering = min(steering + steeringSpeed * deltaTime * abs(speed), maxSteering);
        }
        steering *= (1 - steerBackSpeed);
    }

    void UpdatePhysics(float deltaTime)
    {
        angle += steering;
        driftAngle = (angle + driftAngle * driftBias) / (1 + driftBias);

        float radians = (angle - 90) * DEG2RAD;
        position.x += speed * deltaTime * cos(radians);
        position.y += speed * deltaTime * sin(radians);
    }

    void UpdateSkidmarks()
    {
        if (IsDrifting())
        {
            skidmarks.push_back({CalculateTirePosition(-240), CalculateTirePosition(-300), GetTime()});
        }
        RemoveOldSkidmarks();
    }

    bool IsDrifting() const
    {
        float driftDiff = driftAngle - angle;
        return abs(driftDiff) > 30 && abs(speed) > 50;
    }

    Vector2 CalculateTirePosition(float offsetAngle) const
    {
        float radians = (angle + offsetAngle) * DEG2RAD;
        return {position.x + (size.y / 2.6f) * cos(radians),
                position.y + (size.y / 2.6f) * sin(radians)};
    }

    void RemoveOldSkidmarks()
    {
        double currentTime = GetTime();
        skidmarks.erase(remove_if(skidmarks.begin(), skidmarks.end(),
                                  [currentTime](const Skidmark &skidmark)
                                  {
                                      return (currentTime - skidmark.creationTime) > SKIDMARK_LIFETIME;
                                  }),
                        skidmarks.end());
    }

    void DrawSkidmarks() const
    {
        for (const auto &skidmark : skidmarks)
        {
            DrawCircleV(skidmark.leftTire, 6, BLACK);
            DrawCircleV(skidmark.rightTire, 6, BLACK);
        }
    }

    void DrawCar() const
    {
        Rectangle destRect = {position.x, position.y, size.x, size.y};
        Vector2 origin = {size.x / 2, size.y / 2};
        DrawTexturePro(texture, {0, 0, (float)texture.width, (float)texture.height},
                       destRect, origin, angle, WHITE);
    }

    Vector2 position;
    Vector2 size;
    float speed;
    float angle;
    float steering;
    float driftAngle;
    float maxSpeed;
    float acceleration;
    float slowdown;
    float steeringSpeed;
    float maxSteering;
    float steerBackSpeed;
    float driftBias;
    Texture2D texture;
    vector<Skidmark> skidmarks;
};

int main()
{
    constexpr int screenWidth = 1200;
    constexpr int screenHeight = 700;

    InitWindow(screenWidth, screenHeight, "Infinite Racer (Raylib 5.5)");
    SetTargetFPS(60);

    // Load background tile texture ("Soil_Tile")
    Texture2D soilTexture = LoadTexture("Images/Soil_Tile.png");

    Car car({screenWidth / 2.0f, screenHeight / 2.0f}, "Images/Car_1_01.png");

    Camera2D camera = {0};
    camera.offset = {screenWidth / 2.0f, screenHeight / 2.0f};
    camera.zoom = 1.0f;

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        car.Update(deltaTime);
        camera.target = car.GetPosition();

        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(camera);

        // Calculate visible tile indices
        int tileWidth = soilTexture.width;
        int tileHeight = soilTexture.height;
        int startX = static_cast<int>((camera.target.x - screenWidth / 2) / tileWidth) - 1;
        int endX = static_cast<int>((camera.target.x + screenWidth / 2) / tileWidth) + 1;
        int startY = static_cast<int>((camera.target.y - screenHeight / 2) / tileHeight) - 1;
        int endY = static_cast<int>((camera.target.y + screenHeight / 2) / tileHeight) + 1;

        // Draw only visible tiles
        for (int x = startX; x <= endX; ++x)
        {
            for (int y = startY; y <= endY; ++y)
            {
                DrawTexture(soilTexture, x * tileWidth, y * tileHeight, WHITE);
            }
        }

        car.Draw();
        EndMode2D();
        EndDrawing();
    }

    UnloadTexture(soilTexture);
    CloseWindow();
    return 0;
}
