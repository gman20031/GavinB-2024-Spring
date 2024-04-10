// Tile.h
#pragma once

#include "AppearanceStrategies.h"
#include "BehaviorStrategies.h"

class Player;



class Tile
{
	AppearanceStrategy* m_pAppearance;
	BehaviorStrategy* m_pBehavior;

public:
	Tile(AppearanceStrategy::Appearance apearanceType, BehaviorStrategy::Behavior behaviorType);
	void SetAppearance(AppearanceStrategy::Appearance apearanceType);
	void SetBehavior(BehaviorStrategy::Behavior behaviorType);
	Tile* Clone();

	void Draw() { m_pAppearance->Draw(); }
	void OnEnter([[maybe_unused]] Player* pPlayer) { m_pBehavior->OnEnter(pPlayer); }
};


