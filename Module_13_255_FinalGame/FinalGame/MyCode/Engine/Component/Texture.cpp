#include "Texture.h"
#include "../Debug.h"

void Texture::FillSDL_Texture(SDL_Renderer* pRenderer)
{
	SDL_Surface* pSurface = SDL_LoadBMP(m_imageFilePath.c_str());

#if DEBUG
	std::cout << "reading in :  " << m_imageFilePath << '\n';
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

Texture::Texture(const char* imageFilePath, int maxFrames, Vector2d<int> spriteDimensions, SDL_Renderer* pRenderer)
	: m_imageFilePath(imageFilePath)
	, m_maxFrameCount(maxFrames - 1)
	, m_spriteHeight(spriteDimensions.x)
	, m_spriteWidth(spriteDimensions.y)
{
	FillSDL_Texture(pRenderer);
	m_frameClipping = SDL_Rect(0, 0, m_spriteWidth, m_spriteHeight);
	m_framesPerX = m_textureWidth / m_spriteWidth;
	m_framesPerY = m_textureHeight / m_spriteHeight;
}

Texture::Texture(const std::unique_ptr<TextureSaveInfo>& info, SDL_Renderer* pRenderer)
	: m_imageFilePath(info->m_imageFilePath)
	, m_maxFrameCount(info->m_maxFrameCount)
	, m_spriteWidth(info->m_width)
	, m_spriteHeight(info->m_height)
	, m_currentFrame(info->m_currentFrame)
	, m_scaleModifier(info->m_scaleMod)
{
	FillSDL_Texture(pRenderer);
	m_frameClipping = SDL_Rect(0, 0, m_spriteWidth, m_spriteHeight);
	m_framesPerX = m_textureWidth / m_spriteWidth;
	m_framesPerY = m_textureHeight / m_spriteHeight;
}

Texture::~Texture()
{
	SDL_free(m_pTexture);
	DEBUG_PRINT("Deleting Texture" << m_imageFilePath);
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
	unsigned int targetFrame = m_currentFrame + changeAmount;

	if (targetFrame > m_maxFrameCount)
		targetFrame = 0;

	SetFrame(targetFrame);
}

TextureSaveInfo Texture::GetSaveInfo() const
{
	return {
		  m_imageFilePath
		, m_maxFrameCount
		, m_spriteWidth, m_spriteHeight
		, m_currentFrame
		, m_scaleModifier
	};
}

void Texture::RenderCurrentFrame(
	int x, int y,
	SDL_Renderer* pRenderer,
	double rotationAngle, SDL_Point rotationPoint,
	SDL_RendererFlip flip
) const
{
	SDL_Rect renderPosition{
		  x , y
		, int(m_spriteWidth * m_scaleModifier)
		, int(m_spriteHeight * m_scaleModifier)
	};

	SDL_RenderCopyEx(
		pRenderer
		, m_pTexture
		, &m_frameClipping
		, &renderPosition
		, rotationAngle
		, &(rotationPoint)
		, flip
	);
}
