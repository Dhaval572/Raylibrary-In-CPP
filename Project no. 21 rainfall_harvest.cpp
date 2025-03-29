// Rain water
#include <raylib.h>
#include <vector>
#include <algorithm>
using namespace std;

struct WaterParticle
{
    Vector2 position;
    float speed;
    static constexpr float size = 3.0f;
};

class WaterSystem
{
public:
    vector<WaterParticle> particles;
    vector<float> waterSurface;

    // Initialize the water surface with 0 height at every x.
    WaterSystem(const int screenWidth)
    {
        waterSurface.resize(screenWidth, 0.0f);
    }

    // Update droplets and accumulate them on the water surface.
    void Update(const float deltaTime, const int screenHeight)
    {
        for (auto &p : particles)
        {
            p.position.y += p.speed * 999 * deltaTime;

            // When droplet reaches (or passes) the bottom:
            if (p.position.y + WaterParticle::size >= screenHeight)
            {
                AccumulateDroplet(p);

                // Move droplet off-screen for removal.
                p.position.y = screenHeight + 100;
            }
        }
        RemoveOffScreenDroplets(screenHeight);
        SmoothWaterSurface();
    }

    // Draw droplets and the accumulated water "river".
    void Draw(const int screenHeight) const
    {
        // Draw falling droplets as blue circles.
        for (const auto &p : particles)
        {
            DrawCircleV(p.position, WaterParticle::size, SKYBLUE);
        }
        
        // Draw the accumulated water as vertical lines along the bottom.
        for (int x = 0; x < static_cast<int>(waterSurface.size()); x++)
        {
            const float height = waterSurface[x];
            if (height > 0)
            {
                DrawLine(x, screenHeight - static_cast<int>(height), x, screenHeight, Fade(BLUE, 0.8f));
            }
        }
    }

private:
    void SmoothWaterSurface()
    {
        for (size_t x = 1; x < waterSurface.size() - 1; x++)
        {
            waterSurface[x] = (waterSurface[x - 1] + waterSurface[x] + waterSurface[x + 1]) * (1.0f / 3.0f);
        }
    }

    void AccumulateDroplet(const WaterParticle &p)
    {
        const int dropletX = static_cast<int>(p.position.x);
        const int dropletRadius = static_cast<int>(WaterParticle::size);

        // Add water to the surface directly under the droplet.
        for (int x = dropletX - dropletRadius; x <= dropletX + dropletRadius; x++)
        {
            if (x >= 0 && x < static_cast<int>(waterSurface.size()))
            {
                waterSurface[x] += WaterParticle::size;
            }
        }
    }

    // Remove droplets that have fallen off-screen.
    void RemoveOffScreenDroplets(const int screenHeight)
    {
        particles.erase(remove_if(particles.begin(), particles.end(),
                                  [screenHeight](const WaterParticle &p)
                                  {
                                      return p.position.y > screenHeight;
                                  }),
                        particles.end());
    }
};

int main()
{
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Rainfall Harvest");

    SetTargetFPS(60);

    WaterSystem waterSystem(screenWidth);

    while (!WindowShouldClose())
    {
        const float deltaTime = GetFrameTime();

        WaterParticle p;
        p.position = {static_cast<float>(GetRandomValue(0, screenWidth - 1)), -10.0f};
        p.speed = static_cast<float>(GetRandomValue(150, 249)) / 100.0f;
        waterSystem.particles.push_back(p);
        waterSystem.Update(deltaTime, screenHeight);

        BeginDrawing();
        ClearBackground(BLACK);
        waterSystem.Draw(screenHeight);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
