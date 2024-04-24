#pragma once

#include "Component.h"

class BasicRenderer : public Component
{
public:
	using sprite_t = char;
	NEW_STATIC_ID;
private:
	sprite_t m_sprite = '\0';
public:
	BasicRenderer(Actor* pOwner) : Component(pOwner, s_id) {}
	BasicRenderer(const BasicRenderer& original, Actor* pOwner);
	virtual Component* Clone(Actor* pOwner) override;

	void SetColour(Color* newColor);
	bool ChangeSprite(sprite_t newSprite) { m_sprite = newSprite; return true; }
	virtual void Render() override;
};
