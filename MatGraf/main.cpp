#include <iostream>

#include "Line.h"
#include "MathHelpers.h"
#include "Sphere.h"
#include "Renderer.h"

int main()
{
	// Initially fill with dots
	clearBuffer();

	Plane p(Vector(0, 0, 1), Vector(0, 0, 1));



	render();
}
