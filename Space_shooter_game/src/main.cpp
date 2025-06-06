// Space shooter game
#include <raylib.h>
#include <string>
#include "Game.hpp"

std::string formateWithLeadingZeros(int number, int width)
{
    std::string numberText = std::to_string(number);
    int leadingZeros = width - numberText.length();
    return numberText = std::string(leadingZeros, '0') + numberText;
}

int main()
{
    int sWidth = 650, sHeight = 600;
    int offSet = 50;
    InitWindow(sWidth + offSet, sHeight + 2 * offSet, "Space shooter");

    Image gameIcon = LoadImage("src/pixel_ship.png");
    SetWindowIcon(gameIcon);

    Color green = {0, 228, 48, 255};
    Color backgroundColor = {29, 29, 27, 255};
    Texture2D shipImg = LoadTexture("src/pixel_ship.png");

    InitAudioDevice();
    SetTargetFPS(60); // Setting FPS

    Game game; // Creating objectn

    while (!WindowShouldClose())
    {
        UpdateMusicStream(game.music);
        game.handleInput();
        game.update();

        BeginDrawing();

        ClearBackground(backgroundColor);
        DrawRectangleRoundedLines({10, 10, 680, 680}, 0.18f, 20, green);
        DrawLineEx({25, 630}, {675, 630}, 3, green);

        if (game.run)
            DrawText("Level 01", 470, 640, 34, green);
        else
            DrawText("Game Over", 470, 640, 34, green);

        float x = 50.0;
        for (int i = 0; i < game.lives; i++)
        {
            DrawTextureV(shipImg, {x, 645}, WHITE); // Display the remain spaceship
            x += 50;
        }

        DrawText("Score", 50, 15, 34, green);
        std::string scoreText = formateWithLeadingZeros(game.score, 5);
        DrawText(scoreText.c_str(), 50, 50, 34, green);

        DrawText("HIGH-SCORE", 470, 15, 28, green);
        std::string highScoreText = formateWithLeadingZeros(game.highScore, 5);
        DrawText(highScoreText.c_str(), 475, 40, 34, green);

        game.draw();

        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();
    return 0;
}