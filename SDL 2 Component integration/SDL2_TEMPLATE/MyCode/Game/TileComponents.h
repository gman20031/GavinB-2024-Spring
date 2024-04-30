#pragma once

#include "../Engine/SDL_integration/WindowRenderer2D.h"
#include "../Engine/ComponentFactory.h"
#include "../Engine/BasicRenderer.h"
#include "../System/Vector2d.h"

class EndGameOnCollide : public Component
{
	NEW_STATIC_ID;
public:
	EndGameOnCollide(Actor* pOwner) : Component(pOwner, s_id) {}
	virtual void OnCollide() override;
};

// --------

class ExplodeOnCollide : public Component
{
	NEW_STATIC_ID;
private:
	inline static constexpr std::pair<int, int> s_damageRange{ 3,6 };
	bool m_exploded = false;
	WindowRenderer2D* m_pOwnerRenderer;
public:
	bool Exploded() const { return m_exploded; }
	ExplodeOnCollide(Actor* pOwner);
	virtual void OnCollide() override;
};

// --------

class GiveTreasureCollide : public Component
{
	NEW_STATIC_ID;
	static constexpr std::pair<int, int> s_treasureRange{ 50,150 };
	WindowRenderer2D* m_pOwnerRenderer;
	bool m_used = false;
public:
	GiveTreasureCollide(Actor* pOwner);
	virtual void OnCollide() override;
};

// --------

///////////////////////////////////////////////////////////////
// Requires Init of linked position
///////////////////////////////////////////////////////////////
class TeleportCollide : public Component
{
	NEW_STATIC_ID;
	Vector2d<int> m_linkedPosition;
public:
	TeleportCollide(Actor* pOwner) : Component(pOwner, s_id) , m_linkedPosition(0,0) {}
	void Init(Vector2d<int> linkedPosition);
	virtual void OnCollide() override;

};