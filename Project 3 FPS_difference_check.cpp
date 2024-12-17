// Check difference between fps 
#include <raylib.h>

void MoveCircle(Vector2 &circlePos, float speed, float deltaTime, float &timer, float fps)
{
    int radius = 30;
    timer += deltaTime;
    if (timer >= 1.0f / fps) // Move when timer exceeds frame rate interval
    {
        circlePos.x += speed * deltaTime; 

        if (circlePos.x > GetScreenWidth() - radius) 
            circlePos.x = radius; // Reset to start position
        
        timer = 0.0f; // Reset the timer
    }
}

int main()
{
    InitWindow(800, 600, "Moving Circles with Different FPS");

    int radius = 30;

    // Define initial circle positions and speeds
    Vector2 circle1Pos = { 0, 100 }; 
    Vector2 circle2Pos = { 0, 300 }; 
    Vector2 circle3Pos = { 0, 500 }; 

    float speed1 = 100.0f; // Speed for Circle 1 (moves every 1/30 seconds)
    float speed2 = 200.0f; // Speed for Circle 2 (moves every 1/60 seconds)
    float speed3 = 300.0f; // Speed for Circle 3 (moves every 1/120 seconds)

    // Time trackers for each circle
    float timer1 = 0.0f;
    float timer2 = 0.0f;
    float timer3 = 0.0f;

    // Set standard FPS for the window
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Get the elapsed time since the last frame
        float deltaTime = GetFrameTime();

        // Move each circle with its own FPS
        MoveCircle(circle1Pos, speed1, deltaTime, timer1, 30.0f); 
        MoveCircle(circle2Pos, speed2, deltaTime, timer2, 60.0f); 
        MoveCircle(circle3Pos, speed3, deltaTime, timer3, 120.0f); 

        BeginDrawing();
    
        ClearBackground(BLACK);

        // Draw the circles with his current fps 
        DrawText("Moves with 30 fps", 0, 0, radius, RED);
        DrawCircleV(circle1Pos, 30, RED);

        DrawText("Moves with 60 fps", 0, 200, radius, GREEN);
        DrawCircleV(circle2Pos, 30, GREEN);

        DrawText("Moves with 120 fps", 0, 400, radius, BLUE);
        DrawCircleV(circle3Pos, 30, BLUE);

        EndDrawing();
    }

    CloseWindow(); 

    return 0;
}
