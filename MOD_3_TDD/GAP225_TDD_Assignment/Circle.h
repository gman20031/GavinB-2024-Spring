#pragma once
#include "vector2.h"

class Circle
{
	static constexpr float k_pi = 3.1415;
	Vector2 m_centerPoint;
	float m_radius;
	float m_diameter;
	float m_circumference;
	float m_area;

	void CalcAndSetDiameter();
	void CalcAndSetCircumference();
	void CalcAndSetArea();

	float Square(float squaredNumber);
	float DistanceBetweenVectors(Vector2 vector1, Vector2 vector2);

public:
	Circle(Vector2& centerPoint, float radius);

	void SetCenterPoint(Vector2& newCenter);
	void SetRadius(float newRadius);
	void SetDiameter(float newDiameter);

	Vector2 GetCenterPoint() const { return m_centerPoint; }
	float GetRadius() const { return m_radius; }
	float GetDiameter() const { return m_diameter; }
	float GetCircumference() const { return m_circumference; }
	float GetArea() const { return m_area; }

	bool CollidesWithCircle(Circle* otherCircle);

};