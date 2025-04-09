// Aim practice 
#include <raylib.h>
#include <array>
#include <algorithm>
#include <cmath>
#include <raymath.h>
using namespace std;

constexpr int MAX_PARTICLES = 50;
constexpr int MAX_PARTICLE_SYSTEMS = 100;
constexpr int NUM_BALLOONS = 3;

inline float Randf(float min, float max)
{
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

class Particle
{
public:
    Vector2 pos;
    Vector2 vel;
    float life = 0.0f;

    Particle() = default;

    Particle(Vector2 position)
    {
        pos = position;
        float angle = Randf(0, 2 * PI);
        float speed = Randf(100, 250);
        vel = {cosf(angle) * speed, sinf(angle) * speed};
        life = Randf(0.5f, 1.2f);
    }

    void Update(float dt)
    {
        pos.x += vel.x * dt;
        pos.y += vel.y * dt;
        vel.y += 500 * dt; // gravity
        life -= dt;
    }

    inline void Draw() const
    {
        DrawCircleV(pos, 3, GREEN);
    }

    inline bool IsAlive() const
    {
        return life > 0.0f;
    }
};

class ParticleSystem
{
private:
    array<Particle, MAX_PARTICLES> particles;
    int particleCount = 0;

public:
    ParticleSystem() = default;

    void Spawn(Vector2 position, int amount)
    {
        particleCount = (amount > MAX_PARTICLES) ? MAX_PARTICLES : amount;
        for (int i = 0; i < particleCount; ++i)
        {
            particles[i] = Particle(position);
        }
    }

    void Update(float dt)
    {
        int aliveCount = 0;
        for (int i = 0; i < particleCount; ++i)
        {
            particles[i].Update(dt);
            if (particles[i].IsAlive())
                particles[aliveCount++] = particles[i];
        }
        particleCount = aliveCount;
    }

    inline void Draw() const
    {
        for (int i = 0; i < particleCount; ++i)
            particles[i].Draw();
    }

    inline bool IsEmpty() const
    {
        return particleCount == 0;
    }
};

class Balloon
{
public:
    Vector2 position;
    float radius = 20.0f;

    Balloon() = default;

    inline void RandomizePosition()
    {
        position.x = static_cast<float>(GetRandomValue(100, GetScreenWidth() - 100));
        position.y = static_cast<float>(GetRandomValue(100, GetScreenHeight() - 100));
    }

    inline void Draw() const
    {
        DrawCircleV(position, radius, GREEN);
        DrawLineV({position.x, position.y + radius},
                  {position.x, position.y + radius + 30}, DARKGRAY);
    }

    inline bool IsHit(const Vector2 &mousePos) const
    {
        return CheckCollisionPointCircle(mousePos, position, radius);
    }
};

// Global particle systems
array<ParticleSystem, MAX_PARTICLE_SYSTEMS> particleSystems;
int activeParticleSystemCount = 0;
array<Balloon, NUM_BALLOONS> balloons;
static Vector2 smoothedMousePos = {0, 0};

void DrawCrosshair(int size, Color color)
{
    DrawLine(smoothedMousePos.x - size, smoothedMousePos.y, smoothedMousePos.x + size, smoothedMousePos.y, color);
    DrawLine(smoothedMousePos.x, smoothedMousePos.y - size, smoothedMousePos.x, smoothedMousePos.y + size, color);
}

inline void UpdateActiveParticleSystems(float dt)
{
    int aliveCount = 0;
    for (int i = 0; i < activeParticleSystemCount; ++i)
    {
        particleSystems[i].Update(dt);
        if (!particleSystems[i].IsEmpty())
            particleSystems[aliveCount++] = particleSystems[i];
    }
    activeParticleSystemCount = aliveCount;
}

void RestartGame(array<Balloon, NUM_BALLOONS> &balloons, int &score, float &timeRemaining, bool &gameOver)
{
    for (int i = 0; i < NUM_BALLOONS; ++i)
        balloons[i].RandomizePosition();
    score = 0;
    timeRemaining = 30.0f;
    activeParticleSystemCount = 0;
    gameOver = false;
}

void UpdateGame(array<Balloon, NUM_BALLOONS> &balloons, int &score, float &timeRemaining, bool &gameOver)
{
    const float dt = GetFrameTime();
    Vector2 currentMousePos = GetMousePosition();

    // Valorant style aim 😎
    smoothedMousePos = Vector2Lerp(smoothedMousePos, currentMousePos, 55.0f * dt);

    if (!gameOver)
    {
        timeRemaining -= dt;
        if (timeRemaining <= 0.0f)
        {
            gameOver = true;
            return;
        }

        // Process one balloon per click so no balloon is overwritten.
        for (auto &balloon : balloons)
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && balloon.IsHit(smoothedMousePos))
            {
                if (activeParticleSystemCount < MAX_PARTICLE_SYSTEMS)
                    particleSystems[activeParticleSystemCount++].Spawn(balloon.position, 50);
                balloon.RandomizePosition();
                ++score;
                break;
            }
        }
        UpdateActiveParticleSystems(dt);
    }
    else
    {
        if (IsKeyPressed(KEY_ENTER))
            RestartGame(balloons, score, timeRemaining, gameOver);
    }
}

void DrawGame(const array<Balloon, NUM_BALLOONS> &balloons, int score, float timeRemaining, bool gameOver)
{
    if (!gameOver)
    {
        ClearBackground(RAYWHITE);
        HideCursor();

        for (int i = 0; i < activeParticleSystemCount; ++i)
            particleSystems[i].Draw();

        for (const auto &balloon : balloons)
            balloon.Draw();

        DrawCrosshair(5, BLACK);
        DrawText(TextFormat("Score: %i", score), 10, 10, 20, DARKBLUE);
        DrawText(TextFormat("Time: %.1f", timeRemaining), 10, 40, 20, DARKBLUE);
    }
    else
    {
        ClearBackground(BLACK);
        const int centerX = GetScreenWidth() / 2;
        const int centerY = GetScreenHeight() / 2;

        DrawText("GAME OVER", centerX - MeasureText("GAME OVER", 40) / 2, centerY - 20, 40, RED);
        DrawText(TextFormat("Your Score: %i", score), centerX - MeasureText(TextFormat("Your Score: %i", score), 20) / 2, centerY + 20, 20, GREEN);
        DrawText("Press ENTER to Restart", centerX - MeasureText("Press ENTER to Restart", 20) / 2, centerY + 50, 20, PURPLE);
        DrawText("Press ESC to Exit", centerX - MeasureText("Press ESC to Exit", 20) / 2, centerY + 80, 20, PURPLE);
    }
}

int main()
{
    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "Balloon Blast");
    SetTargetFPS(60);
    SetWindowPosition(0, 0);

    for (int i = 0; i < NUM_BALLOONS; ++i)
        balloons[i].RandomizePosition();

    smoothedMousePos = GetMousePosition();

    int score = 0;
    float timeRemaining = 30.0f;
    bool gameOver = false;

    while (!WindowShouldClose())
    {
        UpdateGame(balloons, score, timeRemaining, gameOver);

        BeginDrawing();
        DrawGame(balloons, score, timeRemaining, gameOver);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
