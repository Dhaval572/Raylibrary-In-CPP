// Rainbow stars
#include <raylib.h>
#include <stdlib.h> // For rand() and srand()
#include <time.h>   // For time()

#define MAX_STARS 1000
#define NUM_STRIPS 7

typedef struct Star
{
    float x, y;
    float speed;
} Star;

void InitStars(Star stars[], int count, int screenWidth, int screenHeight)
{
    for (int i = 0; i < count; i++)
    {
        stars[i].x = (float)(rand() % screenWidth);  // Random horizontal position
        stars[i].y = (float)(rand() % screenHeight); // Random vertical position
        stars[i].speed = (float)(rand() % 5 + 1);    // Random speed (up to 5)
    }
}

void UpdateStars(Star stars[], int count, int screenWidth, int screenHeight)
{
    for (int i = 0; i < count; i++)
    {
        stars[i].y += stars[i].speed; // Move the star down

        if (stars[i].y > screenHeight) // Reset star when it goes off the screen
        {
            stars[i].x = (float)(rand() % screenWidth);
            stars[i].y = 0; // Reset to the top side
            stars[i].speed = (float)(rand() % 5 + 1);
        }
    }
}

void DrawStars(Star stars[], int count, Color color)
{
    for (int i = 0; i < count; i++)
    {
        DrawPixel((int)stars[i].x, (int)stars[i].y, color);
    }
}

int main()
{
    InitWindow(800, 700, "Rainbow Starfield Simulation");

    SetTargetFPS(60);

    srand(time(NULL)); // Seed the random number generator

    Color rainBow[NUM_STRIPS] =
        {
            RED,
            ORANGE,
            YELLOW,
            GREEN,
            BLUE,
            DARKBLUE,
            PURPLE,
        };

    Star stars[NUM_STRIPS][MAX_STARS]; // 2D array for 7 strips of stars

    // Initialize the stars for each color strip
    for (int i = 0; i < NUM_STRIPS; i++)
    {
        InitStars(stars[i], MAX_STARS, 800, 700);
    }

    while (!WindowShouldClose())
    {
        // Update the stars for each color strip
        for (int i = 0; i < NUM_STRIPS; i++)
        {
            UpdateStars(stars[i], MAX_STARS, 800, 700);
        }

        BeginDrawing();
        ClearBackground(BLACK);

        // Draw the stars for each color strip
        for (int i = 0; i < NUM_STRIPS; i++)
        {
            DrawStars(stars[i], MAX_STARS, rainBow[i]);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
