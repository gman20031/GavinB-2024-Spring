#pragma once


#include "Component.h"

class BasicRenderer : public Component
{
public:
	NEW_STATIC_ID;
private:

public:
	BasicRenderer(Actor* pOwner , Component::IdType sId) : Component(pOwner, sId) {}

	virtual void Render() override = 0;
};


#include "../System/ConsoleManip.h"
class ConsoleRenderer final : public BasicRenderer
{
public:
	using sprite_t = char;
	NEW_STATIC_ID;
private:
	const char* m_formatting = TEXT_DEF;
	sprite_t m_sprite = '\0';
public:
	ConsoleRenderer(Actor* pOwner) : BasicRenderer(pOwner , s_id) {}

	void SetFormatting(const char* newFormatting) { m_formatting = newFormatting; }
	bool ChangeSprite(sprite_t newSprite) { m_sprite = newSprite; return true; }

	virtual void Render() override final;
};
