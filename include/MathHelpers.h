#pragma once
#include <iostream>
#define PI 3.14159265f
#include "Line.h"
#include "LineSegment.h"
#include "Plane.h"
#include "Vector.h"
#include "Sphere.h"

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

inline Vector intersection(Line l, Plane p)
{
	Vector n = p.normal;
	Vector p0 = l.p;
	Vector q0 = p.p;
	Vector v = l.v;

	float t = -n.dot(p0 - q0) / n.dot(v);
	Vector P = p0 + v * t;

	if (n.dot(P - q0) == 0)
		return P;

	return Vector::invalid();
}

inline float angleBetween(Line l, Plane p)
{
	const Vector n = p.normal;
	const Vector v = l.v;
	const float angleDeg = v.angle(n) * 180 / PI;
	float result = 0;

	if (angleDeg > 90)
		result = angleDeg - 90;
	else
		result = 90 - angleDeg;

	return result;
}

inline std::pair<Vector, Vector> intersection(Sphere s, Line l)
{
	float a = l.v.dot(l.v);
	float b = 2.0f * l.v.dot((l.p - s.point));
	float c = (l.p - s.point).dot(l.p - s.point) - (s.radius * s.radius);

	float delta = b * b - 4.0f * a * c;

	if (delta < 0)
	    return std::make_pair(Vector::invalid(), Vector::invalid());

	float t1 = (-b + sqrt(delta)) / (2.0f * a);
	float t2 = (-b - sqrt(delta)) / (2.0f * a);

	Vector p1 = l.p + l.v * t1;
	Vector p2 = l.p + l.v * t2;

    return std::make_pair<Vector, Vector>(Vector(p1), Vector(p2));
}

inline Vector intersection(LineSegment l1, LineSegment l2)
{
    const Vector p1 = l1.p;
	const Vector p2 = l2.p;
	const Vector v1 = l1.v;
	const Vector v2 = l2.v;

	const float t1 = (((p2 - p1).cross(v2)).dot(v1.cross(v2))) / std::pow((v1.cross(v2)).magnitude(), 2);
	const float t2 = -(((p2 - p1).cross(v1)).dot(v2.cross(v1))) / std::pow((v2.cross(v1)).magnitude(), 2);

	if (t1 < 0 || t1 > 1 || t2 < 0 || t2 > 1)
	    return Vector::invalid();

	if (p1 + v1 * t1 == p2 + v2 * t2)
	    return p1 + v1 * t1;

	return Vector::invalid();
}

// inline Line intersection(Plane p1, Plane p2)
// {
// 	
// }
//
// inline float angleBetween(Plane p1, Plane p2)
// {
// 	
// }

