#pragma once
#include <iostream>

using VectorType = double;

class Vector2D
{
public:

	// Stream operators
	friend std::ostream& operator<<(std::ostream& os, const Vector2D& vector);
	// comparison operators
	friend bool operator==(const Vector2D& lhs, const Vector2D& rhs);
	auto operator<=>(const Vector2D&) const = default;
	// unary Operators
	Vector2D operator-() const;
	// arithmetic operators
	friend Vector2D operator*(const Vector2D& lhs, VectorType rhs);
	friend Vector2D operator/(const Vector2D& lhs, VectorType rhs);
	friend Vector2D operator*(VectorType lhs, const Vector2D& rhs);
	friend Vector2D operator/(VectorType lhs, const Vector2D& rhs);
	// assignment operators
	Vector2D& operator/=(const VectorType rhs);
	Vector2D& operator*=(const VectorType rhs);


private:
	VectorType m_xComponent;
	VectorType m_yComponent;
	VectorType m_magnitude;
	VectorType m_squaredMagnitude;
	double m_direction;

	double GetSquaredDistance(VectorType x, VectorType y) const;
	void SetMagnitudeFromComponents();
	void SetDirectionFromComponents();
	void SetXFromMagY();
	void SetYFromMagX();
	void SetXFromDirY();
	void SetYFromDirX();
	void SetXFromMagDir();
	void SetYFromMagDir();

public:
	Vector2D(VectorType x = 0, VectorType y = 0);

	VectorType GetX() const { return m_xComponent; }
	VectorType GetY() const { return m_yComponent; }
	VectorType GetMagnitude() const { return m_magnitude; }
	VectorType GetSquaredMagnitude() const { return m_squaredMagnitude; }
	double GetDirection() const { return m_squaredMagnitude; }

	void SetX(VectorType newX);
	void SetY(VectorType newy);
	void SetMagnitude(VectorType newMag);
	void SetDirection(double newDir);

};