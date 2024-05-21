#pragma once
#include <SDL.h>
#include <memory>
#include <string>

#include "../System/Vector2d.h"

/**
 *  @brief std::string m_imageFilePath;
 * 	@brief unsigned int m_maxFrameCount = 0;
 * 	@brief unsigned int m_width = 0;
 * 	@brief unsigned int m_height = 0;
 * 	@brief unsigned int m_currentFrame = 0;
 * 	@brief unsigned int m_scaleMod = 1;
 */
struct TextureSaveInfo
{
	std::string m_imageFilePath;
	unsigned int m_maxFrameCount = 0;
	unsigned int m_width = 0;
	unsigned int m_height = 0;
	unsigned int m_currentFrame = 0;
	unsigned int m_scaleMod = 1;
	SDL_ScaleMode m_scaleMode = SDL_ScaleModeBest;
};
static constexpr size_t kTextureSaveInfoLines = 7;

/**
 * @brief int x
 * @brief int y
 * @brief SDL_Renderer* pRenderer
 * @brief double rotationAngle
 * @brief SDL_Point rotationPoint
 * @brief SDL_RendererFlip flip
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
	std::string m_imageFilePath = nullptr;
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
	SDL_ScaleMode m_scaleMode = SDL_ScaleModeLinear;
	SDL_Rect m_frameClipping{ 0,0,0,0 };

private:
	void FillSDL_Texture(SDL_Renderer* pRenderer);
public:
	Texture(const char* imageFilePath, int maxFrames, Vector2d<int> spriteDimensions, SDL_Renderer* pRenderer);
	Texture(const std::unique_ptr<TextureSaveInfo>& info, SDL_Renderer* pRenderer);
	~Texture();
	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;


	void SetFrame(unsigned int frameNumber);
	void ChangeFrame(int changeAmount);

	SDL_Texture* GetSDLTexture() { return m_pTexture; }

	const std::string& GetImageFileName() const { return m_imageFilePath; }
	TextureSaveInfo GetSaveInfo() const;
	unsigned int GetCurrentFrame() const { return m_currentFrame; }
	void SetScale(unsigned int scaleMod) { m_scaleModifier = scaleMod; }
	void SetScaleMode(SDL_ScaleMode mode) { m_scaleMode = mode; }

	/**
	 * @brief int x
	 * @brief int y
	 * @brief SDL_Renderer* pRenderer
	 * @brief double rotationAngle
	 * @brief SDL_Point rotationPoint
	 * @brief SDL_RendererFlip flip
	*/
	void RenderCurrentFrame(const TextureRenderInfo& info) const;
};