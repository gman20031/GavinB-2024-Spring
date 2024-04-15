#pragma once

#include <unordered_map>
#include <assert.h>
#include <initializer_list>

#include "Tile.h"

class TileFactory
{
public:
	enum class TileType
	{
		kEmpty,
		kBomb,
		kTreasure,
		kMimic,
		kExit,
		kTeleporter,
		kCount,
	} static;

private:
	using Appearance = FlyweightAppearanceFactory::Appearance;
	using Behavior = BehaviorFactory::Behavior;
	using TileMap = std::unordered_map< TileType, Tile >;

	static TileMap& GetTiles()
	{
		using enum TileType;
		static TileMap tiles
		{
			{ kEmpty,   {Appearance::kEmpty   ,	Behavior::kNothing}},
			{ kBomb,    {Appearance::kBomb    ,	Behavior::kExplosion}},
			{ kTreasure,{Appearance::kTreasure,	Behavior::kGiveTreasure}},
			{ kMimic,   {Appearance::kTreasure,	Behavior::kExplosion}},
			{ kExit,    {Appearance::kExit    ,	Behavior::kEndGame}},
			{ kTeleporter , {Appearance::KTeleporter , Behavior::kTeleport}},
		};
		return tiles;
	}

public:
	static Tile* Create(TileType type, std::initializer_list<int> behaviorInputs = {} )
	{
		auto it = GetTiles().find(type);
		if (it != GetTiles().end())
			return it->second.Clone(behaviorInputs);
		return nullptr;
	}
};

