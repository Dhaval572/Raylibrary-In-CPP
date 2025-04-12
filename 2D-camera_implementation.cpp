// Implement the 2d camera in raylib
#include <raylib.h>

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "2D Camera Example");

    Camera2D camera = {0};
    camera.offset = {(float)screenWidth / 2.0f, (float)screenHeight / 2.0f};
    camera.target = camera.offset;
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_RIGHT))
            camera.target.x += 2.0f;
        if (IsKeyDown(KEY_LEFT))
            camera.target.x -= 2.0f;
        if (IsKeyDown(KEY_UP))
            camera.target.y -= 2.0f;
        if (IsKeyDown(KEY_DOWN))
            camera.target.y += 2.0f;

        camera.zoom += (float)GetMouseWheelMove() * 0.1f;
        if (camera.zoom < 0.1f)
            camera.zoom = 0.1f;
        if (camera.zoom > 3.0f)
            camera.zoom = 3.0f;

        if (IsKeyDown(KEY_Q))
            camera.rotation -= 1.0f;
        if (IsKeyDown(KEY_E))
            camera.rotation += 1.0f;

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);

        DrawText("Use arrow keys to move the camera", 10, 10, 20, GREEN);
        DrawText("Use mouse wheel to zoom", 10, 40, 20, GREEN);
        DrawText("Use Q and E keys to rotate", 10, 70, 20, GREEN);

        DrawRectangle((int)camera.target.x - 25, (int)camera.target.y - 25, 50, 50, BLUE);
        DrawRectangle(500, 500, 100, 100, RED);

        EndMode2D();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
