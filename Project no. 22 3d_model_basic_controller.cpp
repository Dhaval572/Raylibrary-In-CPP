// 3d object control
#include <raylib.h>
#include <raymath.h>

// Input handling
void UpdateCamera(Camera3D *camera, float *cameraAngleX, float *cameraAngleY, float *cameraDistance, Vector3 cubePosition)
{
    // Update camera controls: W/A/S/D for orbit, Q/E for zoom
    if (IsKeyDown(KEY_D))
        *cameraAngleX += 1.0f;
    if (IsKeyDown(KEY_A))
        *cameraAngleX -= 1.0f;
    if (IsKeyDown(KEY_W))
        *cameraAngleY += 1.0f;
    if (IsKeyDown(KEY_S))
        *cameraAngleY -= 1.0f;
    if (IsKeyDown(KEY_Q))
        *cameraDistance += 0.2f;
    if (IsKeyDown(KEY_E))
        *cameraDistance -= 0.2f;

    // Clamp the values to ensure the camera behaves as expected
    *cameraDistance = Clamp(*cameraDistance, 5.0f, 50.0f);
    *cameraAngleY = Clamp(*cameraAngleY, -89.0f, 89.0f);

    // Update the camera position based on spherical coordinates conversion
    camera->position.x = cubePosition.x + (*cameraDistance) * cos(DEG2RAD * (*cameraAngleX)) * cos(DEG2RAD * (*cameraAngleY));
    camera->position.y = cubePosition.y + (*cameraDistance) * sin(DEG2RAD * (*cameraAngleY));
    camera->position.z = cubePosition.z + (*cameraDistance) * sin(DEG2RAD * (*cameraAngleX)) * cos(DEG2RAD * (*cameraAngleY));
}

// Function to draw the 3D scene and on-screen text.
void DrawScene(Camera3D camera, Vector3 cubePosition, float cubeScale, Color cubeColor)
{
    BeginMode3D(camera);
    DrawCubeWiresV(cubePosition,
                   (Vector3){2.0f * cubeScale, 2.0f * cubeScale, 2.0f * cubeScale},
                   DARKGRAY);
    DrawCubeV(cubePosition,
              (Vector3){2.0f * cubeScale, 2.0f * cubeScale, 2.0f * cubeScale},
              Fade(cubeColor, 0.4f));
    DrawGrid(10, 1.0f);
    EndMode3D();

    DrawText("Keyboard Controls:", 10, 50, 20, DARKGRAY);
    DrawText("W/A/S/D: Orbit camera", 10, 80, 20, DARKGRAY);
    DrawText("Q/E: Zoom out/in", 10, 110, 20, DARKGRAY);
}

int main(void)
{
    constexpr int screenWidth = 1280;
    constexpr int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "3D Gesture Visualizer (Keyboard Controls)");
    SetWindowPosition(40, 40);

    Camera3D camera = {0};
    camera.position = (Vector3){10.0f, 10.0f, 10.0f};
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Vector3 cubePosition = {0};
    float cubeScale = 1.0f;
    Color cubeColor = BLUE;

    // Camera control variables
    float cameraDistance = 20.0f;
    float cameraAngleX = 45.0f;
    float cameraAngleY = 30.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, &cameraAngleX, &cameraAngleY, &cameraDistance, cubePosition);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawScene(camera, cubePosition, cubeScale, cubeColor);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
