#pragma once

#include <assert.h>
#include <unordered_map>

#include "BehaviorStrategies.h"
#include "AppearanceStrategies.h"

class BehaviorFactory
{
public:
	enum class Behavior
	{
		kNothing,
		kExplosion,
		kGiveTreasure,
		kEndGame,
		kTeleport,

		kCount,
	} static;

	static BehaviorStrategy* Create(Behavior type, const std::initializer_list<int>& behaviorInputs = {})
	{
		assert(type != Behavior::kCount);
		using enum Behavior;
		switch (type)
		{
		case kGiveTreasure:  return new GiveTreasure;
		case kExplosion: return new Explosion;
		case kNothing:   return new DoNothing;
		case kEndGame:   return new EndGame;
		case kTeleport:  return new Teleport(behaviorInputs);
		default: return nullptr;
		}
	}
};

class FlyweightAppearanceFactory
{
public:
	enum class Appearance
	{
		kEmpty = '.',
		kBomb = '*',
		kUsedBomb = '#',
		kExit = 'H',
		kTreasure = '$',
		KTeleporter = '&',
	} static;
private:
	using AppearanceMap = std::unordered_map< Appearance, AppearanceStrategy >;

	static AppearanceMap& GetMap()
	{
		using enum Appearance;
		static AppearanceMap AppearancesMap
		{
			{kEmpty		, AppearanceStrategy((char)kEmpty)},
			{kBomb		, AppearanceStrategy((char)kBomb)},
			{kUsedBomb	, AppearanceStrategy((char)kUsedBomb)},
			{kExit		, AppearanceStrategy((char)kExit)},
			{kTreasure  , AppearanceStrategy((char)kTreasure)},
			{KTeleporter, AppearanceStrategy((char)KTeleporter)},
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