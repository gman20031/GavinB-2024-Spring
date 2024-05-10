#include "SpriteSDL.h"

#include <SDL.h>
#include <iostream>

#include "../../System/ConsoleManip.h"

SpriteSDL::SpriteSDL(int width, int height, SDL_Texture* pTexture, SDL_Renderer* pRenderer)
	: m_width(width)
	, m_height(height)
	, m_pTexture(pTexture)
	, m_pRenderer(pRenderer)
{
	// REQUIRES NO FURTHER CALLS
}

SpriteSDL::SpriteSDL(const char* filePath, SDL_Renderer* pRenderer)
	: m_pTexture(nullptr)
	, m_width(0)
	, m_height(0)
	, m_pRenderer(pRenderer)
{
	SDL_Surface* pSurface = SDL_LoadBMP(filePath);
	if (!pSurface)
	{
		std::cout << "surface not loaded!\n";
		std::cout << filePath << '\n';
		ConsoleManip::Pause();
		return;
	}

	SDL_SetColorKey(pSurface, SDL_TRUE , SDL_MapRGB( pSurface->format , 0,0,0) );

	m_pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
	m_width = pSurface->w;
	m_height = pSurface->h;
	SDL_FreeSurface(pSurface);
}

SpriteSDL::~SpriteSDL()
{
	SDL_free(m_pTexture);
}

void SpriteSDL::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(m_pTexture, red, green, blue);
}

void SpriteSDL::SetBlend(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(m_pTexture, blending);
}

void SpriteSDL::SetAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(m_pTexture, alpha);
}

void SpriteSDL::Render(
	int x, int y,
	SDL_Rect* clip,
	double angle,
	SDL_Point* center,
	SDL_RendererFlip flip	)
{
	SDL_Rect renderQuad{ x, y, m_width, m_height };

	//Render to screen
	if (SDL_RenderCopyEx(m_pRenderer, m_pTexture, clip, &renderQuad, angle, center, flip) != 0)
	{
		std::cout << SDL_GetError();
	}
}
