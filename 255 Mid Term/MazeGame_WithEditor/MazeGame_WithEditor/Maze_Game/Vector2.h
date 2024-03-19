#pragma once

struct Vector2
{
	int x = 0;
	int y = 0;
};

bool operator==(const Vector2& lhs, const Vector2& rhs) 
{
	return (lhs.x == rhs.x
		and lhs.y == rhs.y);
}