// Arrange images in the cube
#include <raylib.h>
#include <rlgl.h>
#include <array>
#include <memory>
#include <string>
using namespace std;

constexpr int SCREEN_WIDTH = 1080;
constexpr int SCREEN_HEIGHT = 700;
constexpr float CUBE_SIZE = 6.0f;
constexpr float TEXTURE_SIZE = 600.0f;
constexpr float ROTATION_SPEED = 1.5f;
constexpr float ZOOM_SPEED = 0.2f;

Image CropAndResizeImage(const string &path, int size)
{
    Image img = LoadImage(path.c_str());
    int squareSize = min(img.width, img.height);
    Rectangle crop = {
        (img.width - squareSize) / 2.0f,
        (img.height - squareSize) / 2.0f,
        static_cast<float>(squareSize),
        static_cast<float>(squareSize)};

    ImageCrop(&img, crop);
    ImageResize(&img, size, size);
    ImageFlipVertical(&img); // Fix upside-down textures
    return img;
}

class CubeFace
{
public:
    explicit CubeFace(const string &imagePath)
    {
        Image img = CropAndResizeImage(imagePath, static_cast<int>(TEXTURE_SIZE));
        texture = LoadTextureFromImage(img);
        SetTextureFilter(texture, TEXTURE_FILTER_BILINEAR);
        UnloadImage(img);
    }

    // Unload images 
    ~CubeFace()
    {
        if (texture.id != 0)
            UnloadTexture(texture);
    }

    void DrawFace(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 v4) const
    {
        rlSetTexture(texture.id);
        rlBegin(RL_QUADS);
        rlTexCoord2f(0.0f, 0.0f);
        rlVertex3f(v1.x, v1.y, v1.z);
        rlTexCoord2f(1.0f, 0.0f);
        rlVertex3f(v2.x, v2.y, v2.z);
        rlTexCoord2f(1.0f, 1.0f);
        rlVertex3f(v3.x, v3.y, v3.z);
        rlTexCoord2f(0.0f, 1.0f);
        rlVertex3f(v4.x, v4.y, v4.z);
        rlEnd();
        rlSetTexture(0);
    }

private:
    Texture2D texture = {0};
};

class Cube
{
public:
    explicit Cube(const array<string, 6> &faceImages)
    {
        for (size_t i = 0; i < faceImages.size(); ++i)
            faces[i] = make_unique<CubeFace>(faceImages[i]);
    }

    void Draw(float size) const
    {
        float h = size * 0.5f;

        faces[0]->DrawFace({-h, h, h}, {-h, -h, h}, {h, -h, h}, {h, h, h});     // Front
        faces[1]->DrawFace({h, h, -h}, {h, -h, -h}, {-h, -h, -h}, {-h, h, -h}); // Back
        faces[2]->DrawFace({-h, h, -h}, {-h, -h, -h}, {-h, -h, h}, {-h, h, h}); // Left
        faces[3]->DrawFace({h, h, h}, {h, -h, h}, {h, -h, -h}, {h, h, -h});     // Right
        faces[4]->DrawFace({-h, h, -h}, {-h, h, h}, {h, h, h}, {h, h, -h});     // Top
        faces[5]->DrawFace({-h, -h, -h}, {h, -h, -h}, {h, -h, h}, {-h, -h, h}); // Bottom
    }

private:
    array<unique_ptr<CubeFace>, 6> faces;
};

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Image Cube");
    SetTargetFPS(60);

    array<string, 6> images = {
        "Assets/Img_1.png",
        "Assets/Img_2.png",
        "Assets/Img_3.png",
        "Assets/Img_4.png",
        "Assets/Img_5.png",
        "Assets/Img_6.png"};

    Cube cube(images);

    Camera camera = {0};
    camera.position = {0.0f, 0.0f, 12.0f};
    camera.target = {0.0f, 0.0f, 0.0f};
    camera.up = {0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Vector3 rotation = {0.0f, 0.0f, 0.0f};

    while (!WindowShouldClose())
    {
        // Input Handling
        if (IsKeyDown(KEY_W))
            rotation.x -= ROTATION_SPEED;
        if (IsKeyDown(KEY_S))
            rotation.x += ROTATION_SPEED;
        if (IsKeyDown(KEY_A))
            rotation.y -= ROTATION_SPEED;
        if (IsKeyDown(KEY_D))
            rotation.y += ROTATION_SPEED;
        if (IsKeyDown(KEY_Q))
            camera.position.z -= ZOOM_SPEED;
        if (IsKeyDown(KEY_E))
            camera.position.z += ZOOM_SPEED;

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode3D(camera);

        rlPushMatrix();

        rlRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
        rlRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
        cube.Draw(CUBE_SIZE);

        rlPopMatrix();

        EndMode3D();

        DrawText("W/S/A/D: Rotate  |  Q/E: Zoom", 20, 20, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
