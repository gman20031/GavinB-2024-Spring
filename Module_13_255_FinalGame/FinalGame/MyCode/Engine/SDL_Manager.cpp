#include "SDL_Manager.h"
#include <assert.h>

void SDL_Manager::Init(const char* title, int xPos, int yPos, int width, int height , SDL_WindowFlags windowFlags)
{
	assert(SDL_Init(SDL_INIT_VIDEO) == 0);
	m_pWindow = SDL_CreateWindow(title, xPos, yPos, width, height, windowFlags);
	m_pRenderer = SDL_CreateRenderer(m_pWindow, NULL, NULL);
	
	m_xPos = xPos;
	m_yPos = yPos;
	m_width = width;
	m_height = height;
}

WindowInfo SDL_Manager::GetWindowInfo()
{
	return WindowInfo({
		m_xPos, m_yPos,
		m_width, m_height
	});
}
