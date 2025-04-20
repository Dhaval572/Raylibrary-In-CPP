#pragma once
#include <raylib.h>

class Player
{
public:
    Player();
    ~Player();

    void update();
    void draw();

    void handleMovement();
    void updateAnimation();
    const Rectangle playerRect();

    void takeDamage(float damage); // Handles receiving damage
    void heal(float amount);       // Heal function
    void healOverTime(float amount, float cooldown); // Heal over time function

    float getHealth();
    float currentHealth() const;
    float maxHealth() const;

private:
    // Helpers
    Image resizeImage(const char *path, int width, int height);
    Texture2D loadTextureFromResizedImage(const char *path, int width, int height);
    void drawHealthBar();
    void updateHealthBar();

    // Player state
    Vector2 position;
    float speed;
    float currentHealthValue;
    float maxHealthValue;
    Rectangle healthBar;
    Color healthColor;

    // Movement & animation
    bool isMoving;
    bool isMovingRight;
    int frame;
    float animationTime;

    // Textures
    Texture2D walkRight1, walkRight2;
    Texture2D walkLeft1, walkLeft2;
    Texture2D background;

    // Healing mechanism
    float healCooldown;   // Time between healing actions
    float healTimer;      // Tracks elapsed time for healing cooldown
};
