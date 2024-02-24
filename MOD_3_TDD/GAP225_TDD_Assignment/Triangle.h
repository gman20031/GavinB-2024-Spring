#pragma once

#include "Vector2.h"
#include <vector>


class Triangle
{
	static constexpr int k_numberOfVertecies = 3;

	Vector2 m_pVertexList[k_numberOfVertecies];
	float m_pSideLengths[k_numberOfVertecies];
	float m_perimiter;
	float m_area;

	void CalculateAndSetALl();
	void CalculatePermiter();
	void CalculateArea();
	float CalculateAndReturnSideLength(Vector2& vertex1, Vector2& vertex2);

	float Square(float squaredNumber);

public:
	Triangle(Vector2 vertex0, Vector2 vertex1, Vector2 vertex2);

	void SetVertex(int vertexIndex, Vector2* newLocation);
	Vector2 GetVertex(int vertexIndex) const;
	float GetSideLength(int SideIndex) const;

	float GetPerimeter() const { return m_perimiter; }
	float GetArea() const { return m_area; }
};