#pragma once
#include "../System/ConsoleManip.h"

#include "Component.h"

class BasicRenderer : public Component
{
public:
	using sprite_t = char;
	ID_FROM_NAME("BasicRenderer");
private:
	const char* m_formatting = TEXT_DEF;
	sprite_t m_sprite = '\0';
public:
	BasicRenderer(Actor* pOwner) : Component(pOwner) {}
	BasicRenderer(const BasicRenderer& original, Actor* pOwner);

	void SetFormatting(const char* newFormatting) { m_formatting = newFormatting; }
	bool ChangeSprite(sprite_t newSprite) { m_sprite = newSprite; return true; }
	virtual void Render() override;
};
