#pragma once

class Vector2
{
private:
	float m_X;
	float m_Y;

public:
	Vector2() = default;
	Vector2(float X, float Y) :m_X(X), m_Y(Y) {};

	float GetX() const {return m_X;}
	void SetX(float newX) { m_X = newX; }

	float GetY() const { return m_Y; }
	void SetY(float newY) { m_Y = newY; }
};
