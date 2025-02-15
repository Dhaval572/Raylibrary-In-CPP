#include <raylib.h>
#include <raymath.h>
#include <cstdlib>
#include <vector>

// Returns a fire-like color based on particle age.
Color GetFireColor(float age)
{
    float hue = 15.0f + 15.0f * age;
    float saturation = 0.9f - 0.3f * age;
    float value = 1.2f - 0.5f * age;
    value += 0.1f * sinf(GetTime() * 30.0f);
    hue = fmodf(hue, 360.0f);
    saturation = Clamp(saturation, 0.0f, 1.0f);
    value = Clamp(value, 0.0f, 1.5f);
    return ColorFromHSV(hue, saturation, value);
}

//---------------------------------------------------------------------------
// FireParticle class: Represents a single fire particle.
// It handles initialization, update, and drawing.
//---------------------------------------------------------------------------
class FireParticle
{
public:
    Vector2 position, velocity;
    float radius, speed, lifetime, initialLifetime, flickerOffset, noiseOffset;

    FireParticle(int screenWidth, int screenHeight)
    {
        Reset(screenWidth, screenHeight);
    }

    // Reset the particle. The emitter remains centered.
    void Reset(int screenWidth, int screenHeight)
    {
        // Keep the same horizontal spread and vertical variation.
        position = { (float)(screenWidth / 2 + (rand() % 100 - 50)),
                     (float)(screenHeight / 2 + (rand() % 20 - 10)) };
        velocity = { 0, 0 };
        // Increased base speed to allow particles to travel higher.
        speed = 5.0f + (float)(rand() % 100) / 40.0f;
        // Increased lifetime so particles live longer.
        initialLifetime = 2.0f + (float)(rand() % 100) / 80.0f;
        lifetime = initialLifetime;
        radius = 4.0f + (float)(rand() % 10) / 4.0f;
        flickerOffset = (float)(rand() % 360);
        noiseOffset = ((float)(rand() % 1000) / 1000.0f) * 2.0f * PI;
    }

    void Update(float dt)
    {
        float age = 1.0f - (lifetime / initialLifetime);
        noiseOffset += 0.05f;
        float turbulence = 0.6f * sinf(noiseOffset) +
                           0.3f * sinf(2.2f * noiseOffset + 1.0f) +
                           0.2f * sinf(3.3f * noiseOffset + 2.0f);
        velocity.x = turbulence * (1.2f - age);
        velocity.y = -speed * (0.8f + 0.3f * (1.0f - age));
        position.x += velocity.x;
        position.y += velocity.y;
        flickerOffset += 8.0f;
        float sizeVariation = 0.7f + 0.5f * sinf(flickerOffset * DEG2RAD);
        radius = (4.0f * (1.0f - age * 0.5f)) * sizeVariation;
        lifetime -= dt * 2.0f;
    }

    void Draw() const
    {
        float age = 1.0f - (lifetime / initialLifetime);
        Color color = GetFireColor(age);
        float alpha = lifetime / initialLifetime;
        DrawCircleV(position, radius, Fade(color, alpha * 0.9f));
        DrawCircleV(position, radius * 2.5f, Fade(color, alpha * 0.25f));
    }

    void DrawSmoke() const
    {
        float age = 1.0f - (lifetime / initialLifetime);
        if (age > 0.4f)
        {
            float smokeAlpha = (age - 0.4f) * 0.5f;
            DrawCircleV(position, radius * 2.0f, Fade(DARKGRAY, smokeAlpha));
        }
    }
};

//---------------------------------------------------------------------------
// FireEffect class: Manages multiple fire particles.
// It updates and draws all the particles.
//---------------------------------------------------------------------------
class FireEffect
{
public:
    std::vector<FireParticle> particles;
    int screenWidth, screenHeight;

    FireEffect(int numParticles, int screenWidth, int screenHeight)
        : screenWidth(screenWidth), screenHeight(screenHeight)
    {
        particles.reserve(numParticles);
        for (int i = 0; i < numParticles; i++)
            particles.emplace_back(screenWidth, screenHeight);
    }

    void Update(float dt)
    {
        for (auto &p : particles)
        {
            p.Update(dt);
            // Allow particles to travel further upward (reset when y < -160)
            if (p.lifetime <= 0.0f || p.position.y < -160.0f)
                p.Reset(screenWidth, screenHeight);
        }
    }

    void Draw() const
    {
        BeginBlendMode(BLEND_ADDITIVE);
        for (const auto &p : particles)
            p.Draw();
        EndBlendMode();

        BeginBlendMode(BLEND_ALPHA);
        for (const auto &p : particles)
            p.DrawSmoke();
        EndBlendMode();
    }
};

//---------------------------------------------------------------------------
// Main function: Initializes the window and runs the fire effect loop.
//---------------------------------------------------------------------------
int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Larger Fire Effect");
    SetTargetFPS(60);

    const int numParticles = 1200;
    FireEffect fire(numParticles, screenWidth, screenHeight);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        fire.Update(dt);

        BeginDrawing();
        ClearBackground(BLACK);
        fire.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
