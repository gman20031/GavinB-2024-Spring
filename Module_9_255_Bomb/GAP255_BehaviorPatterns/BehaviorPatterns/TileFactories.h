#pragma once

#include <unordered_map>
#include <assert.h>

#include "Tile.h"
#include "AppearanceStrategies.h"
#include "BehaviorStrategies.h"


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
		kCount,
	} static;

private:
	using Appearance = AppearanceStrategy::Appearance;
	using Behavior = BehaviorStrategy::Behavior;
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
		};
		return tiles;
	}

public:
	static Tile* Create(TileType type)
	{
		auto it = GetTiles().find(type);
		if (it != GetTiles().end())
			return it->second.Clone();
		return nullptr;
	}
};

class BehaviorFactory
{
	using Behavior = BehaviorStrategy::Behavior;

public:

	static BehaviorStrategy* Create(Behavior type)
	{
		assert(type != Behavior::kCount);
		using enum Behavior;
		switch (type)
		{
		case kGiveTreasure:  return new GiveTreasure;
		case kExplosion: return new Explosion;
		case kNothing:   return new DoNothing;
		case kEndGame:   return new EndGame;
		default: return nullptr;
		}
	}
};

class FlyweightAppearanceFactory
{
	using Appearance = AppearanceStrategy::Appearance;
	using AppearanceMap = std::unordered_map< Appearance, AppearanceStrategy >;

	static AppearanceMap& GetMap()
	{
		using enum Appearance;
		static AppearanceMap AppearancesMap
		{
			{kEmpty		, AppearanceStrategy(kEmpty)},
			{kBomb		, AppearanceStrategy(kBomb)},
			{kUsedBomb	, AppearanceStrategy(kUsedBomb)},
			{kExit		, AppearanceStrategy(kExit)},
			{kTreasure  , AppearanceStrategy(kTreasure)},
		};
		return AppearancesMap;
	}

public:
	static AppearanceStrategy* Create(Appearance type)
	{
		auto it = GetMap().find(type);
		if (it != GetMap().end())
			return &(it->second);
		return nullptr;
	}
};