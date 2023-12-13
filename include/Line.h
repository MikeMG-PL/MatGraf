#pragma once
#include "Vector.h"

struct Line
{
	// static Line makeLineFromPoints(Vector v1, Vector v2);

	// p, v or x0y0z0, ABC
	Line(const Vector& p, const Vector& v)
		: p(p),
		  v(v)
	{
	}

	Vector p;
	Vector v;
};
