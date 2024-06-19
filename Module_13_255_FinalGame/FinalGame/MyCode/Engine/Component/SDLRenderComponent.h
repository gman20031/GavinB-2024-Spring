#pragma once

#include <SDL.h>

#include "Component.h"
#include "../System/Vector2d.h"
#include "../System/ConsoleManip.h"
#include "Texture.h"

class SDLRenderComponent : public Component
{
public:
	using Texture_ptr = std::unique_ptr<Texture>;
	ID_FROM_NAME("SDLRenderComponent");
private:
	Texture_ptr m_pTexture;

	double m_rotationAngle = 0;
	SDL_Point m_rotationPoint = { 0,0 };
	double m_scaleModifier = 1;
	SDL_RendererFlip m_flip = SDL_FLIP_NONE;

	struct callbackInfo
	{
		bool m_looping;
		const Texture_ptr* m_ppTexture;
	};
	callbackInfo m_callInfo { false, nullptr };
	bool m_animating = false;
	uint32_t m_callbackId = 0;
	uint32_t m_framesPerSecond = 0;

private: // methods

public:
	SDLRenderComponent(Actor* pOwner);

	void Rotate(int degreeChange);
	void SetRotation(int degrees);
	void Flip(SDL_RendererFlip flip);

	bool IsAnimating() const { return m_animating; }
	void StartAnimation(uint32_t framesPerSecond = 0, bool loop = false);
	void StopAnimation();
	void SetFrame(int frameNumber);

	void SetTexture(Texture_ptr pTexture);
	void NewTexture(const std::string& textureIdentifer);

	void ScaleTexture(double newScaleModifier);

	// Changes the underlying SDL texture
	//void SetScaleMode(SDL_ScaleMode mode);
	//void SetColor(Uint8 red, Uint8 green, Uint8 blue);
	//void SetBlend(SDL_BlendMode blending);
	//void SetAlpha(Uint8 alpha);

	const Texture_ptr& GetTexture() const { return m_pTexture; }

	virtual void Render() override;
};

