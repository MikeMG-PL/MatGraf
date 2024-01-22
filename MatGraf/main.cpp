#include <iostream>

#include "Line.h"
#include "MathHelpers.h"
#include "Quaternion.h"
#include "Sphere.h"
#include "Renderer.h"

int main()
{
    // Initially fill with dots
    Renderer::clearBuffer();

    //Plane p(Vector(0, 0, 1), Vector(1, 4, 1));

    //Renderer::planes.emplace_back(p);
    //Sphere sphere1(Vector(0.0f, 0.0f, 0.0f), 0.5f);
    //Renderer::spheres.emplace_back(sphere1);

    Cube cube(Vector(0.0f, 0.0f, 0.0f), 0.5f, 0.5f, 0.5f);
    Renderer::cubes.emplace_back(cube);
	Renderer::cameraPos.z += 0.25f;
    float flow = -10000.0f;
    float rotation = 1.0f;
    bool once = true;
    while (true)
    {
        // Check if high-order bit is set (1 << 15)
        if (GetKeyState('A') & 0x8000)
        {
            Renderer::cameraPos.y += 0.01f;
        }

        flow += 0.01f;
        //rotation += 0.0001f;
        for (auto& sphere : Renderer::spheres)
        {
            sphere.radius = sin(flow);
        }

        //if (once)
        {
            for (auto& cube : Renderer::cubes)
            {
                //cube.rotate(rotation, Vector(0.0f, 1.0f, 0.0f));
                //cube.rotate(rotation, Vector(1.0f, 0.0f, 0.0f));
                //cube.rotate(rotation, Vector(0.0f, 0.0f, 1.0f));
                //cube.center = Vector(sin(flow), sin(flow), 0.0f);
                once = false;
            }
        }

        Renderer::cameraPos = Quaternion::rotate(Renderer::cameraPos, Vector(0, 1, 0), 0.1f);
        
        Renderer::render();
    }
}
