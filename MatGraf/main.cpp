#include <iostream>
#include "Quaternion.h"
#define PI 3.14159265f

int main()
{
	Quaternion quaternion1 = Quaternion(2.0f, 3.0f, 4.0f, 1.0f);
	Quaternion quaternion2 = Quaternion(6.0f, 7.0f, 8.0f, 5.0f);

	std::cout << "Quaternion q1: " << quaternion1.toString() << "\n";
	std::cout << "Quaternion q2: " << quaternion2.toString() << "\n";

	std::cout << std::endl;

	// Quaternion addition
    {
	    std::cout << "q1 + q2:" << "\n";
		std::cout << (quaternion1 + quaternion2).toString() << "\n";
	}

	std::cout << std::endl;

	// Quaternion subtraction
	{
	    std::cout << "q1 - q2" << "\n";
		std::cout << (quaternion1 - quaternion2).toString() << "\n";
	}

	std::cout << std::endl;

	// Proof that quaternion multiplication is not commutative
	{
		std::cout << "q1 * q2" << "\n";
        const Quaternion r1 = quaternion1 * quaternion2;
	    std::cout << "Result: " << r1.toString() << "\n";

		std::cout << "q2 * q1" << "\n";
		const Quaternion r2 = quaternion2 * quaternion1;
	    std::cout << "Result: " << r2.toString() << "\n";

		std::cout << "Checking if multiplying is not commutative..." << "\n";

		if (r1 == r2)
			std::cout << "ERROR, multiplying is commutative." << "\n";
		else
			std::cout << "SUCCESS, multiplying is not commutative." << "\n";
	}

	std::cout << std::endl;

	// Quaternion division
	{
	    std::cout << "q1 / q2" << "\n";
		std::cout << "Result: " << (quaternion1 / quaternion2).toString() << "\n";
	}

	std::cout << std::endl;

	// Rotate
	{
		const Vector point = { -1.0f, -1.0f, -1.0f };
        const Vector axis = { 1.0f, 0.0f, 0.0f };
        const float angle = 270.0f;
	    std::cout << "Rotate " << point.toString() << " by " << angle << " degrees." << "\n";
		std::cout << "Result: " << Quaternion::rotate(point, axis, angle * PI / 180.0f).toString() << "\n";
	}
}
