#pragma once
#include "Renderer.h"
#include "system\Vector2d.h"


class Sprite_2D : public Sprite
{
private:
	SDL_Texture* m_pTexture;
	SDL_Renderer* m_pRenderer;

	int m_spriteWidth;
	int m_spriteHeight;
	int m_textureWidth;
	int m_textureHeight;
	uint16_t m_frameNumber;
	SDL_Rect m_frameClipping;

	double m_rotationAngle = 0;
	SDL_Point m_rotationPoint;
	SDL_RendererFlip m_flip;

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

	void SetFrameCount(unsigned int frameNumber);
	void ChangeFrameCount(int changeAmount );

	virtual void Render( Vector2d<int> actorPosition ) override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
};
