#include <iostream>
#include <Vector.h>
#include "MathHelpers.h"
#define PI 3.14159265f

int main()
{
    Vector v1(1.23f, 4.56f, 7.89f), v2(22, 24, 13);
    if (v1 + v2 == v2 + v1)
        std::cout << "[SUCCESS] Addition of vectors is commutative." << std::endl;
    else std::cout << "[ASSERTION FAILED]" << std::endl;

    Vector a(0, 3, 0), b(5, 5, 0);
    if(floatNearlyEqual(a.angle(b) * 180 / PI, 45))
		std::cout << "[SUCCESS] Angle between " << a.toString() << " and " << b.toString() << " equals expected value (45 degrees)." << std::endl;
    else std::cout << "[ASSERTION FAILED]" << std::endl;

    Vector c(4, 5, 1), d(4, 1, 3);
    Vector perpendicular = c.cross(d);
    bool b1 = perpendicular == Vector(14, -8, -16);
    bool b2 = floatNearlyEqual(c.angle(perpendicular) * 180 / PI, 90);
    bool b3 = floatNearlyEqual(d.angle(perpendicular) * 180 / PI, 90);
    if(b1 && b2 && b3)
		std::cout << "[SUCCESS] Cross product equals expected vector, angle between vectors and perpendicular vector equals 90 degrees." << std::endl;
    else std::cout << "[ASSERTION FAILED]" << std::endl;

    if(floatNearlyEqual(perpendicular.normalized().magnitude(), 1))
		std::cout << "[SUCCESS] Normalized vector length equals expected value (1)" << std::endl;
    else std::cout << "[ASSERTION FAILED]" << std::endl;
}
