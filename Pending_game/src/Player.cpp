#include <raylib.h>
#include "Player.hpp"

// Constructor
Player::Player()
	: position{GetScreenWidth() / 2.0f, 325.0f},
	  speed(1.0f),
	  currentHealthValue(100.0f),
	  maxHealthValue(100.0f),
	  healthBar{},
	  healthColor(WHITE),
	  isMoving(false),
	  isMovingRight(true),
	  frame(0),
	  animationTime(0.0f),
	  healCooldown(1.0f), // Heal every 1 second
	  healTimer(0.0f)	  // Start with no healing time
{
	// Initialize health bar position and size
	healthBar = {position.x / 2, position.y - 3, 150, 10};

	// Load textures
	walkRight1 = loadTextureFromResizedImage("Sprites/Player walking/monster_right_1.png", 150, 150);
	walkRight2 = loadTextureFromResizedImage("Sprites/Player walking/monster_right_2.png", 150, 150);
	walkLeft1 = loadTextureFromResizedImage("Sprites/Player walking/monster_Left_1.png", 150, 150);
	walkLeft2 = loadTextureFromResizedImage("Sprites/Player walking/monster_Left_2.png", 150, 150);
	background = loadTextureFromResizedImage("Images/background.png", 1200, 600);
}

// Destructor
Player::~Player()
{
	UnloadTexture(walkRight1);
	UnloadTexture(walkRight2);
	UnloadTexture(walkLeft1);
	UnloadTexture(walkLeft2);
	UnloadTexture(background);
}

// Movement handling
void Player::handleMovement()
{
	if (IsKeyDown(KEY_RIGHT))
	{
		position.x += speed;
		isMovingRight = true;
	}
	else if (IsKeyDown(KEY_LEFT))
	{
		position.x -= speed;
		isMovingRight = false;
	}

	if (position.x > GetScreenWidth() - walkRight1.width)
		position.x = GetScreenWidth() - walkRight1.width;

	if (position.x < 0)
		position.x = 0;
}

// Animation update
void Player::updateAnimation()
{
	if (isMoving)
	{
		animationTime += GetFrameTime();
		if (animationTime >= 0.7f)
		{
			frame = !frame;
			animationTime = 0.0f;
		}
	}
	else
	{
		frame = 0;
	}
}

// Player rectangle
const Rectangle Player::playerRect()
{
	return {position.x, position.y, (float)walkRight1.width, (float)walkRight1.height};
}

// Damage handling
void Player::takeDamage(float damage)
{
	currentHealthValue -= damage;
	if (currentHealthValue < 0)
		currentHealthValue = 0;
}

// Healing
void Player::heal(float amount)
{
	currentHealthValue += amount;
	if (currentHealthValue > maxHealthValue)
		currentHealthValue = maxHealthValue;
}

// Healing over time
void Player::healOverTime(float amount, float cooldown)
{
	healTimer += GetFrameTime();
	if (healTimer >= healCooldown)
	{
		heal(amount);
		healTimer = 0.0f;
	}
}

// Health accessors
float Player::getHealth()
{
	return currentHealthValue;
}

float Player::currentHealth() const
{
	return currentHealthValue;
}

float Player::maxHealth() const
{
	return maxHealthValue;
}

// Update logic
void Player::update()
{
	isMoving = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT);
	handleMovement();
	updateAnimation();

	// Heal over time (for demonstration)
	healOverTime(0.5f, healCooldown); // Heal 0.5 health every second
}

// Resize and load texture
Texture2D Player::loadTextureFromResizedImage(const char *path, int width, int height)
{
	Image resizedImage = resizeImage(path, width, height);
	Texture2D texture = LoadTextureFromImage(resizedImage);
	UnloadImage(resizedImage);
	return texture;
}

// Resize helper
Image Player::resizeImage(const char *path, int width, int height)
{
	Image img = LoadImage(path);
	ImageResize(&img, width, height);
	return img;
}

// Draw health bar
void Player::drawHealthBar()
{
	updateHealthBar();
	DrawRectangleRec(healthBar, healthColor);
}

// Update health bar visuals
void Player::updateHealthBar()
{
	float healthPercentage = currentHealthValue / maxHealthValue;
	healthBar.width = 100 * healthPercentage;

	if (currentHealthValue <= maxHealthValue * 0.25f)
		healthColor = RED;
	else if (currentHealthValue <= maxHealthValue * 0.5f)
		healthColor = YELLOW;
	else
		healthColor = GREEN;

	healthBar.x = position.x + (walkRight1.width / 2) - (healthBar.width / 2);
	healthBar.y = position.y - 20;
}

// Drawing player and background
void Player::draw()
{
	DrawTexture(background, 0, 0, WHITE);

	Texture2D currentTexture;
	if (isMoving)
	{
		currentTexture = isMovingRight ? (frame == 0 ? walkRight1 : walkRight2)
									   : (frame == 0 ? walkLeft1 : walkLeft2);
	}
	else
	{
		currentTexture = isMovingRight ? walkRight1 : walkLeft1;
	}

	DrawTexture(currentTexture, (int)position.x, (int)position.y, WHITE);
	drawHealthBar();
}
