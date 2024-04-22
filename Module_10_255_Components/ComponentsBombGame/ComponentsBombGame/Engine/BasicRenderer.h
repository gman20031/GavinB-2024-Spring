#pragma once

#include "Component.h"

class BasicRenderer : public Component
{
	using sprite_t = char;
public:
	NEW_STATIC_ID;
	BasicRenderer(Actor* pOwner) : Component(pOwner, s_id) {}
private:
	sprite_t m_sprite = '\0';
public:
	bool Init(sprite_t newSprite) { m_sprite = newSprite; return true; }
	virtual Component* Clone() override;
	virtual void Render() override;
};
