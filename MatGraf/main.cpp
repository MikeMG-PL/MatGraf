#include <iostream>

#include "Line.h"
#include "MathHelpers.h"
#define PI 3.14159265f

int main()
{
	{
		Line l1({ -2, 5, 0 }, { 3, 1, 5 });
		Line l2({ -2, 4, 0 }, { 1, -5, 3 });

		Vector v = intersection(l1, l2);
		std::cout << v.toString() << std::endl;

		if (v.toString() == Vector::invalid().toString())
			std::cout << "No intersections between those lines." << std::endl;

		std::cout << angleBetween(l1, l2) * 180.0f / PI << std::endl;
	}

	{
		Line l1({ -2, 2, -1 }, { 3, -1, 2 });
		Plane p(2, 3, 3, -8);

		Vector v = intersection(l1, p);

		std::cout << v.toString() << std::endl;
	}

}
