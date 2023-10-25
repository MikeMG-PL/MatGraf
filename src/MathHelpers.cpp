#include "MathHelpers.h"
#include <iostream>

bool floatNearlyEqual(float f1, float f2, float tolerance)
{
	return (std::abs(f1 - f2) < tolerance);
}
