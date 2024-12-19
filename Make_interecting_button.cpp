// Make button in raylib
#include <raylib.h>
#include <iostream>

// Button functionallities
class Button
{
public:
    Button(const char *imagePath, Vector2 imagePosition, float scale);
    ~Button();
    void draw();
    bool isPressed(Vector2 mousePos, bool mousePressed);

private:
    Texture2D buttonImg;
    Vector2 buttonPos;
};

// Button methods
Button::Button(const char *imagePath, Vector2 imagePosition, float scale)
{
    this->buttonPos = imagePosition;
    Image buttonImage = LoadImage(imagePath);
    int originalWidth = buttonImage.width;
    int originalHeight = buttonImage.height;

    // Setting new width and hight
    int newWidth = static_cast<int>(originalWidth * scale);
    int newHeight = static_cast<int>(originalHeight * scale);

    ImageResize(&buttonImage, newWidth, newHeight);
    buttonImg = LoadTextureFromImage(buttonImage); // Reloding updated button image
}

// To display button
void Button::draw()
{
    DrawTextureV(buttonImg, buttonPos, WHITE);
}

// Checking key pressed 
bool Button::isPressed(Vector2 mousePos, bool mousePressed)
{
    // Creating rectangle area around button to check collision
    Rectangle rect = {buttonPos.x, buttonPos.y, static_cast<float>(buttonImg.width), static_cast<float>(buttonImg.height)};

    // Checks collisions between mouse curson and button
    if (CheckCollisionPointRec(mousePos, rect) && mousePressed)
        return true;
    else
        return false;
}

// Dellocate the allocated memory
Button::~Button()
{
    UnloadTexture(buttonImg);
}

int main()
{
    InitWindow(800, 600, "Check button press in raylib");

    Texture2D backGround = LoadTexture("Images/background.png");
    Button startButton("Images/start_button.png", {300, 150}, 0.65);
    Button exitButton("Images/exit_button.png", {300, 300}, 0.65);
    bool exit = false;

    while (!WindowShouldClose() && !exit)
    {
        Vector2 mousePos = GetMousePosition();
        bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        if (startButton.isPressed(mousePos, mousePressed))
        {
            std::cout << "Start button is pressed\n";
        }

        if (exitButton.isPressed(mousePos, mousePressed))
        {
            exit = true;
        }

        BeginDrawing();

        ClearBackground(BLACK);
        DrawTexture(backGround, 0, 0, WHITE);
        startButton.draw();
        exitButton.draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
