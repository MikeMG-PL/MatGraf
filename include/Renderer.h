#pragma once
#define NUM_PIXELS 60

float pixelSize = 0.25f;
char pixels[NUM_PIXELS][NUM_PIXELS] = {};
Vector pixelPositions[NUM_PIXELS][NUM_PIXELS] = {};
Vector cameraPos(0, 0, 5);

inline void clearBuffer()
{
	for (int i = 0; i < NUM_PIXELS; i++)
	{
		for (int j = 0; j < NUM_PIXELS; j++)
		{
			pixels[i][j] = '.';
		}
	}
}

inline void setupPixelPositions()
{
	// Finished in this function: trying to save pixel positions of "plane" in front of virtual camera
	// Coordinates like in OpenGL, I wanna
	Vector firstPixelPos(-(NUM_PIXELS / 2 * pixelSize - pixelSize / 2), NUM_PIXELS / 2 * pixelSize - pixelSize / 2, cameraPos.z - 2.5f);
	for (int i = 0; i < NUM_PIXELS; i++)
	{
		for (int j = 0; j < NUM_PIXELS; j++)
		{
			// ...
			pixelPositions[i][j] = Vector();
		}
	}
}

inline void render()
{
	for (int i = 0; i < NUM_PIXELS; i++)
	{
		for (int j = 0; j < NUM_PIXELS; j++)
		{
			std::cout << pixels[i][j];
		}
		std::cout << std::endl;
	}
}