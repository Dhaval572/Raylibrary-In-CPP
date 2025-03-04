// Allocation and Deallocation of memory blocks in memory   
#include <raylib.h>
#include <vector>
using namespace std;

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 450;
constexpr int MAX_BLOCKS = 10;
constexpr int BLOCK_SIZE = 50;
constexpr int BLOCK_SPACING = 60;
constexpr int START_X = 100;
constexpr int START_Y = 200;

// Creates memory block
class MemoryBlock
{
public:
    Rectangle rect;
    Color color;
    bool allocated;
    float alpha; 

    // Initialize memory block
    MemoryBlock(float x, float y)
        : rect{x, y, BLOCK_SIZE, BLOCK_SIZE}, allocated(false), alpha(0.0f)
    {
        color = {static_cast<unsigned char>(GetRandomValue(50, 200)),
                 static_cast<unsigned char>(GetRandomValue(50, 200)),
                 static_cast<unsigned char>(GetRandomValue(50, 200)), 255};
    }

    void Allocate()
    {
        allocated = true;
        alpha = 1.0f;
    }

    void Deallocate()
    {
        allocated = false;
    }

    // Add fading effect
    void Update()
    {
        if (!allocated && alpha > 0)
        {
            alpha -= 0.05f; 
        }
    }

    // Draw block with transparency effect
    void Draw() const
    {
        if (alpha > 0)
        {
            DrawRectangleRec(rect, Fade(color, alpha));
        }
    }
};

// Manages all memory blocks
class MemoryManager
{
private:
    vector<MemoryBlock> memoryBlocks; 

public:
    
    MemoryManager()
    {
        // Adds block in memory
        for (int i = 0; i < MAX_BLOCKS; ++i)
        {
            // (Note: emplace_back is More efficient than push_back())
            memoryBlocks.emplace_back(START_X + i * BLOCK_SPACING, START_Y);
        }
    }

    // Allocate the first available block
    void Allocate()
    {
        for (auto &block : memoryBlocks)
        {
            if (!block.allocated)
            {
                block.Allocate();
                return; // Stop after allocating one block
            }
        }
    }

    // Deallocate the last allocated block
    void Deallocate()
    {
        for (auto it = memoryBlocks.rbegin(); it != memoryBlocks.rend(); ++it)
        {
            if (it->allocated)
            {
                it->Deallocate();
                return; // Stop after deallocating one block
            }
        }
    }

    // Add fading effects 
    void Update()
    {
        for (auto &block : memoryBlocks)
        {
            block.Update();
        }
    }

    void Draw() const
    {
        for (const auto &block : memoryBlocks)
        {
            block.Draw();
        }
    }
};

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Memory Allocation Animation");
    
    MemoryManager memoryManager; 
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_A))
            memoryManager.Allocate();

        if (IsKeyPressed(KEY_D))
            memoryManager.Deallocate();

        memoryManager.Update(); 

        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Press A to allocate, D to deallocate", 20, 20, 20, GREEN);
        memoryManager.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
