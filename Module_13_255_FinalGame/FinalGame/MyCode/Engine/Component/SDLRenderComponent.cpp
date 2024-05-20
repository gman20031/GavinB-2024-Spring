#include "SDLRenderComponent.h"

#include "../Actor/Actor.h"
#include "TextureFileIO.h"
#include "../SDL_Manager.h"
#include "../Debug.h"

SDLRenderComponent::SDLRenderComponent(Actor* pOwner)
	: Component(pOwner)
{
	//
}

void SDLRenderComponent::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(m_pTexture->GetSDLTexture(), red, green, blue);
}

void SDLRenderComponent::SetBlend(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(m_pTexture->GetSDLTexture(), blending);
}

void SDLRenderComponent::SetAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(m_pTexture->GetSDLTexture(), alpha);
}

void SDLRenderComponent::Rotate(int degreeChange)
{
	m_rotationAngle += degreeChange;
}

void SDLRenderComponent::SetRotation(int degrees)
{
	m_rotationAngle = degrees;
}

void SDLRenderComponent::Flip(SDL_RendererFlip flip)
{
	m_flip = flip;
}

void SDLRenderComponent::StartAnimation(uint32_t framesPerSecond, bool loop)
{
	if (framesPerSecond == 0)
		return;
	m_animating = true;
	m_callInfo.m_looping = loop;
	m_framesPerSecond = framesPerSecond;
	uint32_t ticksPerFrame = kTicksPerSecond / framesPerSecond ;
	m_callInfo.m_ppTexture = &m_pTexture;
	
#if DEBUG
	std::cout << "Starting Animation of texture: " << m_pTexture->GetImageFileName() << '\n';
	std::cout << framesPerSecond << " Frames Per Second , " << ticksPerFrame << " Ticks Per Frame\n";
#endif

	auto callback = [](uint32_t interval, void* param) -> uint32_t
		{
			auto pInfo = reinterpret_cast<callbackInfo*>(param); // static_Cast vs Reinterpret ??
			Texture_ptr& pTexture = *(pInfo->m_ppTexture);
			int currentFrame = pTexture->GetCurrentFrame();
			pTexture->ChangeFrame(1);
			if (pTexture->GetCurrentFrame() == 0 && (pInfo->m_looping == false))
			{
				pTexture->SetFrame(currentFrame); // reset the loop
				return 0;
			}
			return interval;
		};

	m_callbackId = SDL_AddTimer(ticksPerFrame, callback, &m_callInfo);
	if (m_callbackId == 0)
	{
		std::cout << "Failed to Add animation to timer: " << m_pTexture->GetImageFileName()  << '\n';
		std::cout << SDL_GetError() << '\n';
	}
}

void SDLRenderComponent::StopAnimation()
{
}

void SDLRenderComponent::SetFrame(int frameNumber)
{
	m_pTexture->SetFrame(frameNumber);
}

void SDLRenderComponent::SetTexture(Texture_ptr pTexture)
{
	m_pTexture.swap(pTexture);
}

void SDLRenderComponent::NewTexture(const std::string& textureIdentifer)
{
	Texture_ptr newTexture = TextureFileIO::Create(textureIdentifer, SDL_Manager::GetSDLRenderer());
	m_pTexture.swap(newTexture);
}

void SDLRenderComponent::ScaleTexture(unsigned int newScaleModifier)
{
	m_pTexture->SetScale(newScaleModifier);
}

void SDLRenderComponent::SetScaleMode(SDL_ScaleMode mode)
{
	m_pTexture->SetScaleMode(mode);
}

void SDLRenderComponent::Render()
{
	m_pTexture->RenderCurrentFrame({
		m_pOwner->GetPosition().x,
		m_pOwner->GetPosition().y,
		SDL_Manager::GetSDLRenderer(),
		m_rotationAngle,
		m_rotationPoint,
		m_flip
	}); 
}


