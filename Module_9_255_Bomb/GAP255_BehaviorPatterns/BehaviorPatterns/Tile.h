// Tile.h
#pragma once

#include <initializer_list>

#include "StrategyFactories.h"

class Entity;

class Tile
{
	using AppearanceType = FlyweightAppearanceFactory::Appearance;
	using BehaviorType = BehaviorFactory::Behavior;

	AppearanceStrategy* m_pAppearance = nullptr;
	BehaviorStrategy* m_pBehavior = nullptr;
public:
	Tile(AppearanceType appearanceType, BehaviorType behaviorType
		, const std::initializer_list<int>& behaviorInputs = {0,0});
	~Tile();

	Tile(const Tile& original, const std::initializer_list<int>& behaviorInputs = {0,0});


	void SetBehavior(BehaviorType, const std::initializer_list<int>& behaviorInputs = {});
	void SetAppearance(AppearanceType appearanceType);


	BehaviorType GetBehaviorType() { return (BehaviorType)m_pBehavior->GetBehaviorType(); }
	AppearanceType GetAppearanceType() { return (AppearanceType)m_pAppearance->GetAppearanceType(); }
	Tile* Clone(const std::initializer_list<int>& behaviorInputs = {});

	void Draw() { m_pAppearance->Draw(); }
	void OnEnter([[maybe_unused]] Entity* pEntity);
};

class NewTile
{


};

// to add new tile
// Add tile you want to the TileFactory TileType Enum
// add the instance you want prototyped to the static tileMap in the factory
// Add any new behaviors to the enum of the behavior strategy
// add any new behaviors to the map of the behavior facroy
// add any new appearances to the enum of the appearance strategy
// add any new Appearances to the appearance factory
// Create the actual behavior

// What I want

// Create behavior
// Add behavior to enum on factory

// Create Appearance
// add Appearnce to enum on factory

// Create Tile
// Create Tile prototype in Tile Factory
// Add Tile to Tile Enum

// eww