#include <cassert>
#include <iostream>
#include <Vector.h>
#include "MathHelpers.h"
#define PI 3.14159265f

int main()
{
    Vector v1(1.23f, 4.56f, 7.89f), v2(22, 24, 13);
    assert(v1 + v2 == v2 + v1);
    std::cout << "[SUCCESS] Addition of vectors is commutative." << std::endl;

    Vector a(0, 3, 0), b(5, 5, 0);
    assert(floatNearlyEqual(a.angle(b) * 180 / PI, 45));
    std::cout << "[SUCCESS] Angle between " << a.toString() << " and " << b.toString() << " equals expected value (90 degrees)." << std::endl;

    Vector c(4, 5, 1), d(4, 1, 3);
    Vector perpendicular = c.cross(d);
    assert(perpendicular == Vector(14, -8, -16));
    assert(floatNearlyEqual(c.angle(perpendicular) * 180 / PI, 90));
    assert(floatNearlyEqual(d.angle(perpendicular) * 180 / PI, 90));
    std::cout << "[SUCCESS] Cross product equals expected vector, angle between vectors and perpendicular vector equals 90 degrees." << std::endl;

    assert(floatNearlyEqual(perpendicular.normalized().magnitude(), 1));
    std::cout << "[SUCCESS] Normalized vector length equals expected value (1)" << std::endl;
}
