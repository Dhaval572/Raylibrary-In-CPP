// 3D FPS Hall view
#include <raylib.h>
#include <raymath.h>
#include <cmath>

// 3D Model representation for the player
class PlayerModel
{
public:
    Vector3 dimensions;
    Color color;
    float eyeHeight;

    // Use inline initialization for brevity.
    PlayerModel(Vector3 size = {1.0f, 2.0f, 1.0f}, Color color = BLUE, float eyeHeight = 0.8f)
        : dimensions(size), color(color), eyeHeight(eyeHeight) {}

    inline void Render(const Vector3 &pos) const
    {
        DrawCube(pos, dimensions.x, dimensions.y, dimensions.z, color);
        DrawCubeWires(pos, dimensions.x, dimensions.y, dimensions.z, DARKBLUE);
    }
};

// Axis-Aligned Bounding Box for collision
struct BoundingBox3D
{
    Vector3 min;
    Vector3 max;

    inline bool IsPointInside(const Vector3 &p) const
    {
        return (p.x >= min.x && p.x <= max.x &&
                p.y >= min.y && p.y <= max.y &&
                p.z >= min.z && p.z <= max.z);
    }

    inline bool FitsInside(const BoundingBox3D &box) const
    {
        return (box.min.x >= min.x && box.max.x <= max.x &&
                box.min.y >= min.y && box.max.y <= max.y &&
                box.min.z >= min.z && box.max.z <= max.z);
    }
};

class PlayerController
{
public:
    Vector3 position;
    Camera3D camera;
    float moveSpeed;
    float lookSensitivity;
    float yaw;
    float pitch;
    PlayerModel model;
    Vector3 velocity;
    float bobPhase;
    float bobAmplitude;
    float bobFrequency;
    bool isMoving;
    float smoothedPitch;
    float smoothedYaw;

    Vector3 moveInput;

    PlayerController(Vector3 startPos)
        : position(startPos), moveSpeed(5.0f), lookSensitivity(0.07f), yaw(0.0f), pitch(0.0f),
          model(), velocity({0, 0, 0}), bobPhase(0), bobAmplitude(0.015f), bobFrequency(10.0f),
          isMoving(false), smoothedPitch(0), smoothedYaw(0), moveInput({0, 0, 0})
    {
        InitCamera();
    }

    void Update(const BoundingBox3D &bounds)
    {
        float delta = GetFrameTime();

        UpdateMouseLook();
        UpdateMovementInput();
        UpdateVelocity(delta);
        UpdatePosition(delta, bounds);
        UpdateHeadBobbing(delta);
        UpdateCamera();
    }

