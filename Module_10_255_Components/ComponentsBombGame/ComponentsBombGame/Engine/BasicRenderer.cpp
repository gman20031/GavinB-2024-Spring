#include "BasicRenderer.h"

#include <iostream>

Component* BasicRenderer::Clone()
{
	return new BasicRenderer(*this);
}

void BasicRenderer::Render()
{
	std::cout << m_sprite;
}
