#pragma once
#include "Renderer.h"
#include "system\Vector2d.h"
#include "Texture.h"

class Sprite_2D : public Sprite
{
private:
	Texture m_Texture;
	SDL_Renderer* m_pRenderer;

	double m_rotationAngle = 0;
	SDL_Point m_rotationPoint;
	SDL_RendererFlip m_flip;

private:
	void SetSpriteClip(int newSpriteSheetCount);

public:
	Sprite_2D(const char* filePath, int maxFrames, Vector2d<int> spriteDimensions , SDL_Renderer* pRenderer);

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
