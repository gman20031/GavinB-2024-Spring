#pragma once
#include <type_traits>
#include <concepts>
#include <iostream>
#include <math.h>
	
template<typename T>
concept Number = std::is_arithmetic_v<T>;

template<Number dataType>
class Vector2d
{
public:
	// Stream operators
	//friend std::ostream& operator<<(std::ostream& os, const Vector2d& vector);
	// comparison operators
	//friend bool operator==(const Vector2d& lhs, const Vector2d& rhs);
	auto operator<=>(const Vector2d&) const = default;
	// unary Operators
	Vector2d operator-() const;
	// arithmetic operators
	//friend Vector2d operator+(const Vector2d& lhs, const Vector2d& rhs);
	//friend Vector2d operator-(const Vector2d& lhs, const Vector2d& rhs);
	//friend Vector2d operator*(const Vector2d& lhs, dataType rhs);
	//friend Vector2d operator/(const Vector2d& lhs, dataType rhs);
	//friend Vector2d operator*(dataType lhs, const Vector2d& rhs);
	//friend Vector2d operator/(dataType lhs, const Vector2d& rhs);
	// assignment operators
	Vector2d& operator+=(const Vector2d rhs);
	Vector2d& operator-=(const Vector2d rhs);
	Vector2d& operator/=(const dataType rhs);
	Vector2d& operator*=(const dataType rhs);
	//Increment/decrement
	Vector2d& operator++();
	Vector2d& operator--();
	Vector2d operator++(int);
	Vector2d operator--(int);


public:
	dataType x, y;

	constexpr Vector2d(dataType _x, dataType _y) : x(_x), y(_y) {}
	constexpr static const Vector2d& GetUnitVector();

	constexpr dataType GetLength() const;
	constexpr dataType GetSquareLength() const;
	constexpr dataType GetDotProduct(const Vector2d& right) const;
	//Vector2d GetCrossProduct(const Vector3& right) const;
};


/////////////////////////////////////////////
/// Stream operators
/////////////////////////////////////////////

template<Number dataType>
std::ostream& operator<<(std::ostream& os, const Vector2d<dataType>& vector)
{
	os << "(" << vector.x << "," << vector.y << ")";
	return os;
}


/////////////////////////////////////////////
/// Comparison Operators
/////////////////////////////////////////////

// FUNCTION NOT WORKING
//template<Number dataType>
//bool operator==(const Vector2d<dataType>& lhs, const Vector2d<dataType>& rhs)
//{
//	return(
//		lhs.x == rhs.x
//	and lhs.y == rhs.y
//	);
//}


/////////////////////////////////////////////
/// Unary operators
/////////////////////////////////////////////

template<Number dataType>
Vector2d<dataType> Vector2d<dataType>::operator-() const
{
	return Vector2d(-(x), -(y));
}


/////////////////////////////////////////////
/// arithmetic operators
/////////////////////////////////////////////
template<Number dataType>
inline Vector2d<dataType> operator+(const Vector2d<dataType>& lhs, const Vector2d<dataType>& rhs)
{
	return Vector2d(
		lhs.x + rhs.x,
		lhs.y + rhs.y
	);
}
template<Number dataType>
inline Vector2d<dataType> operator-(const Vector2d<dataType>& lhs, const Vector2d<dataType>& rhs)
{
	return Vector2d(
		lhs.x - rhs.x,
		lhs.y - rhs.y
	);
}
template<Number dataType>
inline Vector2d<dataType> operator*(const Vector2d<dataType>& lhs, dataType rhs)
{
	return Vector2d(
		lhs.x * rhs,
		lhs.y * rhs
	);
}
template<Number dataType>
inline Vector2d<dataType> operator/(const Vector2d<dataType>& lhs, dataType rhs)
{
	return Vector2d(
		lhs.x / rhs,
		lhs.y / rhs
	);
}

////// overloads //////

template<Number dataType>
inline Vector2d<dataType> operator*(dataType lhs, const Vector2d<dataType>& rhs)
{
	return (rhs * lhs);
}
template<Number dataType>
inline Vector2d<dataType> operator/(dataType lhs, const Vector2d<dataType>& rhs)
{
	return (rhs / lhs);
}

/////////////////////////////////////////////
/// assignment operators
/////////////////////////////////////////////

template<Number dataType>
inline Vector2d<dataType>& Vector2d<dataType>::operator+=(const Vector2d<dataType> rhs)
{
	*this = *this + rhs;
	return *this;
}

template<Number dataType>
inline Vector2d<dataType>& Vector2d<dataType>::operator-=(const Vector2d<dataType> rhs)
{
	*this = *this - rhs;
	return *this;
}

template<Number dataType>
inline Vector2d<dataType>& Vector2d<dataType>::operator/=(const dataType rhs)
{
	*this = *this * rhs;
	return *this;
}

template<Number dataType>
inline Vector2d<dataType>& Vector2d<dataType>::operator*=(const dataType rhs)
{
	*this = *this / rhs;
	return *this;
}


/////////////////////////////////////////////
/// Increment/decrement
/////////////////////////////////////////////

template<Number dataType>
inline Vector2d<dataType>& Vector2d<dataType>::operator++()
{
	++x;
	++y;
	return *this;
}

template<Number dataType>
inline Vector2d<dataType>& Vector2d<dataType>::operator--()
{
	--x;
	--y;
	return *this;
}

template<Number dataType>
inline Vector2d<dataType> Vector2d<dataType>::operator++(int)
{
	Vector2d oldValue = *this;
	operator++();
	return oldValue;
}

template<Number dataType>
inline Vector2d<dataType> Vector2d<dataType>::operator--(int)
{
	Vector2d oldValue = *this;
	operator--();
	return oldValue;
}


/////////////////////////////////////////////
/// Member Functions
/////////////////////////////////////////////


/////////////////////////////////////////////
/// Returns const& to a static unit vector
/////////////////////////////////////////////
template<Number dataType>
constexpr const Vector2d<dataType>& Vector2d<dataType>::GetUnitVector()
{
	static const Vector2d unitVector(dataType(1), dataType(1));
	return unitVector;
}

template<Number dataType>
constexpr dataType Vector2d<dataType>::GetLength() const
{
	return std::sqrt(GetSquareLength());
}

template<Number dataType>
constexpr dataType Vector2d<dataType>::GetSquareLength() const
{
	return (x * x) + (y * y);
}

template<Number dataType>
constexpr dataType Vector2d<dataType>::GetDotProduct(const Vector2d& right) const
{
	return Vector2d(
		x * right.x ,
		y * right.y
	);
}

//template<Number dataType>
//Vector3 Vector2d<dataType>GetCrossProduct(const Vector3& right) const
//{
//
//}

