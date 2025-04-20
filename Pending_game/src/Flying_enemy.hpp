#pragma once

#include <raylib.h>
#include "Player.hpp"

class FlyingDragon
{
public:
	// Constructor and Destructor
	FlyingDragon();
	~FlyingDragon();
	
	// Update and draw functions
	void draw();
	void update(Player &player);
	void handleAnimation();				  

	const Rectangle enemyRect();

private:
	// Position of the enemy
	Vector2 enemyPos;

	// Animation frames (flying and attack)
	Texture2D flyFrames[4];	   // Flying animation frames
	Texture2D attackFrames[8]; // Attack animation frames (currently not used)

	// Animation state
	int frame;			 // Current frame in the animation
	float animationTime; // Timer for frame animation

	// Movement and state variables
	bool isMoving;	   // Whether the enemy is moving
	float speed;	   // Movement speed
	float spawnDelay;  // Time before enemy starts moving
	float elapsedTime; // Time since the enemy became active
	bool isActive;	   // Whether the enemy is currently active

	// Health variables
	int maxHealth;	   // Maximum health of the enemy
	int currentHealth; // Current health of the enemy

	// Healing variables
	float healAmount;	// Amount of health to heal the player
	float healCooldown; // Time between healing events
	float healTimer;	// Timer to manage healing cooldown

	// Private helper methods
	Texture2D getCurrentAnimationFrame(); // Get the current frame for drawing

	// Movement and behavior methods
	void followPlayer(Player &player);	// Make the enemy follow the player
	void handleHealing(Player &player); // Heal the player if necessary

	// Texture handling methods
	Image resizeTexture(const char *path, int width, int height);
	Texture2D loadTextureFromResizedImage(const char *path, int width, int height);

	// Helper method to load animation frames (both flying and attack)
	void loadAnimationFrames(const char *pathPattern, Texture2D *frameArray, int frameCount, int width, int height);

	// Helper method to unload textures from memory
	void unloadTextures(Texture2D *frameArray, int frameCount);
};
