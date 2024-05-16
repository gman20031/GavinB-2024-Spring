#pragma once
#include <SDL.h>
#include "System/Vector2d.h"

class Texture
{
	SDL_Texture* m_pTexture  = nullptr;
	int m_spriteWidth		 = 0;
	int m_spriteHeight		 = 0;
	int m_textureWidth		 = 0;
	int m_textureHeight		 = 0;
	uint16_t m_maxFrameCount = 0;
	uint16_t m_framesPerX	 = 0;
	uint16_t m_framesPerY	 = 0; 
	uint16_t m_currentFrame	 = 0;
	uint16_t m_scaleModifier = 1;
	SDL_Rect m_frameClipping { 0,0,0,0 };

public:
	Texture(const char* imageFilePath, int maxFrames, Vector2d<int> spriteDimensions, SDL_Renderer* pRenderer);
	~Texture() { SDL_free(m_pTexture); }
	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;

	void SetFrame(unsigned int frameNumber);
	void ChangeFrame(int changeAmount);
	SDL_Texture* GetSDLTexture() { return m_pTexture; }

	void Save(const char* filePath);
	void Load(const char* filePath);

	void RenderCurrentFrame(int x, int y, SDL_Renderer* pRenderer, double rotationAngle, SDL_Point rotationPoint, SDL_RendererFlip flip);
};


/**
* -- Texture Saving --
* ImageFilePath
* number of frames
* width, height
* currentFrame
* Scale Mod
*/