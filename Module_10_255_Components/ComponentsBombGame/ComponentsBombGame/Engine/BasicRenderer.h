#pragma once

#include "Component.h"

class BasicRenderer : public Component
{
	using sprite_t = char;
public:
	NEW_STATIC_ID;
	BasicRenderer(Actor* pOwner) : Component(pOwner, s_id) {}
	BasicRenderer(const BasicRenderer& original, Actor* pOwner);

private:
	sprite_t m_sprite = '\0';
public:
	bool ChangeSprite(sprite_t newSprite) { m_sprite = newSprite; return true; }
	virtual Component* Clone(Actor* pOwner) override;
	virtual void Render() override;
};
