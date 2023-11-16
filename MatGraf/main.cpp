#include <iostream>
#include "Matrix.h"
#define PI 3.14159265f

int main()
{
	{
		// Equals
		Matrix m1(2, 2), m2(2, 2);

		m1.Set(1, 0);
		m1.Set(1, 1);
		m1.Set(1, 2);
		m1.Set(1, 3);

		m2.Set(1, 0);
		m2.Set(1, 1);
		m2.Set(1, 2);
		m2.Set(1, 3);

		if (m1 == m2 && m2 == m1)
			std::cout << "EQUALS: SUCCESS" << std::endl;
	}

	{
		// Adding
		Matrix m1(2, 2), m2(2, 2), expected(2, 2);

		m1.Set(1, 0);
		m1.Set(1, 1);
		m1.Set(1, 2);
		m1.Set(1, 3);

		m2.Set(1, 0);
		m2.Set(1, 1);
		m2.Set(1, 2);
		m2.Set(2, 3);

		expected.Set(2, 0);
		expected.Set(2, 1);
		expected.Set(2, 2);
		expected.Set(3, 3);

		auto result = m1 + m2;

		if (result == expected)
			std::cout << "ADDING: SUCCESS" << std::endl;
	}

	{
		// Substracting
		Matrix m1(2, 2), m2(2, 2), expected(2, 2);

		m1.Set(5, 0);
		m1.Set(4, 1);
		m1.Set(3, 2);
		m1.Set(2, 3);

		m2.Set(1, 0);
		m2.Set(1, 1);
		m2.Set(1, 2);
		m2.Set(2, 3);

		expected.Set(4, 0);
		expected.Set(3, 1);
		expected.Set(2, 2);
		expected.Set(0, 3);

		auto result = m1 - m2;

		if (result == expected)
			std::cout << "SUBSTRACTING: SUCCESS" << std::endl;
	}

	{
		// Substracting
		Matrix m1(2, 2);
		float f = 3.0f;
		Matrix expected(2, 2);

		m1.Set(5, 0);
		m1.Set(4, 1);
		m1.Set(3, 2);
		m1.Set(2, 3);

		expected.Set(15, 0);
		expected.Set(12, 1);
		expected.Set(9, 2);
		expected.Set(6, 3);

		auto result = m1 * f;

		if (result == expected)
			std::cout << "MULTIPLYING BY SCALAR: SUCCESS" << std::endl;
	}

	{
		// Substracting
		Matrix m1(3, 3), m2(3, 1), expected(3, 1);

		m1.Set(1, 0);
		m1.Set(2, 1);
		m1.Set(2, 2);
		m1.Set(1, 3);
		m1.Set(5, 4);
		m1.Set(6, 5);
		m1.Set(8, 6);
		m1.Set(4, 7);
		m1.Set(7, 8);

		m2.Set(2, 0);
		m2.Set(2, 1);
		m2.Set(2, 2);

		expected.Set(10, 0);
		expected.Set(24, 1);
		expected.Set(38, 2);

		if (m1 * m2 == expected)
			std::cout << "MULTIPLYING BY MATRIX: SUCCESS" << std::endl;
	}

	{
		Matrix m1(2, 2), expected(2, 2);

		m1.Set(1, 0);
		m1.Set(4, 1);
		m1.Set(1, 2);
		m1.Set(6, 3);

		expected.Set(3, 0);
		expected.Set(-2, 1);
		expected.Set(-0.5f, 2);
		expected.Set(0.5f, 3);

		auto m = !m1;

		if (m == expected)
			std::cout << "INVERSE MATRIX: SUCCESS" << std::endl;
	}

	{
		Matrix m1(4, 1), expected(4, 4);

		expected.SetAt(1, 0, 0);
		expected.SetAt(1, 1, 1);
		expected.SetAt(1, 2, 2);
		expected.SetAt(1, 3, 3);

		if (m1.identity() == expected)
			std::cout << "IDENTITY MATRIX: SUCCESS" << std::endl;
	}

	{
		Matrix m1(3, 2), expected(2, 3);

		m1.Set(1, 0);
		m1.Set(2, 1);
		m1.Set(3, 2);
		m1.Set(4, 3);
		m1.Set(5, 4);
		m1.Set(6, 5);

		expected.Set(1, 0);
		expected.Set(3, 1);
		expected.Set(5, 2);
		expected.Set(2, 3);
		expected.Set(4, 4);
		expected.Set(6, 5);

		if (m1.transpose() == expected)
			std::cout << "TRANSPOSE MATRIX: SUCCESS" << std::endl;
	}

	{
		Matrix m1(3, 3);

		m1.Set(1, 0);
		m1.Set(2, 1);
		m1.Set(2, 2);
		m1.Set(1, 3);
		m1.Set(5, 4);
		m1.Set(6, 5);
		m1.Set(8, 6);
		m1.Set(4, 7);
		m1.Set(7, 8);

		float expected = 21;

		if (floatNearlyEqual(m1.determinant(), expected))
			std::cout << "MATRIX DETERMINANT: SUCCESS" << std::endl;
	}

	// Rotate [1, 0, 0, 1] by 90 degrees
	{
		std::cout << "\n" <<  "/// ROTATION CHECK ///" << "\n";

		Matrix a = Matrix(4, 1);
		a.Set(1.0f, 0);
		a.Set(1.0f, 3);
		auto rotationMatrix = a.rotate(Axis::Y, PI / 2);

		std::cout << "Rotate [1, 0, 0, 1] by 90 degrees:" << "\n";
		std::cout << (rotationMatrix * a).toString() << "\n";

		Matrix expected(4, 1);

		expected.Set(0, 0);
		expected.Set(0, 1);
		expected.Set(-1, 2);
		expected.Set(1, 3);

		if(rotationMatrix * a == expected)
			std::cout << "VECTOR ROTATION: SUCCESS" << std::endl;
	}

	// Proof that matrix multiplication is not commutative
	{
		std::cout << "\n" << "/// COMMUTATIVE CHECK ///" << "\n";

		Matrix a = Matrix(2, 3);
		a.Set(1.0f, 0);
		a.Set(2.0f, 1);
		a.Set(3.0f, 2);
		a.Set(4.0f, 3);
		a.Set(5.0f, 4);
		a.Set(6.0f, 5);

		Matrix b = Matrix(3, 2);
		b.Set(10.0f, 0);
		b.Set(11.0f, 1);
		b.Set(20.0f, 2);
		b.Set(21.0f, 3);
		b.Set(30.0f, 4);
		b.Set(31.0f, 5);

		std::cout << "Matrix multiplication: a * b:" << "\n";
		std::cout << (a * b).toString() << "\n";

		std::cout << "Matrix multiplication: b * a:" << "\n";
		std::cout << (b * a).toString() << "\n";

		if(!(a * b == b * a))
			std::cout << "MATRIX MULTIPLICATION NOT COMMUTATIVE: SUCCESS" << std::endl;
	}
}
