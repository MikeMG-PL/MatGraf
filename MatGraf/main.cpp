#include <iostream>
#include "Matrix.h"

int main()
{
	// Just a random check, fill it with a regular exercise content :>

	Matrix m1(3, 2);

	m1.Set(1, 0);
	m1.Set(5, 1);
	m1.Set(4, 2);
	m1.Set(3, 3);
	m1.Set(2, 4);
	m1.Set(6, 5);

	for(int i = 0; i < m1.GetVectorSize(); i++)
		std::cout << m1.transpose().Get(i) << std::endl;
}
