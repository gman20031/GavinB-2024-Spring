#include "Sprite_2D.h"

#include "Debug.h"

void Sprite_2D::SetSpriteClip(int newSpriteSheetCount)
{
	int spriteCount = newSpriteSheetCount;


}

Sprite_2D::Sprite_2D(const char* filePath, Vector2d<int> spriteDimensions, SDL_Renderer* pRenderer)
	: m_pTexture(nullptr)
	, m_pRenderer(pRenderer)
	, m_spriteWidth(spriteDimensions.x)
	, m_spriteHeight(spriteDimensions.y)
	, m_textureWidth(0)
	, m_textureHeight(0)
	, m_spriteSheetCount(0)
	, m_flip(SDL_FLIP_NONE)
	, m_rotationPoint{0,0}
	, m_rotationAngle(0)
{
	SDL_Surface* pSurface = SDL_LoadBMP(filePath);

#if DEBUG
	std::cout << "reading in :  " << filePath << '\n';
	if (!pSurface)
	{
		std::cout << "surface not loaded!\n";
		ConsoleManip::Pause();
		return;
	}
#endif
	SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0, 0, 0));

	m_pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
	m_textureWidth = pSurface->w;
	m_textureHeight = pSurface->h;

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
	SDL_Rect renderQuad{ actorPosition.x , actorPosition.y , m_spriteWidth, m_spriteHeight };

	SDL_RenderCopyEx(m_pRenderer, m_pTexture, &m_spriteSheetClip, &renderQuad, m_rotationAngle, &m_rotationPoint, m_flip);
}

void Sprite_2D::OnEnter()
{
	DEBUG_PRINT("Sprite added to renderer");
}

void Sprite_2D::OnExit()
{
	DEBUG_PRINT("Sprite removed from Renderer");
}
