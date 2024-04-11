#pragma once

#include <utility>

class Tile;
class World;
class Entity;

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
	} static;
protected:
	Tile* m_pOwner = nullptr;
	World* m_pWorld = nullptr;
	const Behavior m_behaviorType;
public:
	BehaviorStrategy(Behavior behaviorType) : m_behaviorType(behaviorType) {}
	virtual ~BehaviorStrategy() = default;

	Behavior GetBehavior() const { return m_behaviorType; }
	void GiveOwner(Tile* pOwner);

	virtual Behavior OnEnter([[maybe_unused]] Entity* pEntity) = 0;
};

class DoNothing : public BehaviorStrategy
{
public:
	DoNothing() : BehaviorStrategy(Behavior::kNothing) {}

	virtual Behavior OnEnter([[maybe_unused]] Entity* pEntity) override { return Behavior::kNothing; }
};

class Explosion : public BehaviorStrategy
{
	using DamageRange = std::pair<int, int>;
	inline static constexpr DamageRange s_damageRange{ 3,6 };

public:
	Explosion() : BehaviorStrategy(Behavior::kExplosion) {}
	virtual Behavior OnEnter([[maybe_unused]] Entity* pEntity) override;
};

class GiveTreasure : public BehaviorStrategy
{
	static constexpr std::pair<int, int> s_treasureRange{ 50,150 };
public:
	GiveTreasure() : BehaviorStrategy(Behavior::kGiveTreasure) {}

	virtual Behavior OnEnter([[maybe_unused]] Entity* pEntity) override;
};

class EndGame : public BehaviorStrategy
{
public:
	EndGame() : BehaviorStrategy(Behavior::kEndGame) {}

	virtual Behavior OnEnter([[maybe_unused]] Entity* pEntity) override;
};

