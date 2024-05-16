#include "Sprite_2D.h"

#include "Debug.h"

Sprite_2D::Sprite_2D(const char* filePath, int maxFrames, Vector2d<int> spriteDimensions, SDL_Renderer* pRenderer)
	: m_Texture(filePath, maxFrames, spriteDimensions, pRenderer)
	, m_pRenderer(pRenderer)
	, m_flip(SDL_FLIP_NONE)
	, m_rotationPoint{ 0,0 }
	, m_rotationAngle(0)
{
	//
}

void Sprite_2D::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(m_Texture.GetSDLTexture(), red, green, blue);
}

void Sprite_2D::SetBlend(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(m_Texture.GetSDLTexture(), blending);
}

void Sprite_2D::SetAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(m_Texture.GetSDLTexture(), alpha);
}

void Sprite_2D::Flip(SDL_RendererFlip flip)
{
	m_flip = flip;
}

void Sprite_2D::Rotate(int degreeChange)
{
	m_rotationAngle += degreeChange;
}

void Sprite_2D::SetRotation(int degrees)
{
	m_rotationAngle = degrees;
}

void Sprite_2D::Render(Vector2d<int> actorPosition)
{
	m_Texture.RenderCurrentFrame(
		  actorPosition.x, actorPosition.y
		, m_pRenderer
		, m_rotationAngle
		, m_rotationPoint
		, m_flip
	);
}

void Sprite_2D::OnEnter()
{
	DEBUG_PRINT("Sprite added to renderer");
}

void Sprite_2D::OnExit()
{
	DEBUG_PRINT("Sprite removed from Renderer");
}
