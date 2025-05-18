#include <raylib.h>
#include "Handle_character_movement.hpp"

/*
+----------------------------------------------------------------------------------+
|                                 HOW TO USE                                       |
+----------------------------------------------------------------------------------+

1. Create an object of the Character class.

2. Provide the image path as the first argument to the constructor.
   Use '{}' as a placeholder for the frame number. For example, if your images are named
   "Test_(1).png", "Test_(2).png", "Test_(3).png", etc., pass the path as "Test_({}).png".

3. Provide the second argument, which is the total number of frames in the
   sprite animation.

4. Provide the delay time (in seconds) between each frame as the third argument.
   This controls how fast the animation will play. For example, 0.1f means each frame will
   stay for 0.1 seconds before switching to the next frame.

+----------------------------------------------------------------------------------+
|                                   GOOD LUCK                                      |
+----------------------------------------------------------------------------------+
*/

int main()
{
   InitWindow(800, 600, "Sprite Animation Header-Based");
   SetTargetFPS(60);

   Character warrior("Assets/Walking/walk_({}).png", 8, 0.1f);

   while (!WindowShouldClose())
   {
      warrior.HandleMovement();

      BeginDrawing();
      ClearBackground(RAYWHITE);

      warrior.Draw();

      EndDrawing();
   }

   CloseWindow();
   return 0;
}
