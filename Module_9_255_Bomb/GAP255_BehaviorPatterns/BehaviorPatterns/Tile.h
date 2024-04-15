// Tile.h
#pragma once

#include <initializer_list>

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
	Tile(AppearanceStrategy::Appearance appearanceType, BehaviorStrategy::Behavior behaviorType
		, const std::initializer_list<int>& behaviorInputs = {0,0});
	~Tile();

	Tile(const Tile& original, const std::initializer_list<int>& behaviorInputs = {0,0});


	void SetBehavior(Behavior behaviorType, const std::initializer_list<int>& behaviorInputs = {});
	void SetAppearance(Appearance appearanceType);


	Behavior GetBehaviorType() { return m_pBehavior->GetBehavior(); }
	Appearance GetAppearanceType() { return m_pAppearance->GetAppearance(); }
	Tile* Clone(const std::initializer_list<int>& behaviorInputs = {});

	void Draw() { m_pAppearance->Draw(); }
	void OnEnter([[maybe_unused]] Entity* pEntity);
};

// to add new tile
// Add tile you want to the TileFactory TileType Enum
// add the instance you want prototyped to the static tileMap in the factory
// Add any new behaviors to the enum of the behavior strategy
// add any new behaviors to the map of the behavior facroy
// add any new appearances to the enum of the appearance strategy
// add any new Appearances to the appearance factory
// Create the actual behavior

// eww