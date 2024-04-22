#pragma once

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
	BasicRenderer* m_pOwnerRenderer;
public:
	ExplodeOnCollide(Actor* pOwner);
	virtual void OnCollide() override;
};

// --------

class GiveTreasureCollide : public Component
{
	NEW_STATIC_ID;
	BasicRenderer* m_pOwnerRenderer;
public:
	GiveTreasureCollide(Actor* pOwner);
	virtual void OnCollide() override;
};

// --------

class TeleportCollide : public Component
{
	NEW_STATIC_ID;

	Vector2d<int> m_linkedPosition;
public:
	TeleportCollide(Actor* pOwner) : Component(pOwner, s_id) {}
	void Init(Vector2d<int> linkedPosition);
	virtual void OnCollide() override;

};