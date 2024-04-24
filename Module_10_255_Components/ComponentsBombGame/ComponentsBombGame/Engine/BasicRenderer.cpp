#include "BasicRenderer.h"

#include <iostream>

BasicRenderer::BasicRenderer(const BasicRenderer& original, Actor* pOwner)
	: Component(pOwner, s_id)
	, m_sprite(original.m_sprite)
{
}

Component* BasicRenderer::Clone(Actor* pOwner)
{
	return new BasicRenderer(*this, pOwner);
}

void BasicRenderer::SetColor(Color* newColor)
{

}

void BasicRenderer::Render()
{
	std::cout << m_sprite;
}
