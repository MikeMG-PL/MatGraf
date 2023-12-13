#include "Plane.h"

Plane::Plane(const Vector& p, const Vector& normal)
{
	this->p = p;
	this->normal = normal;
}

Plane::Plane(float a, float b, float c, float d)
{
	this->normal = { a, b, c };
	this->p = { 0, 0, -d / c };
}
