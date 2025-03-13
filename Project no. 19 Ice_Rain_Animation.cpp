// Ice raining animation
#include <raylib.h>
#include <vector>
#include <algorithm>
using namespace std;

class IceSystem
{
public:
    struct IceParticle
    {
        Vector2 position;
        float speed;
        float size;
    };

    vector<IceParticle> particles;
    vector<float> iceSurface;

    // Static constexpr values for optimization
    static constexpr float BASE_FALL_SPEED = 300.0f;
    static constexpr float ACCUMULATION_FACTOR = 1.0f;
    static constexpr int DEFAULT_SPAWN_COUNT = 3;

    IceSystem(int screenWidth)
    {
        iceSurface.resize(screenWidth, 0.0f);
    }

    void AutoSpawn(int screenWidth, int count = DEFAULT_SPAWN_COUNT)
    {
        // Reserve memory to prevent multiple reallocations
        particles.reserve(particles.size() + count);

        for (int i = 0; i < count; i++)
        {   
            // Emplacing the constructor
            particles.emplace_back(IceParticle
            {
                {static_cast<float>(GetRandomValue(0, screenWidth - 1)), -10.0f}, 
                static_cast<float>(GetRandomValue(100, 150)) / 100.0f,            
                static_cast<float>(GetRandomValue(2, 4))                          
            });
        }
    }

    void Update(float deltaTime, int screenHeight)
    {
        // Updates for each partic
        for (auto &p : particles)
        {
            p.position.y += p.speed * BASE_FALL_SPEED * deltaTime;
            int centerX = static_cast<int>(p.position.x);
            centerX = max(0, min(centerX, static_cast<int>(iceSurface.size()) - 1));
            float hillTop = screenHeight - iceSurface[centerX];

            if (p.position.y + p.size >= hillTop)
            {
                int radius = static_cast<int>(p.size);
                for (int x = centerX - radius; x <= centerX + radius; x++)
                {
                    if (x >= 0 && x < static_cast<int>(iceSurface.size()))
                        iceSurface[x] += p.size * ACCUMULATION_FACTOR;
                }
                p.position.y = screenHeight + 100;
            }
        }

        particles.erase(remove_if(particles.begin(), particles.end(),
                                  [screenHeight](const IceParticle &p)
                                  { return p.position.y > screenHeight; }),
                        particles.end());
    }

    void Draw(int screenHeight) const
    {
        for (const auto &p : particles)
            DrawCircleV(p.position, p.size, WHITE);

        for (int j = 0; j < static_cast<int>(iceSurface.size()); j++)
        {
            float height = iceSurface[j];
            if (height > 0)
                DrawLine(j, screenHeight - static_cast<int>(height), j, screenHeight, Fade(WHITE, 0.8f));
        }
    }
};

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Ice Rain");
    
    IceSystem iceSystem(screenWidth);
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        iceSystem.AutoSpawn(screenWidth);
        iceSystem.Update(deltaTime, screenHeight);

        BeginDrawing();
        ClearBackground(BLACK);

        iceSystem.Draw(screenHeight);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
