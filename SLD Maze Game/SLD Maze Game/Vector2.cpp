#include "Vector2.h"

#include <math.h>

#define SQUARE(x) (x*x)

Vector2D::Vector2D(VectorType x, VectorType y )
	:m_xComponent(x)
	, m_yComponent(y)
	, m_magnitude(0)
	, m_squaredMagnitude(0)
	, m_direction(0)
{
	SetMagnitudeFromComponents();
	SetDirectionFromComponents();
	m_squaredMagnitude = GetSquaredDistance(m_xComponent, m_yComponent);
}

////////////////////////////////////Member Functions////////////////////////////////////


void Vector2D::SetX(VectorType newX)
{
	m_xComponent = newX;
	void SetMagnitudeFromComponents();
	void SetDirectionFromComponents();
}

void Vector2D::SetY(VectorType newY)
{
	m_yComponent = newY;
	void SetMagnitudeFromComponents();
	void SetDirectionFromComponents();
}

void Vector2D::SetMagnitude(VectorType newMag)
{
	m_magnitude = newMag;
	void SetXFromMagDir();
	void SetYFromMagDir();
}

void Vector2D::SetDirection(VectorType newDir)
{
	m_direction = newDir;
	SetXFromMagDir();
	SetYFromMagDir();
}

double Vector2D::GetSquaredDistance(VectorType x , VectorType y) const
{
	return ( SQUARE(m_xComponent) + SQUARE(m_yComponent) );
}

// Set magnitude using x and y
void Vector2D::SetMagnitudeFromComponents()
{
	m_magnitude = std::sqrt( GetSquaredDistance(m_xComponent,m_yComponent) );
}

// Set direction using x and y
void Vector2D::SetDirectionFromComponents()
{
	m_direction = std::atan2(m_xComponent, m_yComponent);
}

// Set x using magnitude and y
void Vector2D::SetXFromMagY()
{
	m_xComponent = std::sqrt( GetSquaredDistance(m_magnitude,m_yComponent) );
}
// Set y using magnitude and x
void Vector2D::SetYFromMagX()
{
	m_yComponent = std::sqrt( GetSquaredDistance(m_magnitude , m_xComponent) );
}
// Set x using Direction and Y
void Vector2D::SetXFromDirY()
{
	m_xComponent = m_yComponent / (std::tan(m_direction));
}
// Set Y using direction and X
void Vector2D::SetYFromDirX()
{
	m_yComponent = m_xComponent * (std::tan(m_direction));
}
// Set X using magnitude and direction
void Vector2D::SetXFromMagDir() {
	m_xComponent = m_magnitude * std::sin(m_direction);
}
// Set Y using Magnitude and direction
void Vector2D::SetYFromMagDir() {
	m_yComponent = m_magnitude * std::cos(m_direction);
}


////////////////////////////////////Overloading////////////////////////////////////


////////////////////////////////////
// Stream operators
////////////////////////////////////

std::ostream& operator<<(std::ostream& os, const Vector2D& vector)
{
	os << "{" << vector.m_xComponent << ", " << vector.m_yComponent << "}";
	return os;
}

////////////////////////////////////
// Comparison operators
////////////////////////////////////

//only compares x and y components
bool operator==(const Vector2D& lhs, const Vector2D& rhs)
{
	return (
		lhs.m_xComponent == rhs.m_xComponent
	and lhs.m_yComponent == rhs.m_yComponent
	);
}

////////////////////////////////////
// Arithmetic operators
////////////////////////////////////

Vector2D operator*(const Vector2D& lhs, VectorType rhs)
{
	return (Vector2D{
		lhs.m_xComponent * rhs,
		lhs.m_yComponent * rhs,
	});
}

Vector2D operator/(const Vector2D& lhs, VectorType rhs)
{
	return (Vector2D{
		lhs.m_xComponent / rhs,
		lhs.m_yComponent / rhs,
	});
}

Vector2D operator*(VectorType lhs, const Vector2D& rhs)
{
	return rhs * lhs;
}

Vector2D operator/(VectorType lhs, const Vector2D& rhs)
{
	return rhs / lhs;
}

////////////////////////////////////
// Unary operators
////////////////////////////////////
Vector2D Vector2D::operator-() const
{
	return Vector2D(
		-m_xComponent,
		-m_yComponent
	);
}

////////////////////////////////////
// assignment operators
////////////////////////////////////

Vector2D& Vector2D::operator/=(const VectorType rhs)
{
	*this = *this / rhs;
	return *this;
}

Vector2D& Vector2D::operator*=(const VectorType rhs)
{
	*this = *this * rhs;
	return *this;
}
