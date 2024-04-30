#pragma once

#include <filesystem>
#include "SDL.h"

class SpriteSDL
{
private:
	SDL_Texture* m_pTexture;
	SDL_Renderer* m_pRenderer;

	int m_width;
	int m_height;

public:
	SpriteSDL(int width, int height, SDL_Texture* pTexture, SDL_Renderer* pRenderer);
	//SpriteSDL(std::filesystem::path , SDL_Renderer* pRenderer);
	SpriteSDL(const char* filePath, SDL_Renderer* pRenderer);
	~SpriteSDL();

	SDL_Point GetDimensions() { return { m_width, m_height }; }
	SDL_Renderer* GetRenderer() { return m_pRenderer; }

	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
	void SetBlend(SDL_BlendMode blending);
	void SetAlpha(Uint8 alpha);
	void Render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);
};