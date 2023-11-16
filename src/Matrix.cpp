#include "Matrix.h"
#include <iostream>
#include "MathHelpers.h"
#include "Vector.h"

float Matrix::GetAt(unsigned int m, unsigned int n) const
{
	const int index = m * columns + n;
	return matrixArray[index];
}

void Matrix::SetAt(float value, unsigned int m, unsigned int n)
{
	const int index = m * columns + n;
	matrixArray[index] = value;
}

float Matrix::Get(unsigned i) const
{
	return matrixArray[i];
}

void Matrix::Set(float value, unsigned i)
{
	matrixArray[i] = value;
}

unsigned Matrix::GetRows() const
{
	return rows;
}

unsigned Matrix::GetColumns() const
{
	return columns;
}

unsigned Matrix::GetVectorSize() const
{
	return rows * columns;
}


// std::string Matrix::toString()
// {
// }

Matrix Matrix::operator+(const Matrix& m) const
{
	if (GetVectorSize() != m.GetVectorSize())
		throw std::invalid_argument("Invalid matrix dimensions");

	Matrix result(GetRows(), GetColumns());

	for (int i = 0; i < GetVectorSize(); i++)
	{
		result.Set(Get(i) + m.Get(i), i);
	}

	return result;
}

Matrix Matrix::operator-(const Matrix& m) const
{
	if (GetVectorSize() != m.GetVectorSize())
		throw std::invalid_argument("Invalid matrix dimensions");

	Matrix result(GetRows(), GetColumns());

	for (int i = 0; i < GetVectorSize(); i++)
	{
		result.Set(Get(i) - m.Get(i), i);
	}

	return result;
}

bool Matrix::operator==(const Matrix& m)
{
	if (GetVectorSize() != m.GetVectorSize())
		throw std::invalid_argument("Invalid matrix dimensions");

	bool equal;

	for (int i = 0; i < GetVectorSize(); i++)
	{
		equal = floatNearlyEqual(Get(i), m.Get(i)) ? true : false;

		if (!equal)
			return false;
	}

	return true;
}

Matrix Matrix::operator*(float f) const
{
	Matrix result(GetRows(), GetColumns());

	for (int i = 0; i < GetVectorSize(); i++)
	{
		result.Set(Get(i) * f, i);
	}

	return result;
}

Matrix Matrix::operator*(const Matrix& m) const
{
	if (GetRows() != m.GetColumns())
		throw std::invalid_argument("Invalid matrix dimensions");

	Matrix result(GetRows(), m.GetColumns());

	for (unsigned int i = 0; i < GetRows(); i++) {
		for (unsigned int j = 0; j < m.GetColumns(); j++) {
			float sum = 0.0;
			for (unsigned int k = 0; k < GetColumns(); k++) {
				sum += GetAt(i, k) * m.GetAt(k, j);
			}
			result.SetAt(sum, i, j);
		}
	}

	return result;
}

Matrix Matrix::operator!()
{
	return inverse();
}

Matrix Matrix::inverse() const
{
	if (GetRows() != GetColumns())
		throw std::invalid_argument("Invalid matrix dimensions for inversion");

	float det = determinant();

	if (det == 0)
		throw std::invalid_argument("Cannot calculate inverse matrix when its determinant equals 0");

	Matrix adjoint(GetRows(), GetColumns());

	for (unsigned int i = 0; i < GetRows(); i++) {
		for (unsigned int j = 0; j < GetColumns(); j++) {
			float cofactor = cofactorAt(i, j);
			adjoint.SetAt(cofactor, j, i);
		}
	}

	Matrix inverseMatrix = adjoint * (1.0 / det);

	return inverseMatrix;
}

Matrix Matrix::identity() const
{
	if (GetRows() != GetColumns())
		throw std::invalid_argument("Invalid matrix dimensions");

	Matrix id(GetRows(), GetColumns());

	for(int i = 0; i < GetVectorSize(); i++)
		id.Set(0, i);

	for (int i = 0; i < GetRows(); i++)
		id.SetAt(1, i, i);

	return id;
}

Matrix Matrix::transpose() const
{
	Matrix result(GetColumns(), GetRows());

	for (unsigned int i = 0; i < GetRows(); i++) {
		for (unsigned int j = 0; j < GetColumns(); j++) {
			result.SetAt(GetAt(i, j), j, i);
		}
	}

	return result;
}

