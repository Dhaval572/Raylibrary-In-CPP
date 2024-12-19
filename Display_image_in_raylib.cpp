// Display the picture in the raylib
#include <raylib.h>

int main()
{
    InitWindow(800, 600, "Background image");

    Texture2D backGround = LoadTexture("Images/background.png"); // To load an image
    Vector2 imagePos = {0, 0};

    while (!WindowShouldClose())
    {
        BeginDrawing();

        DrawText("Hold Left or Right arrow key to see background image", 0, 0, 24, WHITE);

        ClearBackground(BLACK);
        if(IsKeyDown(KEY_LEFT))
            DrawTexture(backGround, 0, 0, WHITE);

        if(IsKeyDown(KEY_RIGHT))
            DrawTextureV(backGround, imagePos, BLUE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
/*
To load the texture there are used:

    LoadTexture("path/image_name.extention");

To display in background:

    1). DrawTexture(Texture_name, x_pos, y_Pos, color);

        This is simple function.

    2). DrawTexture(Texture_name, Texture_pos, color);

        This function takes the Vector2 as position of image in graphics window.


    So, this was function to display image in graphics window

*/
