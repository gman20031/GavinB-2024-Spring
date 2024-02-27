#pragma once
#include "SDL.h"

class DisplayModel
{
	int m_vertexCount;
	SDL_Color m_displayColor{ 0,0,0,255 };
	SDL_Vertex* m_charModel = nullptr;
public:
	DisplayModel(int vertexCount)
	:m_vertexCount(vertexCount)
	{

	}

};