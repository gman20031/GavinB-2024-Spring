#pragma once

#include <iostream>
using VectorType = float;
class Vector3
{
	// Stream operators
	friend std::ostream& operator<<(std::ostream& os, const Vector3& vector);
	// comparison operators
	friend bool operator==(const Vector3& lhs, const Vector3& rhs);
	// unary Operators
public:
	Vector3 operator-() const;
private:
	// arithmetic operators
	friend Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
	friend Vector3 operator-(const Vector3& lhs, const Vector3& rhs);
	friend Vector3 operator*(const Vector3& lhs, VectorType rhs);
	friend Vector3 operator/(const Vector3& lhs, VectorType rhs);
	friend Vector3 operator*(VectorType lhs, const Vector3& rhs);
	friend Vector3 operator/(VectorType lhs, const Vector3& rhs);
	// assignment operators
	friend void operator+=(Vector3& lhs, const Vector3 rhs);
	friend void operator-=(Vector3& lhs, const Vector3 rhs);
	friend void operator/=(Vector3& lhs, const VectorType rhs);
	friend void operator*=(Vector3& lhs, const VectorType rhs);

	VectorType m_x;
	VectorType m_y;
	VectorType m_z;
public:
	Vector3(VectorType x = 0, VectorType y = 0, VectorType z = 0)
		:m_x(x)
		,m_y(y)
		,m_z(z)
	{}

	static Vector3& GenerateUnitVector();

	float GetLength() const;
	float GetSquareLength() const;
	float GetDotProduct(const Vector3& right) const;
	Vector3 GetCrossProduct(const Vector3& right) const;

	VectorType GetX() const { return m_x; }
	VectorType GetY() const { return m_y; }
	VectorType GetZ() const { return m_z; }
};


