#pragma once

#include <iostream>
using VectorType = float;
class Vector3
{
public:
	// Stream operators
	friend std::ostream& operator<<(std::ostream& os, const Vector3& vector);
	// comparison operators
	friend bool operator==(const Vector3& lhs, const Vector3& rhs);
	auto operator<=>(const Vector3&) const = default;
	// unary Operators
	Vector3 operator-() const;
	// arithmetic operators
	friend Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
	friend Vector3 operator-(const Vector3& lhs, const Vector3& rhs);
	friend Vector3 operator*(const Vector3& lhs, VectorType rhs);
	friend Vector3 operator/(const Vector3& lhs, VectorType rhs);
	friend Vector3 operator*(VectorType lhs, const Vector3& rhs);
	friend Vector3 operator/(VectorType lhs, const Vector3& rhs);
	// assignment operators
	Vector3& operator+=(const Vector3 rhs);
	Vector3& operator-=(const Vector3 rhs);
	Vector3& operator/=(const VectorType rhs);
	Vector3& operator*=(const VectorType rhs);
	//Increment/decrement
	Vector3& operator++();
	Vector3& operator--();
	Vector3 operator++(int);
	Vector3 operator--(int);

private:
	VectorType m_x;
	VectorType m_y;
	VectorType m_z;
public:
	Vector3(VectorType x = 0, VectorType y = 0, VectorType z = 0)
		:m_x(x)
		,m_y(y)
		,m_z(z)
	{}

	static const Vector3& GenerateUnitVector();

	float GetLength() const;
	float GetSquareLength() const;
	float GetDotProduct(const Vector3& right) const;
	Vector3 GetCrossProduct(const Vector3& right) const;

	VectorType GetX() const { return m_x; }
	VectorType GetY() const { return m_y; }
	VectorType GetZ() const { return m_z; }
};