    inline void RenderCrosshair() const
    {
        Vector2 center = {(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};
        const int crosshairSize = 4;
        const Color crosshairColor = DARKPURPLE;
        const int thickness = 2;

        // Drawing horizontal lines with a gap
        DrawLineEx({center.x - crosshairSize - 4, center.y},
                   {center.x - 4, center.y}, thickness, crosshairColor);
        DrawLineEx({center.x + 4, center.y},
                   {center.x + crosshairSize + 4, center.y}, thickness, crosshairColor);

        // Drawing vertical lines with a gap
        DrawLineEx({center.x, center.y - crosshairSize - 4},
                   {center.x, center.y - 4}, thickness, crosshairColor);
        DrawLineEx({center.x, center.y + 4},
                   {center.x, center.y + crosshairSize + 4}, thickness, crosshairColor);
    }

    inline void Begin3DView() const
    {
        BeginMode3D(camera);
    }

    inline void End3DView() const
    {
        EndMode3D();
    }

private:
    void InitCamera()
    {
        camera.position = Vector3Add(position, {0.0f, 1.7f, 0.0f});
        camera.target = Vector3Add(camera.position, {0.0f, 0.0f, 1.0f});
        camera.up = {0.0f, 1.0f, 0.0f};
        camera.fovy = 75.0f;
        camera.projection = CAMERA_PERSPECTIVE;
    }

    void UpdateMouseLook()
    {
        Vector2 mouseMove = GetMouseDelta();

        yaw -= mouseMove.x * lookSensitivity;
        pitch -= mouseMove.y * lookSensitivity;
        pitch = Clamp(pitch, -89.0f, 89.0f);

        // Smoothing for more fluid mouse movement
        constexpr float smoothFactor = 0.7f;
        smoothedYaw = Lerp(smoothedYaw, yaw, smoothFactor);
        smoothedPitch = Lerp(smoothedPitch, pitch, smoothFactor);
    }

    void UpdateMovementInput()
    {
        moveInput = {0, 0, 0};

        Vector3 forward = GetForwardVector();
        Vector3 right = GetRightVector();

        if (IsKeyDown(KEY_W))
            moveInput = Vector3Add(moveInput, forward);
        if (IsKeyDown(KEY_S))
            moveInput = Vector3Subtract(moveInput, forward);
        if (IsKeyDown(KEY_A))
            moveInput = Vector3Subtract(moveInput, right);
        if (IsKeyDown(KEY_D))
            moveInput = Vector3Add(moveInput, right);

        // Normalize if there is any input
        if (Vector3Length(moveInput) > 0.0f)
        {
            moveInput = Vector3Normalize(moveInput);
            isMoving = true;
        }
        else
        {
            isMoving = false;
        }
    }

    void UpdateVelocity(float delta)
    {
        // Adjust speed when sprinting
        float currentSpeed = (IsKeyDown(KEY_LEFT_SHIFT)) ? moveSpeed * 2.5f : moveSpeed;
        constexpr float accelerationMoving = 15.0f;
        constexpr float accelerationStopping = 20.0f;
        float acceleration = isMoving ? accelerationMoving : accelerationStopping;

        Vector3 targetVel = Vector3Scale(moveInput, currentSpeed);

        velocity.x = Lerp(velocity.x, targetVel.x, acceleration * delta);
        velocity.z = Lerp(velocity.z, targetVel.z, acceleration * delta);
    }

    void UpdatePosition(float delta, const BoundingBox3D &bounds)
    {
        Vector3 proposedPos = Vector3Add(position, Vector3Scale(velocity, delta));

        // Use a fixed half-size box for collision
        constexpr Vector3 halfModel = {0.4f, 0.9f, 0.4f};
        BoundingBox3D playerBox = {
            Vector3Subtract(proposedPos, halfModel),
            Vector3Add(proposedPos, halfModel)};

        if (bounds.FitsInside(playerBox))
        {
            position = proposedPos;
        }
        else
        {
            TrySlideAlongWalls(proposedPos, halfModel, bounds);
        }
    }

    void TrySlideAlongWalls(const Vector3 &proposedPos, const Vector3 &halfModel, const BoundingBox3D &bounds)
    {
        Vector3 proposedX = {proposedPos.x, position.y, position.z};
        BoundingBox3D boxX = {
            Vector3Subtract(proposedX, halfModel),
            Vector3Add(proposedX, halfModel)};
        if (bounds.FitsInside(boxX))
        {
            position = proposedX;
            return;
        }

        Vector3 proposedZ = {position.x, position.y, proposedPos.z};
        BoundingBox3D boxZ = {
            Vector3Subtract(proposedZ, halfModel),
            Vector3Add(proposedZ, halfModel)};
        if (bounds.FitsInside(boxZ))
        {
            position = proposedZ;
        }
    }

    void UpdateHeadBobbing(float delta)
    {
        if (isMoving)
        {
            // Scale bobbing phase based on movement speed and delta time.
            bobPhase += bobFrequency * delta * (Vector3Length(velocity) / moveSpeed);
            if (bobPhase > 2 * PI)
                bobPhase -= 2 * PI;
        }
        else
        {
            // Smoothly return to zero bobbing when not moving.
            bobPhase = Lerp(bobPhase, 0.0f, 5.0f * delta);
            if (fabs(bobPhase) < 0.01f)
                bobPhase = 0.0f;
        }
    }

    void UpdateCamera()
    {
        float bobOffset = isMoving ? sinf(bobPhase) * bobAmplitude : 0.0f;
        camera.position = Vector3Add(position, {0.0f, 1.7f + bobOffset, 0.0f});
        Vector3 forward = GetForwardVector();
        camera.target = Vector3Add(camera.position, forward);
    }

    inline Vector3 GetForwardVector() const
    {
        float radYaw = DEG2RAD * smoothedYaw;
        float radPitch = DEG2RAD * smoothedPitch;

        Vector3 forward = {
            cosf(radPitch) * sinf(radYaw),
            sinf(radPitch),
            cosf(radPitch) * cosf(radYaw)};
        return Vector3Normalize(forward);
    }

    inline Vector3 GetRightVector() const
    {
        // Compute right vector via the cross product of forward and global up.
        return Vector3Normalize(Vector3CrossProduct(GetForwardVector(), {0.0f, 1.0f, 0.0f}));
    }
};

void InitWindowSettings()
{
    const int screenWidth = GetMonitorWidth(0);
    const int screenHeight = GetMonitorHeight(0);
    InitWindow(screenWidth, screenHeight, "3D FPS in Hallway");
    SetTargetFPS(144);
    DisableCursor();
}

void DrawEnvironment()
{
    // Floor
    Color floorColor = ColorFromHSV(200.0f, 0.4f, 0.9f);
    DrawCube({0.0f, 0.0f, 20.0f}, 9.0f, 1.0f, 50.0f, Fade(floorColor, 0.8f));

    // Left wall
    Color leftWallColor = ColorFromHSV(30.0f, 0.6f, 0.8f);
    DrawCube({-5.0f, 2.5f, 20.0f}, 1.0f, 5.0f, 50.0f, Fade(leftWallColor, 0.7f));

    // Right wall
    Color rightWallColor = ColorFromHSV(210.0f, 0.5f, 0.85f);
    DrawCube({5.0f, 2.5f, 20.0f}, 1.0f, 5.0f, 50.0f, Fade(rightWallColor, 0.7f));

    // Ceiling
    Color ceilingColor = ColorFromHSV(300.0f, 0.3f, 0.95f);
    DrawCube({0.0f, 5.0f, 20.0f}, 9.0f, 1.0f, 50.0f, Fade(ceilingColor, 0.6f));

    // Back wall
    Color backWallColor = ColorFromHSV(0.0f, 1.0f, 0.7f);
    DrawCube({0.0f, 2.5f, 45.5f}, 9.0f, 5.0f, 1.0f, Fade(backWallColor, 0.8f));

    // Front wall
    Color frontWallColor = ColorFromHSV(180.0f, 0.7f, 0.8f);
    DrawCube({0.0f, 2.5f, -5.5f}, 9.0f, 5.0f, 1.0f, Fade(frontWallColor, 0.8f));

    // Decorative glowing pillars along the sides
    for (float z = -5.0f; z <= 45.0f; z += 10.0f)
    {
        Color pillarColor = ColorFromHSV(120.0f + z * 2.0f, 0.5f, 0.9f);
        DrawCube({-4.0f, 1.0f, z}, 0.3f, 2.0f, 0.3f, Fade(pillarColor, 0.8f));
        DrawCube({4.0f, 1.0f, z}, 0.3f, 2.0f, 0.3f, Fade(pillarColor, 0.8f));
    }
}

int main()
{
    InitWindowSettings();

    PlayerController player({0.0f, 1.0f, 0.0f});
    BoundingBox3D hallwayBounds = {
        {-4.5f, 0.0f, -5.0f},
        {4.5f, 5.0f, 45.0f}};

    while (!WindowShouldClose())
    {
        player.Update(hallwayBounds);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Render 3D scene
        player.Begin3DView();
        DrawEnvironment();
        player.End3DView();

        player.RenderCrosshair();
        DrawText("Move: WASD | Sprint: SHIFT | Camera: Mouse", 20, 20, 20, BLACK);
        DrawFPS(20, 40);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
