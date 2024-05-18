#pragma once
#include <SDL.h>
#include <memory>

template<class T>
struct Vector2d
{
	T x;
	T y;
};

/**
 * @brief ImageFilePath
 * @brief number of frames
 * @brief width, height
 * @brief currentFrame
 * @brief Scale Mod
 */
struct TextureSaveInfo
{
	const char* m_imageFilePath = nullptr;
	unsigned int m_maxFrameCount = 0;
	unsigned int m_width = 0;
	unsigned int m_height = 0;
	unsigned int m_currentFrame = 0;
	unsigned int m_scaleMod = 1;
};
static constexpr size_t kTextureSaveInfoLines = 6;

/**
 * @brief x
 * @brief y
 * @brief pRenderer
 * @brief rotationAngle
 * @brief rotationPoint
 * @brief flip
*/
struct TextureRenderInfo
{
	int x;
	int y;
	SDL_Renderer* pRenderer;
	double rotationAngle;
	SDL_Point rotationPoint;
	SDL_RendererFlip flip;
};

/**
 * @brief SDL_Texture wrapper Class containing info and methods for animation
*/
class Texture
{
	const char* m_imageFilePath = nullptr;
	SDL_Texture* m_pTexture = nullptr;
	unsigned int m_spriteWidth = 0;
	unsigned int m_spriteHeight = 0;
	unsigned int m_textureWidth = 0;
	unsigned int m_textureHeight = 0;
	unsigned int m_maxFrameCount = 0;
	unsigned int m_framesPerX = 0;
	unsigned int m_framesPerY = 0;
	unsigned int m_currentFrame = 0;
	unsigned int m_scaleModifier = 1;
	SDL_Rect m_frameClipping{ 0,0,0,0 };

private:
	void FillSDL_Texture(SDL_Renderer* pRenderer);
public:
	Texture(const char* imageFilePath, int maxFrames, Vector2d<int> spriteDimensions, SDL_Renderer* pRenderer);
	Texture(std::unique_ptr<TextureSaveInfo>& info, SDL_Renderer* pRenderer);
	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;

	void SetFrame(unsigned int frameNumber);
	void ChangeFrame(int changeAmount);
	SDL_Texture* GetSDLTexture() { return m_pTexture; }

	const char* GetImageFileName() const { return m_imageFilePath; }
	TextureSaveInfo GetSaveInfo() const;

	void RenderCurrentFrame(const TextureRenderInfo& info) const;
};


