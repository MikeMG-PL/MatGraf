#include <iostream>

#include "Line.h"
#include "MathHelpers.h"
#include "Sphere.h"

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

		std::cout << angleBetween(l1, p) << std::endl;
	}

	{
	    Sphere s({0.0f, 0.0f, 0.0f}, sqrt(26.0f));
		Line l({3, -1, 2}, {2, 4, -6});

		auto result = intersection(s, l);

	    if (result.first.toString() == Vector::invalid().toString())
			std::cout << "No intersections between the sphere and the line." << std::endl;
		else
		    std::cout << "Intersections at: " << result.first.toString() << ", " << result.second.toString() << std::endl;
	}

	{
	    LineSegment l1({5,5,4}, {5,5,2});
		LineSegment l2({5,5,5}, {5,5,-2});

		auto result = intersection(l1, l2);

	    if (result.toString() == Vector::invalid().toString())
			std::cout << "No intersections between the two line segments." << std::endl;
		else
		    std::cout << result.toString() << std::endl;
	}
}
