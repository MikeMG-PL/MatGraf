#include "Vector.h"
#define PI 3.14159265f
#include <sstream>
#include "MathHelpers.h"

std::string Vector::toString()
{
	std::stringstream s;
	s << "[" << x << ", " << y << ", " << z << "]";
	return s.str();
}

Vector Vector::operator+(const Vector& v) const
{
	return { x + v.x, y + v.y, z + v.z };
}

Vector Vector::operator-(const Vector& v) const
{
	return { x - v.x, y - v.y, z - v.z };
}

bool Vector::operator==(const Vector& v)
{
	return floatNearlyEqual(x, v.x) && floatNearlyEqual(y, v.y) && floatNearlyEqual(z, v.z);
}

Vector Vector::operator*(float f) const
{
	return { x * f, y * f, z * f };
}

Vector Vector::operator/(float f) const
{
	return { x / f, y / f, z / f };
}

Vector Vector::operator!()
{
	return negative();
}

Vector Vector::negative() const
{
	return { -x, -y, -z };
}

float Vector::dot(Vector v) const
{
	return x * v.x + y * v.y + z * v.z;
}

Vector Vector::cross(Vector v) const
{
	return { y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x };
}

Vector Vector::normalized()
{
	Vector vector = { x, y, z };
	return vector / magnitude();
}

float Vector::magnitude()
{
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

float Vector::angle(Vector v)
{
	return acos(dot(v) / (magnitude() * v.magnitude()));
}