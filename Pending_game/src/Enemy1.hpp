class Enemy1
{
private:
	Vector2 enemyPos;
	bool isMoving;
	float speed;
	float maxHealth;
	float currentHealth;
	Rectangle healthBar;
	int frame;
	float animationTime;
	Texture2D walk1, walk2, walk3, walk4, walk5, walk6, walk7, walk8;
	Texture2D attack1, attack2, attack3, attack4, attack5, attack6, attack7, attack8;
	float spawnDelay;
	float elapsedTime;
	bool isActive;

public:
	Enemy1();
	~Enemy1();
	void draw();
	void update(Player &player);
	Image resizeTextureForWalk(const char *path, int width, int height);
	Texture2D loadTextureFromResizedImage(const char *path, int width, int height);
	void drawHealthBar();
	void handleMovement(Player &player);
	void handleAnimation();
	const Rectangle enemyRect();
};