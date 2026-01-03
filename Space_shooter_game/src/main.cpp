// Space shooter game
#include <raylib.h>
#include <string>
#include "Game.hpp"

std::string FormateWithLeadingZeros(int number, int width)
{
    std::string number_text = std::to_string(number);
    int leading_zeros = width - number_text.length();
    return number_text = std::string(leading_zeros, '0') + number_text;
}

int main()
{
    int s_width = 650, s_height = 600;
    int offset = 50;
    InitWindow(s_width + offset, s_height + 2 * offset, "Space shooter");

    Image game_icon = LoadImage("src/pixel_ship.png");
    SetWindowIcon(game_icon);

    Color green = {0, 228, 48, 255};
    Color background_color = {29, 29, 27, 255};
    Texture2D ship_img = LoadTexture("src/pixel_ship.png");

    InitAudioDevice();
    SetTargetFPS(60); // Setting FPS

    Game game; // Creating objectn

    while (!WindowShouldClose())
    {
        UpdateMusicStream(game.music);
        game.HandleInput();
        game.Update();

        BeginDrawing();

        ClearBackground(background_color);
        DrawRectangleRoundedLines({10, 10, 680, 680}, 0.18f, 20, green);
        DrawLineEx({25, 630}, {675, 630}, 3, green);

        if (game.run)
            DrawText("Level 01", 470, 640, 34, green);
        else
            DrawText("Game Over", 470, 640, 34, green);

        float x = 50.0;
        for (int i = 0; i < game.lives; i++)
        {
            DrawTextureV(ship_img, {x, 645}, WHITE); // Display the remain spaceship
            x += 50;
        }

        DrawText("Score", 50, 15, 34, green);
        std::string score_text = FormateWithLeadingZeros(game.score, 5);
        DrawText(score_text.c_str(), 50, 50, 34, green);

        DrawText("HIGH-SCORE", 470, 15, 28, green);
        std::string high_score_text = 
        FormateWithLeadingZeros(game.high_score, 5);
        DrawText(high_score_text.c_str(), 475, 40, 34, green);

        game.Draw();

        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();
    return 0;
}