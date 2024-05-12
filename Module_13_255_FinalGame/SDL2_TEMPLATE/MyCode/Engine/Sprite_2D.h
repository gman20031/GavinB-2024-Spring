#pragma once
#include "Renderer.h"
#include "system\Vector2d.h"

class Sprite_2D : public Sprite
{
private:
	SDL_Texture* m_pTexture;
	SDL_Renderer* m_pRenderer;

	uint16_t m_spriteSheetCount;
	SDL_Rect m_spriteSheetClip;
	double m_rotationAngle = 0;
	SDL_Point m_rotationPoint;
	SDL_RendererFlip m_flip;

	int m_spriteWidth;
	int m_spriteHeight;
	int m_textureWidth;
	int m_textureHeight;

private:
	void SetSpriteClip(int newSpriteSheetCount);

public:
	Sprite_2D(const char* filePath, Vector2d<int> spriteDimensions , SDL_Renderer* pRenderer);
	~Sprite_2D() { SDL_free(m_pTexture); }

	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
	void SetBlend(SDL_BlendMode blending);
	void SetAlpha(Uint8 alpha);
	void Rotate(int degreeChange);
	void SetRotation(int degrees);
	void Flip(SDL_RendererFlip flip);

	virtual void Render( Vector2d<int> actorPosition ) override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
};
