#include "Sprite_2D.h"

Sprite_2D::Sprite_2D(const char* filePath, SDL_Renderer* pRenderer)
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

	SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0, 0, 0));

	m_pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
	m_width = pSurface->w;
	m_height = pSurface->h;
	SDL_FreeSurface(pSurface);
}

void Sprite_2D::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(m_pTexture, red, green, blue);
}

void Sprite_2D::SetBlend(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(m_pTexture, blending);
}

void Sprite_2D::SetAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(m_pTexture, alpha);
}

void Sprite_2D::Render()
{

}

void Sprite_2D::OnEnter()
{
#if DEBUG
	std::cout << "Sprite added to Renderer\n";
#endif
}

void Sprite_2D::OnExit()
{
#if DEBUG
	std::cout << "Sprite removed from Renderer\n";
#endif
}
