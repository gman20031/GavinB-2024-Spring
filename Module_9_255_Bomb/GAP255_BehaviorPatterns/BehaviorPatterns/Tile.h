// Tile.h
#pragma once

#include "AppearanceStrategies.h"
#include "BehaviorStrategies.h"

class Entity;

class Tile
{
	using Appearance = AppearanceStrategy::Appearance;
	using Behavior = BehaviorStrategy::Behavior;

	AppearanceStrategy* m_pAppearance = nullptr;
	BehaviorStrategy* m_pBehavior = nullptr;
public:
	Tile(AppearanceStrategy::Appearance apearanceType, BehaviorStrategy::Behavior behaviorType);
	~Tile();
	Tile(const Tile& original);

	void SetAppearance(Appearance appearanceType);
	void SetBehavior(Behavior behaviorType);
	Behavior GetBehaviorType() { return m_pBehavior->GetBehavior(); }
	Appearance GetAppearanceType() { return m_pAppearance->GetAppearance(); }
	Tile* Clone();

	void Draw() { m_pAppearance->Draw(); }
	void OnEnter([[maybe_unused]] Entity* pEntity);
};


