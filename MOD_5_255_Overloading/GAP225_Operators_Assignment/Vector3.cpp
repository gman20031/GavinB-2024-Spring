#include "Vector3.h"

Vector3& Vector3::GenerateUnitVector()
{
	static Vector3 unitVector(1, 1, 1);
	return unitVector;
}

////////////////////////////////////////////////////////////
// comparison operators
////////////////////////////////////////////////////////////

bool operator==(const Vector3& lhs, const Vector3& rhs)
{
	return (lhs.m_x == rhs.m_x
		and lhs.m_y == rhs.m_y
		and lhs.m_z == rhs.m_z);
}

////////////////////////////////////////////////////////////
// unary Operators
////////////////////////////////////////////////////////////

Vector3 operator-(const Vector3& vector)
{
	VectorType x = -vector.m_x;
	VectorType y = -vector.m_y;
	VectorType z = -vector.m_z;

	return Vector3(x, y, z);
}


////////////////////////////////////////////////////////////
// arithmetic operators
////////////////////////////////////////////////////////////

Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
	VectorType x = lhs.m_x + rhs.m_x;
	VectorType y = lhs.m_y + rhs.m_y;
	VectorType z = lhs.m_z + rhs.m_z;
						   
	return Vector3(x, y, z);
}

Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
{
	VectorType x = lhs.m_x - rhs.m_x;
	VectorType y = lhs.m_y - rhs.m_y;
	VectorType z = lhs.m_z - rhs.m_z;

	return Vector3(x, y, z);
}

Vector3 operator*(const Vector3& lhs, VectorType rhs)
{
	VectorType x = lhs.m_x * rhs;
	VectorType y = lhs.m_y * rhs;
	VectorType z = lhs.m_z * rhs;

	return Vector3(x, y, z);
}

Vector3 operator/(const Vector3& lhs, VectorType rhs)
{
	VectorType x = lhs.m_x / rhs;
	VectorType y = lhs.m_y / rhs;
	VectorType z = lhs.m_z / rhs;

	return Vector3(x, y, z);
}

///// overloads /////

Vector3 operator*(VectorType lhs, const Vector3& rhs)
{
	return (rhs * lhs);
}

Vector3 operator/(VectorType lhs, const Vector3& rhs)
{
	return (rhs * lhs);
}

////////////////////////////////////////////////////////////
// assignment operators
////////////////////////////////////////////////////////////


Vector3& operator+=(Vector3& lhs, const Vector3 rhs)
{
	lhs = lhs + rhs;
	return(lhs);
}

Vector3& operator-=(Vector3& lhs, const Vector3 rhs)
{
	lhs = lhs - rhs;
	return(lhs);
}

Vector3& operator*=(Vector3& lhs, const VectorType rhs)
{
	lhs = lhs * rhs;
	return(lhs);
}

Vector3& operator/=(Vector3& lhs, const VectorType rhs)
{
	lhs = lhs / rhs;
	return(lhs);
}

