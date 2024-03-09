#pragma once


using VectorType = float;
class Vector3
{
	VectorType m_x;
	VectorType m_y;
	VectorType m_z;
	
	// comparison operators

	friend bool operator==(const Vector3& lhs, const Vector3& rhs);

	// unary Operators

	friend Vector3 operator-(const Vector3& vector);

	// arithmetic operators

	friend Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
	friend Vector3 operator-(const Vector3& lhs, const Vector3& rhs);
	friend Vector3 operator*(const Vector3& lhs, VectorType rhs);
	friend Vector3 operator/(const Vector3& lhs, VectorType rhs);
	friend Vector3 operator*(VectorType lhs, const Vector3& rhs);
	friend Vector3 operator/(VectorType lhs, const Vector3& rhs);

	// assignment operators

	friend Vector3& operator+=(Vector3& lhs, const Vector3 rhs);
	friend Vector3& operator-=(Vector3& lhs, const Vector3 rhs);
	friend Vector3& operator/=(Vector3& lhs, const VectorType rhs);
	friend Vector3& operator*=(Vector3& lhs, const VectorType rhs);
public:
	Vector3(VectorType x = 0, VectorType y = 0, VectorType z = 0) 
		:m_x(x)
		,m_y(y)
		,m_z(z)
	{}

	static Vector3& GenerateUnitVector();

	VectorType GetX() const { return m_x; }
	VectorType GetY() const { return m_y; }
	VectorType GetZ() const { return m_z; }

};
