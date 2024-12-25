// Star field simulation
#include <raylib.h>
#include <stdlib.h> // For rand() and srand()
#include <time.h>   // For time()

#define MAX_STARS 9999

typedef struct Star
{
    float x, y;
    float speed;
} Star;

void InitStars(Star stars[], int count, int screenWidth, int screenHeight)
{
    // Setting the x and y position and speed of the each pixels
    for (int i = 0; i < count; i++)
    {
        stars[i].x = (float)(rand() % screenWidth);  // Random horizontal position
        stars[i].y = (float)(rand() % screenHeight); // Random vertical position
        stars[i].speed = (float)(rand() % 5 + 1);    // Random Speed ( up to 5 )
    }
}

// Update the star's Positions
void UpdateStars(Star stars[], int count, int screenWidth, int screenHeight)
{
    for (int i = 0; i < count; i++)
    {
        stars[i].y += stars[i].speed; // Move the pixel down

        // If any star gone off the screen at downSide
        if (stars[i].y > screenHeight)
        {
            stars[i].x = (float)(rand() % screenWidth); 
            stars[i].y = 0;           // Reset to the upper sode
            stars[i].speed = (float)(rand() % 5 + 1);
        }
    }
}

void DrawStars(Star stars[], int count)
{

    // Draw each pixels throw the for loop
    for (int i = 0; i < count; i++)
    {
        DrawPixel((int)stars[i].x, (int)stars[i].y, ORANGE);
    }
}

int main()
{
    int screenWidth = 300;
    int screenHeight = 300;

    InitWindow(screenWidth, screenHeight, "Starfield Simulation");

    SetTargetFPS(120);

    srand(time(NULL)); // Seed the random number generator

    Star stars[MAX_STARS]; // Making stars
    InitStars(stars, MAX_STARS, screenWidth, screenHeight);

    while (!WindowShouldClose())
    {
        UpdateStars(stars, MAX_STARS, screenWidth, screenHeight);

        BeginDrawing();

        ClearBackground(BLACK);
        DrawStars(stars, MAX_STARS);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
