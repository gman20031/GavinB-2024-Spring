#pragma once
#include <SDL.h>
#include <utility>

class Texture
{
	SDL_Texture* m_pTexture;
	int m_spriteWidth;
	int m_spriteHeight;
	int m_textureWidth;
	int m_textureHeight;
	uint16_t m_maxFrameCount;
	uint16_t m_framesPerX;
	uint16_t m_framesPerY;
	uint16_t m_currentFrame;
	SDL_Rect m_frameClipping;

public:
	Texture(const char* imageFilePath, int maxFrames, std::pair<int,int> spriteDimensions, SDL_Renderer* pRenderer);
	~Texture() { SDL_free(m_pTexture); }

	void SetFrame(unsigned int frameNumber);
	void ChangeFrame(int changeAmount);

	SDL_Texture* GetSDLTexture() { return m_pTexture; }
	void RenderCurrentFrame(int x, int y, SDL_Renderer* pRenderer, double rotationAngle, SDL_Point rotationPoint, SDL_RendererFlip flip);
};


/**
* -- Texture Saving --
*	FLIP ROtatePoint RotateVal
* 
*/