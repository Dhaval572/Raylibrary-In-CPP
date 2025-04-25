#include <raylib.h>
#include "SpriteAnimation.hpp"

/*
+----------------------------------------------------------------------------------+
|                                 HOW TO USE                                       |
+----------------------------------------------------------------------------------+

1. Create an object of the SpriteAnimation class.

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

   SpriteAnimation walk("Assets/Walking/Jump_({}).png", 8, 0.1f);
   SpriteAnimation attack("Assets/Attack/Attack_017_({}).png", 6, 0.1f);
   SpriteAnimation jump("Assets/Walking/Jump_({}).png", 8, 0.1f);
   SpriteAnimation hit("Assets/Hit/Hit_({}).png", 6, 0.1f);
   SpriteAnimation idle("Assets/Idle/Idle_({}).png", 6, 0.2f);

   while (!WindowShouldClose())
   {
      walk.Update();
      attack.Update();
      jump.Update();
      hit.Update();
      idle.Update();

      BeginDrawing();
      ClearBackground(RAYWHITE);

      walk.Draw({100, 300});
      attack.Draw({250, 300});
      jump.Draw({400, 300});
      hit.Draw({550, 300});
      idle.Draw({700, 300});

      EndDrawing();
   }

   CloseWindow();
   return 0;
}
