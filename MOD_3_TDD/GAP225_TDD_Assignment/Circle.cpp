#include <math.h>

#include "Circle.h"

///////////////////////////////
// Constructor
///////////////////////////////

Circle::Circle(Vector2& centerPoint, float radius)
	:m_centerPoint(centerPoint)
	,m_radius(radius)
{
	CalcAndSetDiameter();
	CalcAndSetCircumference();
	CalcAndSetArea();
}


///////////////////////////////
// Helper Functions
///////////////////////////////

void Circle::CalcAndSetDiameter() 
{
	m_diameter = m_radius * 2;
}
void Circle::CalcAndSetCircumference()
{
	m_circumference = k_pi * m_radius * 2;
}
void Circle::CalcAndSetArea()
{
	m_area = k_pi * (m_radius * m_radius);
}

///////////////////////////////
// Setters
///////////////////////////////

void Circle::SetCenterPoint(Vector2& newCenter)
{
	m_centerPoint = newCenter;
}

void Circle::SetRadius(float newRadius)
{
	m_radius = newRadius;
	CalcAndSetDiameter();
	CalcAndSetCircumference();
	CalcAndSetArea();
}

void Circle::SetDiameter(float newDiameter)
{
	m_diameter = newDiameter;
	m_radius = newDiameter / 2;
	CalcAndSetCircumference();
	CalcAndSetArea();
}

///////////////////////////////
// Collision checker
///////////////////////////////

float Circle::Square(float squaredNumber)
{
	return squaredNumber * squaredNumber;
}

/// Calculates and returns the distance between two vector2's
float Circle::DistanceBetweenVectors(Vector2 vector1, Vector2 vector2)
{
	//distance = sqrt( xcomponent^2 + ycomponent^2)
	float xComponent = Square((vector1.GetX() - vector2.GetX()));
	float yComponent = Square((vector1.GetY() - vector2.GetY()));
	return static_cast<float>(sqrt(xComponent + yComponent));

}

bool Circle::CollidesWithCircle(Circle* otherCircle)
{
	float combinedRadii = otherCircle->GetRadius() + m_radius;
	
	return(DistanceBetweenVectors(m_centerPoint, otherCircle->GetCenterPoint()) <= combinedRadii);

}

