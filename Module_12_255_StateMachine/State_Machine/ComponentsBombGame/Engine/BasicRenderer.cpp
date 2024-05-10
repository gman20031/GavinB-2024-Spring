#include "BasicRenderer.h"

#include <iostream>

BasicRenderer::BasicRenderer(const BasicRenderer& original, Actor* pOwner)
	: Component(pOwner)
	, m_sprite(original.m_sprite)
{
	// empty
}

void BasicRenderer::Render()
{
	ConsoleManip::Printf(m_sprite, m_formatting);
}
