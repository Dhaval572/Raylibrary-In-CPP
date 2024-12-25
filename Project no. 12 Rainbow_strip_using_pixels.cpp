// Rainbow color strips using pixels
#include <raylib.h>
#include <stdlib.h> // For rand() and srand()
#include <time.h>   // For time()

#define MAX_STARS 9999
#define NUM_STRIPS 7

typedef struct Star
{
    float x, y;
    float speed;
} Star;

void InitStars(Star stars[], int count, int screenWidth, int min, int max)
{
    // Evenly distribute stars within the vertical range of the strip
    for (int i = 0; i < count; i++)
    {
        stars[i].x = (float)(rand() % screenWidth);
        stars[i].y = (float)(min + (rand() % (max - min + 1))); // Ensure y is in the strip's vertical range
        stars[i].speed = (float)(rand() % 5 + 1); // Random speed (up to 5)
    }
}

// Update the star's Positions
void UpdateStars(Star stars[], int count, int screenWidth, int min, int max)
{
    for (int i = 0; i < count; i++)
    {
        stars[i].y += stars[i].speed; // Move the star down

        // If any star goes off the screen at the bottom
        if (stars[i].y > max)
        {
            // Reset to the top side of the current strip, while ensuring it's still within the strip's range
            stars[i].x = (float)(rand() % screenWidth);
            stars[i].y = (float)(min + (rand() % (max - min + 1))); // Reset within the vertical range of the strip
            stars[i].speed = (float)(rand() % 5 + 1); // Re-randomize speed
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
            DrawPixel((int)stars[i].x, (int)stars[i].y, color);
        }
    }
}

int main()
{
    InitWindow(800, 700, "Rainbow Strip design");

    SetTargetFPS(120);

    srand(time(NULL)); 

    // Define the colors for the rainbow
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

    // 2D array to hold stars for each strip
    Star stars[NUM_STRIPS][MAX_STARS];

    // Initialize the stars for each strip with specific vertical ranges
    for (int i = 0; i < NUM_STRIPS; i++)
    {
        int yStart = i * 100;     // Vertical start of the strip (0, 100, 200, ...)
        int yEnd = (i + 1) * 100; // Vertical end of the strip (100, 200, 300, ...)

        // Initialize stars for each strip, ensuring they are evenly distributed
        InitStars(stars[i], MAX_STARS, 800, yStart, yEnd); // Initialize stars for each strip
    }

    while (!WindowShouldClose())
    {
        // Update the stars for each color strip
        for (int i = 0; i < NUM_STRIPS; i++)
        {
            int yStart = i * 100;     // Vertical start of the strip (0, 100, 200, ...)
            int yEnd = (i + 1) * 100; // Vertical end of the strip (100, 200, 300, ...)
            UpdateStars(stars[i], MAX_STARS, 800, yStart, yEnd); // Update stars for each strip
        }

        BeginDrawing();
        ClearBackground(BLACK);

        // Draw the stars for each color strip
        for (int i = 0; i < NUM_STRIPS; i++)
        {
            int yStart = i * 100;     // Vertical start of the strip (0, 100, 200, ...)
            int yEnd = (i + 1) * 100; // Vertical end of the strip (100, 200, 300, ...)
            DrawStars(stars[i], MAX_STARS, rainBow[i], yStart, yEnd); // Draw stars with the corresponding color
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
