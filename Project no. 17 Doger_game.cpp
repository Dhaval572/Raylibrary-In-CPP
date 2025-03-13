// Making Doger game
#include <raylib.h>
#include <iostream>

const unsigned short screenWidth = 800;
const unsigned short screenHeight = 600;
const unsigned short numObstacles = 5;
int unsigned short score = 0;

// Returns a random float in the range
float GetRandomFloat(float min, float max)
{
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

class Player
{
public:
    int x, y;
    int size;
    int speed;

    Player(int startX, int startY, int playerSize, int playerSpeed)
    {
        x = startX;
        y = startY;
        size = playerSize;
        speed = playerSpeed;
    }

    void Move()
    {
        if (IsKeyDown(KEY_LEFT) && x > size / 2)
            x -= speed;
        if (IsKeyDown(KEY_RIGHT) && x < screenWidth - size / 2)
            x += speed;
    }

    // Triangle shape
    void Draw()
    {
        Vector2 v1 = {(float)x, (float)y};
        Vector2 v2 = {(float)(x - size / 2), (float)(y + size)};
        Vector2 v3 = {(float)(x + size / 2), (float)(y + size)};
        DrawTriangle(v1, v2, v3, BLUE);
    }

    Rectangle GetBounds()
    {
        return {(float)(x - size / 2), (float)y, (float)size, (float)size};
    }
};

class Obstacle
{
public:
    int x, y;
    int width = 50, height = 20;
    float lastSpeed, newSpeed, currentSpeed;

    Obstacle()
    {
        lastSpeed = GetRandomFloat(3.0f, 4.0f);
        newSpeed = lastSpeed + 1.0f;
        currentSpeed = GetRandomFloat(lastSpeed, newSpeed);
        ResetPosition();
    }

    void Move()
    {
        // (convert to int for pixel movement)
        y += static_cast<int>(currentSpeed);
        if (y > screenHeight)
        {
            score++;
            ResetPosition();
        }
    }

    void Draw()
    {
        DrawRectangle(x, y, width, height, RED);
    }

    Rectangle GetBounds()
    {
        return {(float)x, (float)y, (float)width, (float)height};
    }

    void ResetPosition()
    {
        x = GetRandomValue(0, screenWidth - width);
        y = GetRandomValue(-screenHeight, -height);
    }

    void IncreaseSpeed()
    {
        lastSpeed += 0.10f;          // Base speed
        newSpeed = lastSpeed + 1.0f; // Maintain the original range
        currentSpeed = GetRandomFloat(lastSpeed, newSpeed);
    }

    void ResetSpeed()
    {
        lastSpeed = GetRandomFloat(3.0f, 4.0f);
        newSpeed = lastSpeed + 1.0f;
        currentSpeed = GetRandomFloat(lastSpeed, newSpeed);
        ResetPosition();
    }
};

class Game
{
private:
    Player player;
    Obstacle *obstacles;
    bool gameOver;

public:
    Game() : player(screenWidth / 2, screenHeight - 60, 30, 7)
    {
        obstacles = new Obstacle[numObstacles]; // Allocate numObstacles obstacles
        gameOver = false;
    }

    ~Game()
    {
        delete[] obstacles;
    }

    void Run()
    {
        InitWindow(screenWidth, screenHeight, "Dodger");
        SetTargetFPS(60);
        srand(static_cast<unsigned int>(time(0)));

        while (!WindowShouldClose())
        {
            Update();
            Draw();
        }

        CloseWindow();
    }

private:
    void Update()
    {
        if (!gameOver)
        {
            player.Move();

            for (int i = 0; i < numObstacles; i++)
            {
                obstacles[i].Move();
                if (CheckCollisionRecs(player.GetBounds(), obstacles[i].GetBounds()))
                {
                    gameOver = true;
                }
            }

            // Increase speed of all obstacles every 10 points
            if (score % 20 == 0 && score > 0)
            {
                for (int i = 0; i < numObstacles; i++)
                {
                    obstacles[i].IncreaseSpeed();
                }
            }
        }

        if (gameOver && IsKeyPressed(KEY_R))
        {
            gameOver = false;
            player.x = screenWidth / 2;

            for (int i = 0; i < numObstacles; i++)
            {
                obstacles[i].ResetPosition();
                obstacles[i].ResetSpeed();
            }

            score = 0;
        }
    }

    void Draw()
    {
        BeginDrawing();
        ClearBackground(BLACK);

        if (!gameOver)
        {
            player.Draw();
            for (int i = 0; i < numObstacles; i++)
            {
                obstacles[i].Draw();
            }
        }
        else
        {
            DrawText("Game Over!", screenWidth / 2 - 100, screenHeight / 2 - 20, 40, RED);
            DrawText("Press R to Restart", screenWidth / 2 - 100, screenHeight / 2 + 20, 20, YELLOW);
        }

        DrawText(TextFormat("Score: %i", score), 10, 10, 20, GREEN);

        // Debug display (if needed)
        // DrawText(TextFormat("Last Speed: %.2f", obstacles[0].lastSpeed), 10, 30, 20, YELLOW);
        // DrawText(TextFormat("New Speed: %.2f", obstacles[0].newSpeed), 10, 50, 20, ORANGE);

        EndDrawing();
    }
};

int main()
{
    Game game;
    game.Run();
    return 0;
}
