#include "Vector3.h"

#include <math.h>

Vector3& Vector3::GenerateUnitVector()
{
	static Vector3 unitVector(1, 1, 1);
	return unitVector;
}

////////////////////////////////////////////////////////////
// Stream operators
////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& os, const Vector3& vector)
{
	os << "Vector3:{" << vector.m_x << ", " << vector.m_y << ", " << vector.m_z << "}";
	return os;
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

Vector3 Vector3::operator-() const
{
	return Vector3(-(m_x), -(m_y), -(m_z) );
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


void operator+=(Vector3& lhs, const Vector3 rhs)
{
	lhs = lhs + rhs;
}

void operator-=(Vector3& lhs, const Vector3 rhs)
{
	lhs = lhs - rhs;
}

void operator*=(Vector3& lhs, const VectorType rhs)
{
	lhs = lhs * rhs;
}

void operator/=(Vector3& lhs, const VectorType rhs)
{
	lhs = lhs / rhs;
}

////////////////////////////////////////////////////////////
// Member Functions
////////////////////////////////////////////////////////////

static double Square(float lhs)
{
	return lhs * lhs;
}

float Vector3::GetLength() const
{
	return sqrt( GetSquareLength() );
}

float Vector3::GetSquareLength() const
{
	return static_cast<VectorType> ( Square(m_x) + Square(m_y) + Square(m_z) );
}

float Vector3::GetDotProduct(const Vector3& right) const
{
	// https://mathinsight.org/dot_product_examples
	return(
		 (m_x * right.GetX())
		+(m_y * right.GetY())
		+(m_z * right.GetZ())
	)

}
Vector3 Vector3::GetCrossProduct(const Vector3& right) const
{
	//https://www.emathhelp.net/en/calculators/linear-algebra/cross-product-calculator/
	VectorType x = (m_y * right.m_z ) - (m_z * right.m_y );
	VectorType y = (m_z * right.m_x ) - (m_x * right.m_z );
	VectorType z = (m_x * right.m_y ) - (m_y * right.m_x );

	return Vector3(x, y , z);
}