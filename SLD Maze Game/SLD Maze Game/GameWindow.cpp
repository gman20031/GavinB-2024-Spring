#include "GameWindow.h"
#include <iostream>

////////////////////////////////
/// Constructors
////////////////////////////////
GameWindow::GameWindow()
	:GameWindow("myGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 540, 540)
{
}

GameWindow::GameWindow(const char* title, int xPos, int yPos, int height, int width)
	:m_title(title)
	,m_xPosition(xPos)
	,m_yPosition(yPos)
	,m_height(height)
	,m_width(width)
{
}

////////////////////////////////
/// Set Rendering Color
////////////////////////////////
void GameWindow::SetRenderColor(SDL_Color* newColor)
{
	SDL_SetRenderDrawColor(m_graphicRenderer, newColor->r, newColor->g, newColor->b, newColor->a);
}

void GameWindow::SetRenderColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	SDL_SetRenderDrawColor(m_graphicRenderer, r, g, b, a);
}


////////////////////////////////
/// Start the widow
////////////////////////////////
void GameWindow::StartWindow()
{
	InitWindow();
	ClearWindowToBackgroundColor();
	
	Entity PlayerCharacter;
	
	/*
		   *
		  ***
		 *****
	*/

	
	Entity EnemyOne;




	bool keepWindowOpen = true;
	while (keepWindowOpen)
	{
		SDL_Event SdlEvent;
		while (SDL_PollEvent(&SdlEvent) > 0)
		{
			switch (SdlEvent.type)
			{
			case SDL_QUIT:
				keepWindowOpen = false;
				break;
			}

			SDL_UpdateWindowSurface(m_pDisplayWindow);
		}
	}

	SDL_DestroyWindow(m_pDisplayWindow);
	SDL_Quit(); // should remove renderer
	return;
}

void GameWindow::StopWindow()
{


}

/////////////////////////////////////////////////////
/// Clear window and replace all with selected color
/////////////////////////////////////////////////////
void GameWindow::ClearWindowToBackgroundColor()
{
	SetRenderColor(&m_backgroundColor);
	SDL_RenderClear(m_graphicRenderer); // fills render target with current color (red)
	SDL_RenderPresent(m_graphicRenderer); // Tell the renderer to go!
}

/////////////////////////////////////////////////////
/// Inits SDL, Renderer, and window
/////////////////////////////////////////////////////
void GameWindow::InitWindow()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("COuld not init SDL vido\n");
		return;
	}

	m_pDisplayWindow = SDL_CreateWindow(m_title, m_xPosition, m_yPosition, m_width, m_height, SDL_WINDOW_RESIZABLE);
	m_graphicRenderer = SDL_CreateRenderer(m_pDisplayWindow, -1, SDL_RENDERER_SOFTWARE);
}
