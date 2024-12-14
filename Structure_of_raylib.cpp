// Main structure of raylib
#include <raylib.h>

int main()
{
    InitWindow(600, 500, " ");

    while (!WindowShouldClose())
    {
        BeginDrawing();

        // Some statements
		//-----***-----//
		//-----***-----//
		//-----***-----//

        EndDrawing();

    }

    CloseWindow();
    return 0;
}
/*
Explaination of raylib:

    Raylib is a special library which is for c and c++ language for do some graphical task.

    All structure about raylib:

    Including section:

        First you should include library for use raylib.

        #include <raylib.h> 

    Main function:

        The main function in Raylib is the entry point of your program where the execution begins.

        It typically involves initializing the window, setting up the game loop, handling inputs, updating the game state, drawing graphics, and finally closing the window.

        Syntax:

            return_type main()
            {
                // Statements
            }

    InitWindow():

        initializes a window where the graphics are displayed.

        It takes three argument first is width of window, second in height of window and third is name to give to window

        Syntax:

            InitWindow(screen_width, screen_height, "Name_of_window");
            ( Line no. 6 )

    Main game loop:

        The game loop in Raylib is the continuous cycle where the game runs, updates, and renders each frame.

        Syntax:

            while (!WindowShouldClose())
            {
                BeginDrawing(); 

                // Statements to do in the main game loop

                EndDrawing();

            }
            ( Line no. 8 )

        In this i used two functions in game loop:

        1). BeginDrawing(): ( Line no 10 )

            Starts the process of drawing everything for the current frame.

        2). EndDrawing():   ( Line no 17 )
        
            Ends the drawing process and displays everything drawn during the frame.

    close the window:

        After all tasks, you must have to close the graphics window to deallocate memory which was allocated when the window was initialized with InitWindow().

        For this task there are one function is used which is CloseWindow(). 
        ( Line no. 21 )

    So, this was main structure of raylib.h 

    I hope you understand everything about structure of ray library.
*/
