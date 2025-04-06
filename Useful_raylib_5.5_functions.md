# Useful raylib Functions (v5.5)

## Core Functions
- `InitWindow(int width, int height, const char *title)`
- `WindowShouldClose(void)`
- `SetTargetFPS(int fps)`
- `GetFrameTime(void)`
- `GetTime(void)`
- `CloseWindow(void)`

## Drawing
- `BeginDrawing(void)`
- `EndDrawing(void)`
- `ClearBackground(Color color)`
- `DrawText(const char *text, int posX, int posY, int fontSize, Color color)`
- `DrawCircle(int centerX, int centerY, float radius, Color color)`
- `DrawRectangle(int posX, int posY, int width, int height, Color color)`
- `DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color)`

## Input Handling
- `IsKeyPressed(int key)`
- `IsKeyDown(int key)`
- `IsMouseButtonPressed(int button)`
- `GetMousePosition(void)`

## Time and Timers
- `WaitTime(double seconds)`
- `GetFrameTime(void)`
- `GetTime(void)`

## Textures
- `LoadTexture(const char *fileName)`
- `DrawTexture(Texture2D texture, int posX, int posY, Color tint)`
- `UnloadTexture(Texture2D texture)`

## Audio
- `InitAudioDevice(void)`
- `LoadSound(const char *fileName)`
- `PlaySound(Sound sound)`
- `UnloadSound(Sound sound)`
- `CloseAudioDevice(void)`

## Math (from raymath.h)
- `Vector2 Vector2Add(Vector2 v1, Vector2 v2)`
- `Vector2 Vector2Subtract(Vector2 v1, Vector2 v2)`
- `float Vector2Length(Vector2 v)`

## Utilities
- `TakeScreenshot(const char *fileName)`
- `SetWindowTitle(const char *title)`

---

# Notes
- **Timing**: `GetFrameTime()` is great for frame-independent movement.
- **Textures**: Always `UnloadTexture()` when done to avoid memory leaks.
- **Audio**: Remember `InitAudioDevice()` before loading sounds.
- **Input**: `IsKeyPressed()` only fires once per press, while `IsKeyDown()` stays true while held down.

---
