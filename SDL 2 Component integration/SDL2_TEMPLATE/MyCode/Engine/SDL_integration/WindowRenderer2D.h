#pragma once

#include "..\..\System\Vector2d.h"
#include "..\BasicRenderer.h"
#include "SpriteSDL.h"

class Actor;

class WindowRenderer2D : public BasicRenderer
{
	NEW_STATIC_ID;
public:
	using Sprite_t = SpriteSDL;
	using Sprite_tPtr = std::shared_ptr<SpriteSDL>;
private:
	Sprite_tPtr m_pSprite;
	double m_rotation = 0 ;
	SDL_RendererFlip m_flip = SDL_FLIP_NONE; 

public:
	WindowRenderer2D(Actor* pOwner);
	WindowRenderer2D& Init(SDL_Renderer* pRenderer, const char* filePath);
	
	bool SetRotation(double theta) { m_rotation = theta; return true; }
	bool Flip(SDL_RendererFlip flip) { m_flip = flip; return true; }
	void SetSprite(const char* filePath);

	virtual void Render() override;
};