float Matrix::determinant() const
{
	if (GetRows() != GetColumns())
		throw std::invalid_argument("Invalid matrix dimensions");

	float det = 0;

	switch (GetRows())
	{
	case 1:
		det = Get(0);
		break;

	case 2:
		det = GetAt(0, 0) * GetAt(1, 1) - GetAt(0, 1) * GetAt(1, 0);
		break;

	case 3:
		det = GetAt(0, 0) * (GetAt(1, 1) * GetAt(2, 2) - GetAt(2, 1) * GetAt(1, 2)) -
			GetAt(0, 1) * (GetAt(1, 0) * GetAt(2, 2) - GetAt(2, 0) * GetAt(1, 2)) +
			GetAt(0, 2) * (GetAt(1, 0) * GetAt(2, 1) - GetAt(2, 0) * GetAt(1, 1));
		break;

	case 4:
		det = GetAt(0, 0) * (GetAt(1, 1) * (GetAt(2, 2) * GetAt(3, 3) - GetAt(3, 2) * GetAt(2, 3)) -
			GetAt(2, 1) * (GetAt(1, 2) * GetAt(3, 3) - GetAt(3, 2) * GetAt(1, 3)) +
			GetAt(3, 1) * (GetAt(1, 2) * GetAt(2, 3) - GetAt(2, 2) * GetAt(1, 3))) -
			GetAt(1, 0) * (GetAt(0, 1) * (GetAt(2, 2) * GetAt(3, 3) - GetAt(3, 2) * GetAt(2, 3)) -
				GetAt(2, 1) * (GetAt(0, 2) * GetAt(3, 3) - GetAt(3, 2) * GetAt(0, 3)) +
				GetAt(3, 1) * (GetAt(0, 2) * GetAt(2, 3) - GetAt(2, 2) * GetAt(0, 3))) +
			GetAt(2, 0) * (GetAt(0, 1) * (GetAt(1, 2) * GetAt(3, 3) - GetAt(3, 1) * GetAt(1, 3)) -
				GetAt(1, 1) * (GetAt(0, 2) * GetAt(3, 3) - GetAt(3, 1) * GetAt(0, 3)) +
				GetAt(3, 1) * (GetAt(0, 2) * GetAt(1, 3) - GetAt(1, 2) * GetAt(0, 3))) -
			GetAt(3, 0) * (GetAt(0, 1) * (GetAt(1, 2) * GetAt(2, 3) - GetAt(2, 2) * GetAt(1, 3)) -
				GetAt(1, 1) * (GetAt(0, 2) * GetAt(2, 3) - GetAt(2, 2) * GetAt(0, 3)) +
				GetAt(2, 1) * (GetAt(0, 2) * GetAt(1, 3) - GetAt(1, 2) * GetAt(0, 3)));
		break;

	default:
		throw std::logic_error("Calculating determinant for matrices over 4x4 is not implemented");
	}

	return det;
}

float Matrix::cofactorAt(unsigned int row, unsigned int col) const
{
	Matrix minor(GetRows() - 1, GetColumns() - 1);
	for (unsigned int i = 0, r = 0; i < GetRows(); i++) {
		if (i == row)
			continue;
		for (unsigned int j = 0, c = 0; j < GetColumns(); j++) {
			if (j == col)
				continue;
			minor.SetAt(GetAt(i, j), r, c);
			c++;
		}
		r++;
	}

	return minor.determinant() * ((row + col) % 2 == 0 ? 1.0 : -1.0);
}

Matrix Matrix::translate(const Vector& vector)
{
	if (GetRows() != 4 || GetColumns() != 1)
		throw std::invalid_argument("Invalid matrix dimensions");

	Matrix id = identity();

	id.SetAt(vector.x, 0, 3);
	id.SetAt(vector.y, 1, 3);
	id.SetAt(vector.z, 2, 3);

	return id;
}

Matrix Matrix::rotate(Axis axis, float angle)
{
	if (GetRows() != 4 || GetColumns() != 1)
		throw std::invalid_argument("Invalid matrix dimensions");

	Matrix result = identity();

	float cosTheta = std::cos(angle);
	float sinTheta = std::sin(angle);

	switch (axis) {
	case X:
		result.SetAt(1.0, 0, 0);
		result.SetAt(cosTheta, 1, 1);
		result.SetAt(-sinTheta, 1, 2);
		result.SetAt(sinTheta, 2, 1);
		result.SetAt(cosTheta, 2, 2);
		break;

	case Y:
		result.SetAt(cosTheta, 0, 0);
		result.SetAt(sinTheta, 0, 2);
		result.SetAt(-sinTheta, 2, 0);
		result.SetAt(cosTheta, 2, 2);
		break;

	case Z:
		result.SetAt(cosTheta, 0, 0);
		result.SetAt(-sinTheta, 0, 1);
		result.SetAt(sinTheta, 1, 0);
		result.SetAt(cosTheta, 1, 1);
		break;

	default:
		throw std::invalid_argument("Invalid rotation axis");
	}

	return result;
}

Matrix Matrix::scale(const Vector& vector)
{
	if (GetRows() != 4 || GetColumns() != 1)
		throw std::invalid_argument("Invalid matrix dimensions");

	Matrix id = identity();

	id.SetAt(vector.x, 0, 0);
	id.SetAt(vector.y, 1, 1);
	id.SetAt(vector.z, 2, 2);

	return id;
}

