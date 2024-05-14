#include "Texture.h"

#include "Debug.h"
#include "system\ConsoleManip.h"

Texture::Texture(const char* imageFilePath, int maxFrames, Vector2d<int> spriteDimensions, SDL_Renderer* pRenderer)
	: m_currentFrame(0)
	, m_maxFrameCount(maxFrames)
	, m_frameClipping{ 0,0,0,0 }
	, m_spriteHeight(spriteDimensions.y)
	, m_spriteWidth(spriteDimensions.x)
	, m_textureHeight(0)
	, m_textureWidth(0)
	, m_pTexture(nullptr)
{
	SDL_Surface* pSurface = SDL_LoadBMP(imageFilePath);

#if DEBUG
	std::cout << "reading in :  " << imageFilePath << '\n';
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

	m_frameClipping = SDL_Rect(0, 0, m_spriteWidth, m_spriteHeight);
	m_framesPerX = m_spriteWidth / m_textureWidth;
	m_framesPerY = m_spriteHeight / m_spriteHeight;
}

void Texture::SetFrame(unsigned int frameNumber)
{
	if (frameNumber > m_maxFrameCount)
		return;

	m_currentFrame = frameNumber;
	
	int frames = m_currentFrame - m_framesPerX;
	int frameY = 0;
	while (frames > 0)
	{
		frames -= m_framesPerX;
		++frameY;
	}
	 
	int frameX = frameNumber - (frameY * m_framesPerX); // the number of frames across on the X required to move
	
	int frameOriginX = frameX * m_spriteWidth;
	int frameOriginY = frameY * m_spriteHeight;

	m_frameClipping.x = frameOriginX;
	m_frameClipping.y = frameOriginY;
}

void Texture::ChangeFrame(int changeAmount)
{
	m_currentFrame += changeAmount;
	SetFrame(m_currentFrame);
}

void Texture::RenderCurrentFrame(
	  SDL_Renderer* pRenderer
	, double rotationAngle
	, SDL_Point rotationPoint
	, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(pRenderer, m_pTexture, &m_frameClipping, &m_frameClipping, rotationAngle, &rotationPoint, flip);
	//ChangeFrame(1);
}
