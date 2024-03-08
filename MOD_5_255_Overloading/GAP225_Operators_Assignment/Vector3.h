#pragma once


using VectorType = float;
class Vector3
{
	VectorType m_x;
	VectorType m_y;
	VectorType m_z;
public:
	Vector3(VectorType x, VectorType y, VectorType z);

	VectorType GetX() { return m_x; }
	VectorType GetY() { return m_y; }
	VectorType GetZ() { return m_z; }

};
