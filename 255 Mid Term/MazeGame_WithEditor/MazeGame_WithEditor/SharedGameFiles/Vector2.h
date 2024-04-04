#pragma once
//simple struct containing x and y values, as well as a comparison operator
struct Vector2
{
	int x = 0;
	int y = 0;

	friend bool operator==(const Vector2& lhs, const Vector2& rhs)
	{
		return (lhs.x == rhs.x
			and lhs.y == rhs.y);
	}
};