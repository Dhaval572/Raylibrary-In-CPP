// Rotate the image
#include <raylib.h>

int main()
{
	InitWindow(600, 500, "Image Rotation");
	Image image = LoadImage("Images/pixel_ship.png"); // Replace with your image path
	Texture2D texture = LoadTextureFromImage(image);
	UnloadImage(image); // To deallocate the memory

	// Rotation variables
	float rotationAngle = 0.0f;

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		if (IsKeyDown(KEY_RIGHT))
			rotationAngle += 1.0f;

		if (IsKeyDown(KEY_LEFT))
			rotationAngle -= 1.0f;

		// Wrap the angle within the range of 0 to 360 degrees
		if (rotationAngle >= 360.0f)
			rotationAngle -= 360.0f;

		if (rotationAngle < 0.0f)
			rotationAngle += 360.0f;

		BeginDrawing();
		ClearBackground(BLACK);

		// Define the source and destination rectangles
		Rectangle sourceRec = {0.0f, 0.0f, (float)texture.width, (float)texture.height};
		Rectangle destRec = {300.0f, 250.0f, (float)texture.width, (float)texture.height};
		Vector2 origin = {(float)texture.width / 2.0f, (float)texture.height / 2.0f};

		// Draw the rotated texture
		DrawTexturePro(texture, sourceRec, destRec, origin, rotationAngle, WHITE);

		// Display instructions and rotation angle
		DrawText("Use LEFT and RIGHT arrow keys to rotate the image", 10, 10, 20, GREEN);
		DrawText(TextFormat(" %.2f°", rotationAngle), 250, 400, 50, MAGENTA);

		EndDrawing();
	}

	UnloadTexture(texture);
	CloseWindow();
	return 0;
}
