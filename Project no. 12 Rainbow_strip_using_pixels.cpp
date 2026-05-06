// rainbow color strips using pixels
#include <raylib.h>
#include <stdlib.h> 
#include <time.h>   

constexpr int MAX_STARS = 9999;
constexpr int NUM_STRIPS = 7;
constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 700;

// Pre-calculate strip bounds
constexpr int STRIP_STARTS[NUM_STRIPS] = {0, 100, 200, 300, 400, 500, 600};
constexpr int STRIP_ENDS[NUM_STRIPS] = {100, 200, 300, 400, 500, 600, 700};

struct Star
{
    float x, y;
    float speed;
};

void InitStars(Star stars[], int count, int min, int max)
{
    // Evenly distribute stars within the vertical range of the strip
    for (int i = 0; i < count; i++)
    {
        stars[i].x = static_cast<float>((rand() % SCREEN_WIDTH));
        stars[i].y = static_cast<float>((min + (rand() % (max - min + 1)))); // Ensure y is in the strip's vertical range
        stars[i].speed = static_cast<float>((rand() % 5 + 1)); // Random speed (up to 5)
    }
}

// Update the star's Positions
void UpdateStars(Star stars[], int count, int min, int max)
{
    for (int i = 0; i < count; i++)
    {
        stars[i].y += stars[i].speed; // Move the star down

        // If any star goes off the screen at the bottom
        if (stars[i].y > max)
        {
            // Reset to the top side of the current strip, while ensuring it's still within the strip's range
            stars[i].x = static_cast<float>((rand() % SCREEN_WIDTH));
            stars[i].y = static_cast<float>((min + (rand() % (max - min + 1)))); // Reset within the vertical range of the strip
            stars[i].speed = static_cast<float>((rand() % 5 + 1)); // Re-randomize speed
        }
    }
}

void DrawStars(Star stars[], int count, Color color, int min, int max)
{
    // Draw each star, but only those within the specified y-range 
    //(ensuring it's in the right strip)
    for (int i = 0; i < count; i++)
    {
        if (stars[i].y >= min && stars[i].y <= max)
        {
            DrawPixel(static_cast<int>(stars[i].x), static_cast<int>(stars[i].y), color);
        }
    }
}

// Helper function to update all strips
void UpdateAllStrips(Star stars[NUM_STRIPS][MAX_STARS])
{
    for (int i = 0; i < NUM_STRIPS; i++)
    {
        UpdateStars(stars[i], MAX_STARS, STRIP_STARTS[i], STRIP_ENDS[i]);
    }
}

// Helper function to draw all strips
void DrawAllStrips(Star stars[NUM_STRIPS][MAX_STARS], Color colors[NUM_STRIPS])
{
    for (int i = 0; i < NUM_STRIPS; i++)
    {
        DrawStars(stars[i], MAX_STARS, colors[i], STRIP_STARTS[i], STRIP_ENDS[i]);
    }
}

// Helper function to initialize all strips
void InitAllStrips(Star stars[NUM_STRIPS][MAX_STARS])
{
    for (int i = 0; i < NUM_STRIPS; i++)
    {
        InitStars(stars[i], MAX_STARS, STRIP_STARTS[i], STRIP_ENDS[i]);
    }
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "rainbow Strip design");

    SetTargetFPS(120);
    srand(time(NULL)); 
    Color rainbow[NUM_STRIPS] =
    {
        RED,
        ORANGE,
        YELLOW,
        GREEN,
        BLUE,
        DARKBLUE,
        PURPLE,
    };

    Star stars[NUM_STRIPS][MAX_STARS];
    InitAllStrips(stars);

    while (!WindowShouldClose())
    {
        UpdateAllStrips(stars);
        BeginDrawing();
        ClearBackground(BLACK);
        DrawAllStrips(stars, rainbow);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
