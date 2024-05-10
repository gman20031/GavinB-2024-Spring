#pragma once
#include "Renderer.h"

class Sprite_2D : public Sprite
{
private:
	SDL_Texture* m_pTexture;
	SDL_Renderer* m_pRenderer;

	int m_width;
	int m_height;

public:
	Sprite_2D(const char* filePath, SDL_Renderer* pRenderer);

	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
	void SetBlend(SDL_BlendMode blending);
	void SetAlpha(Uint8 alpha);

	virtual void Render() override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
};

