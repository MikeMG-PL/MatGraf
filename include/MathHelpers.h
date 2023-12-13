#pragma once
#include <iostream>

#include "Line.h"
#include "Plane.h"
#include "Vector.h"

enum Axis
{
	X,
	Y,
	Z
};

inline bool floatNearlyEqual(float d1, float d2, float tolerance = 0.000001f)
{
	return (std::abs(d1 - d2) < tolerance);
}

inline Vector intersection(Line l1, Line l2)
{
	const Vector p1 = l1.p;
	const Vector p2 = l2.p;
	const Vector v1 = l1.v;
	const Vector v2 = l2.v;

	const float t1 = (((p2 - p1).cross(v2)).dot(v1.cross(v2))) / std::pow((v1.cross(v2)).magnitude(), 2);
	const float t2 = -(((p2 - p1).cross(v1)).dot(v2.cross(v1))) / std::pow((v2.cross(v1)).magnitude(), 2);

	if (p1 + v1 * t1 == p2 + v2 * t2)
		return p1 + v1 * t1;

	return Vector::invalid();
}

inline float angleBetween(Line l1, Line l2)
{
	Vector v1 = l1.v;
	Vector v2 = l2.v;
	return v1.angle(v2);
}

// inline Vector intersection(Line l, Plane p)
// {
//
// }
//
// inline float angleBetween(Line l, Plane p)
// {
// 	
// }
//
// inline Line intersection(Plane p1, Plane p2)
// {
// 	
// }
//
// inline float angleBetween(Plane p1, Plane p2)
// {
// 	
// }

