#pragma once
#include <random>

#include "Player.h"

class BehaviorStrategy
{
public:
	enum class Behavior
	{
		kNothing,
		kExplosion,
		kGiveTreasure,
		kEndGame,

		kCount,
	} static ;

	virtual ~BehaviorStrategy() = default;

	virtual void OnEnter([[maybe_unused]] Player* pPlayer) = 0;
};

class DoNothing : public BehaviorStrategy
{
public:
	virtual void OnEnter([[maybe_unused]] Player* pPlayer) override {}
};

class Explosion : public BehaviorStrategy
{
	using DamageRange = std::pair<int, int>;
	inline static constexpr DamageRange s_damageRange{ 3,6 };

public:
	Explosion() {}
	virtual void OnEnter([[maybe_unused]] Player* pPlayer) override;
};

class GiveTreasure : public BehaviorStrategy
{
	static constexpr std::pair<int, int> s_treasureRange{ 50,150 };
public:
	virtual void OnEnter([[maybe_unused]] Player* pPlayer) override;
};

class EndGame : public BehaviorStrategy
{
public:
	virtual void OnEnter([[maybe_unused]] Player* pPlayer) override;
};

