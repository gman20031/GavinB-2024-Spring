#pragma once

struct Vector2
{
	int x = 0;
	int y = 0;

	bool operator==(const Vector2& rhs) 
	{
		return (this->x == rhs.x
			and this->y == rhs.y);
	}
};
