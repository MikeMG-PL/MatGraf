#pragma once

#include <sstream>
#include <vector>
#include <windows.h>

#include "Cube.h"

constexpr int NUM_PIXELS = 60;

namespace Renderer
{
    std::vector<Plane> planes;
    std::vector<Sphere> spheres;
    std::vector<Cube> cubes;
    Vector cameraPos(0, 0, 1);

    #define M_PI 3.14159265f

float pixelSize = 0.25f;
char pixels[NUM_PIXELS][NUM_PIXELS] = {};

static void clearBuffer()
{
	for (int i = 0; i < NUM_PIXELS; i++)
	{
		for (int j = 0; j < NUM_PIXELS; j++)
		{
			pixels[i][j] = '.';
		}
	}
}

static void checkForIntersections()
{
    float aspectRatio = static_cast<float>(NUM_PIXELS) / static_cast<float>(NUM_PIXELS);
    float fov = 90.0f;
    float halfScreenHeight = tan(fov * 0.5f * M_PI / 180.0f);
    float halfScreenWidth = aspectRatio * halfScreenHeight;

    Vector lookAtPoint = Vector(0.0f, 0.0f, 0.0f);
    Vector up = Vector(0.0f, 1.0f, 0.0f);
    Vector direction = (lookAtPoint - cameraPos).normalized();
    Vector right = direction.cross(up).normalized();
    up = right.cross(direction).normalized();

    // Check for plane intersections between camera and a line from camera to pixel angle.
    // Screen is made up of 60x60 pixels, each pixel is 0.25 units wide.
    // For each pixel, check if it intersects with any planes.
    // If it does, set the pixel to "0" otherwise set it to "."
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        for (int j = 0; j < NUM_PIXELS; j++)
        {
            float x = (2.0f * (i + 0.5f) / static_cast<float>(NUM_PIXELS) - 1.0f) * halfScreenWidth;
            float y = (1.0f - 2.0f * (j + 0.5f) / static_cast<float>(NUM_PIXELS)) * halfScreenHeight;

            Vector pixelPos = cameraPos + direction + right * x + up * y;
            Vector pixelDirection = (pixelPos - cameraPos).normalized();
            // Vector direction = (lookAtPoint - cameraPos).normalized();
            // Vector right = direction.cross(up).normalized();
            // up = right.cross(direction).normalized();

            // Vector pixelPos = cameraPos + right * (i * pixelSize - (NUM_PIXELS / 2 * pixelSize)) + up * (j * pixelSize - (NUM_PIXELS / 2 * pixelSize));
            // Vector pixelPos = cameraPos + direction * (i * pixelSize - (NUM_PIXELS / 2 * pixelSize));
            // Vector pixelPos = cameraPos + direction * (i * pixelSize - (NUM_PIXELS / 2 * pixelSize)) + direction * (j * pixelSize - (NUM_PIXELS / 2 * pixelSize));

            // Vector pixelPos = Vector(i * pixelSize - (NUM_PIXELS / 2 * pixelSize), j * pixelSize - (NUM_PIXELS / 2 * pixelSize), 0);
            // Vector direction = (pixelPos - cameraPos).normalized();
            const Line line = Line(cameraPos, pixelDirection);

            bool intersects = false;
            for (const Plane plane : Renderer::planes)
            {
                Vector intersectionPoint = intersection(line, plane);
                std::cout << intersectionPoint.toString() << "\n";
                if (!(intersectionPoint == Vector::invalid()))
                {
                    pixels[i][j] = '0';
                    intersects = true;
                    break;
                }
            }

            if (intersects)
                continue;

            for (const Sphere sphere : Renderer::spheres)
            {
                std::pair<Vector, Vector> intersectionPoints = intersection(sphere, line);

                if (!(intersectionPoints.first == Vector::invalid()))
                {
                    pixels[i][j] = '0';
                    intersects = true;
                    break;
                }

                if (!(intersectionPoints.second == Vector::invalid()))
                {
                    pixels[i][j] = '0';
                    intersects = true;
                    break;
                }
            }

            if (intersects)
                continue;

            for (auto const& cube : Renderer::cubes)
            {
                if (cube.intersects(line))
                {
                    pixels[i][j] = '0';
                    intersects = true;
                    break;
                }
            }

            if (!intersects)
                pixels[i][j] = '.';
        }
    }
}

void cls(HANDLE hConsole);

static void render()
{
    checkForIntersections();

    std::stringstream s;
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        for (int j = 0; j < NUM_PIXELS; j++)
        {
            s << pixels[i][j];
        }
        s << "\n";
    }

    std::string screen = s.str();
    HANDLE stdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    cls(stdOut);
    if (stdOut != NULL && stdOut != INVALID_HANDLE_VALUE)
    {
        DWORD written = 0;
        WriteConsoleA(stdOut, screen.c_str(), screen.length(), &written, NULL);
    }
}

void cls(HANDLE hConsole)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    SMALL_RECT scrollRect;
    COORD scrollTarget;
    CHAR_INFO fill;

    // Get the number of character cells in the current buffer.
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }

    // Scroll the rectangle of the entire buffer.
    scrollRect.Left = 0;
    scrollRect.Top = 0;
    scrollRect.Right = csbi.dwSize.X;
    scrollRect.Bottom = csbi.dwSize.Y;

    // Scroll it upwards off the top of the buffer with a magnitude of the entire height.
    scrollTarget.X = 0;
    scrollTarget.Y = (SHORT)(0 - csbi.dwSize.Y);

    // Fill with empty spaces with the buffer's default text attribute.
    fill.Char.UnicodeChar = TEXT(' ');
    fill.Attributes = csbi.wAttributes;

    // Do the scroll
    ScrollConsoleScreenBuffer(hConsole, &scrollRect, NULL, scrollTarget, &fill);

    // Move the cursor to the top left corner too.
    csbi.dwCursorPosition.X = 0;
    csbi.dwCursorPosition.Y = 0;

    SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}

}