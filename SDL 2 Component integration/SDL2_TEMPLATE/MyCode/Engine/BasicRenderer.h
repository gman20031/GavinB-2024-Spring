#pragma once

#include <type_traits>
#include "Component.h"

class BasicRenderer : public Component
{
public:
		//; // all Renderers have the same ID... this will backfire.. it did
private:

public:
	BasicRenderer(Actor* pOwner  , IdType id) : Component(pOwner, id) {}

	virtual void Render() override = 0;
};

// Concept equal to std::derived_from<T, BasicRenderer>
template<typename T>
concept SubRenderer = std::derived_from<T, BasicRenderer>;


#include "../System/ConsoleManip.h"
class ConsoleRenderer final : public BasicRenderer
{
	NEW_STATIC_ID;
public:
	using sprite_t = char;
private:
	const char* m_formatting = TEXT_DEF;
	sprite_t m_sprite = '\0';
public:
	ConsoleRenderer(Actor* pOwner) : BasicRenderer(pOwner , s_id) {}

	void SetFormatting(const char* newFormatting) { m_formatting = newFormatting; }
	bool ChangeSprite(sprite_t newSprite) { m_sprite = newSprite; return true; }

	virtual void Render() override final;
};
