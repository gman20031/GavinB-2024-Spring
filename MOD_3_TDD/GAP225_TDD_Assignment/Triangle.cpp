#include "Triangle.h"
#include "math.h"

////////////////////////////////////////////
// Math Functions
////////////////////////////////////////////

float Triangle::Square(float squaredNumber)
{
	return squaredNumber * squaredNumber;
}

////////////////////////////////////////////
// Init / calculation Functons
////////////////////////////////////////////

void Triangle::CalculateAndSetALl()
{
	m_pSideLengths[0] = CalculateAndReturnSideLength(m_pVertexList[0], m_pVertexList[1]);	// .GetSideLength(0)  between points 0 and 1
	m_pSideLengths[1] = CalculateAndReturnSideLength(m_pVertexList[1], m_pVertexList[2]);	// .GetSideLength(1)  between points 1 and 2
	m_pSideLengths[2] = CalculateAndReturnSideLength(m_pVertexList[2], m_pVertexList[0]);	// .GetSideLength(2)  between points 0 and 2

	CalculatePermiter();
	CalculateArea();
}


void Triangle::CalculatePermiter()
{
	m_perimiter = m_pSideLengths[0] + m_pSideLengths[1] + m_pSideLengths[2];
}

void Triangle::CalculateArea()
{
	//trinalge Area Formula
	// https://www.britannica.com/science/Herons-formula#:~:text=Heron%27s%20formula%2C%20formula%20credited%20to,%2B%20b%20%2B%20c)%2F2.
	///////////////////////

	float semiP = m_perimiter / 2;
	m_area = sqrt(semiP * (semiP - m_pSideLengths[0]) * (semiP - m_pSideLengths[1]) * (semiP - m_pSideLengths[2]));
}

float Triangle::CalculateAndReturnSideLength(Vector2& vertex1, Vector2& vertex2)
{
	//distance = sqrt( xcomponent^2 + ycomponent^2)
	float xComponent = Square((vertex1.GetX() - vertex2.GetX()));
	float yComponent = Square((vertex1.GetY() - vertex2.GetY()));
	return sqrt(xComponent + yComponent);
}

Triangle::Triangle(Vector2 vertex0, Vector2 vertex1, Vector2 vertex2)
{
	m_pVertexList[0] = vertex0;
	m_pVertexList[1] = vertex1;
	m_pVertexList[2] = vertex2;

	CalculateAndSetALl();
}

////////////////////////////////////////////
// Getter and Setter Functions
////////////////////////////////////////////


void Triangle::SetVertex(int vertexIndex, Vector2* newLocation)
{
	m_pVertexList[vertexIndex] = *newLocation;
	CalculateAndSetALl();
}

Vector2 Triangle::GetVertex(int vertexIndex) const
{
	return m_pVertexList[vertexIndex];
}

float Triangle::GetSideLength(int SideIndex) const
{
	return m_pSideLengths[SideIndex];
}
