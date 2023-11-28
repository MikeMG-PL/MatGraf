#include "Quaternion.h"
#include <complex.h>
#include <sstream>

Quaternion::Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{
}

float& Quaternion::operator[](int index)
{
    switch (index)
    {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        default:
            throw std::invalid_argument("Invalid Quaternion index!");
    }
}

Quaternion Quaternion::operator*(const Quaternion& q) const
{
    return Quaternion(
        // This is wrong
        this->w * q.x + this->x * q.w + this->y * q.z - this->z * q.y,
        this->w * q.y + this->y * q.w + this->z * q.x - this->x * q.z,
        this->w * q.z + this->z * q.w + this->x * q.y - this->y * q.x,
        this->w * q.w - this->x * q.x - this->y * q.y - this->z * q.z
    );
}

std::string Quaternion::toString() const
{
    std::stringstream s{};
    s << "(";
    s << x;
    s << ", ";
    s << y;
    s << ", ";
    s << z;
    s << ", ";
    s << w;
    s << ")";
    return s.str();
}