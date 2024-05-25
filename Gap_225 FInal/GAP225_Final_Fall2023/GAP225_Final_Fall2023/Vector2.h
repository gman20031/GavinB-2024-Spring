#pragma once

template<typename ComponentType>
struct Vector2
{
	ComponentType m_x;
	ComponentType m_y;
};

template<typename Type>
std::ostream& operator<<(std::ostream& out, const Vector2<Type>& vector)
{
	out << vector.m_x << ',' << vector.m_y;

	return out;
}

template<typename Type>
std::istream& operator>>(std::istream& in, Vector2<Type>& vector)
{
	vector.m_x = (Type)in.get() - '0';
	in.ignore();
	vector.m_y = (Type)in.get() - '0';

	return in;
}


template<typename Type>
bool operator==(const Vector2<Type>& lhs, const Vector2<Type>& rhs)
{
	return {
		lhs.m_x == rhs.m_x &&
		lhs.m_y == rhs.m_y
	};
}