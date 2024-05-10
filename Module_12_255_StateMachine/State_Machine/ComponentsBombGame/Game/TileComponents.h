#pragma once

#include "../Engine/ComponentFactory.h"
#include "../Engine/BasicRenderer.h"
#include "../System/Vector2d.h"

class EndGameOnCollide : public Component
{
	ID_FROM_NAME("EndGameOnCollide");
public:
	EndGameOnCollide(Actor* pOwner) : Component(pOwner) {}
	virtual void OnCollide() override;
};

// --------

class ExplodeOnCollide : public Component
{
	ID_FROM_NAME("ExplodeOnCollide");
private:
	inline static constexpr std::pair<int, int> s_damageRange{ 3,6 };
	bool m_exploded = false;
	BasicRenderer* m_pOwnerRenderer;
public:
	ExplodeOnCollide(Actor* pOwner);

	bool Exploded() const { return m_exploded; }
	virtual void OnCollide() override;
};

// --------

class GiveTreasureCollide : public Component
{
	ID_FROM_NAME("GiveTreasureCollide");
	static constexpr std::pair<int, int> s_treasureRange{ 50,150 };
	BasicRenderer* m_pOwnerRenderer;
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
	ID_FROM_NAME("TeleportCollide");
	Vector2d<int> m_linkedPosition;
public:
	TeleportCollide(Actor* pOwner) : Component(pOwner) , m_linkedPosition(0,0) {}
	void Init(Vector2d<int> linkedPosition);
	virtual void OnCollide() override;

};