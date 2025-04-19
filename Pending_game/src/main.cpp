#include <raylib.h>
#include "Game.hpp"

int main()
{
    const int sWidth = 1200, sHeight = 600;
    InitWindow(sWidth, sHeight, "Walking Animation");
  
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose())
    {
        game.Update();
        game.updateAnimation();

        BeginDrawing();
        ClearBackground(BLACK); 

        game.Draw();
        
        EndDrawing();
    }

    CloseWindow(); 
    return 0;
}