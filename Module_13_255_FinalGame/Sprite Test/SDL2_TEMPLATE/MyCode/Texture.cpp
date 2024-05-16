#include "Texture.h"

Texture::Texture(const char* imageFilePath, int maxFrames, std::pair<int,int> spriteDimensions, SDL_Renderer* pRenderer)
	: m_currentFrame(0)
	, m_maxFrameCount(maxFrames - 1)
	, m_frameClipping{ 0,0,0,0 }
	, m_spriteHeight(spriteDimensions.second)
	, m_spriteWidth(spriteDimensions.first)
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
	m_framesPerX = m_textureWidth / m_spriteWidth ;
	m_framesPerY = m_textureHeight / m_spriteHeight;
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
	int targetFrame = m_currentFrame + changeAmount;

	if (targetFrame > m_maxFrameCount)
		targetFrame = 0;

	SetFrame(targetFrame);
}

void Texture::RenderCurrentFrame(
	int x, int y
	, SDL_Renderer* pRenderer
	, double rotationAngle
	, SDL_Point rotationPoint
	, SDL_RendererFlip flip)
{
	SDL_Rect renderPosition{ x,y,m_spriteWidth * 4,m_spriteHeight * 4};
	SDL_RenderCopyEx(pRenderer, m_pTexture, &m_frameClipping, &renderPosition, rotationAngle, &rotationPoint, flip);
	//ChangeFrame(1);
}
