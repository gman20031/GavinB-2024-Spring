#pragma once

#include <utility>

class Tile;
class World;
class Entity;

class BehaviorStrategy
{
public:

protected:
	Tile* m_pOwner = nullptr;
	World* m_pWorld = nullptr;
	const int m_behaviorType;
	using Behavior = int;
public:
	constexpr BehaviorStrategy(Behavior behaviorType) : m_behaviorType(behaviorType) {}
	virtual ~BehaviorStrategy() = default;

	Behavior GetBehaviorType() const { return m_behaviorType; }
	void GiveOwner(Tile* pOwner);

	virtual Behavior OnEnter([[maybe_unused]] Entity* pEntity) = 0;
};

class DoNothing : public BehaviorStrategy
{
public:
	constexpr DoNothing() : BehaviorStrategy(0) {}

	virtual Behavior OnEnter([[maybe_unused]] Entity* pEntity) override { return 0; }
};

class Explosion : public BehaviorStrategy
{
	using DamageRange = std::pair<int, int>;
	inline static constexpr DamageRange s_damageRange{ 3,6 };

public:
	constexpr Explosion() : BehaviorStrategy(1) {}

	virtual Behavior OnEnter([[maybe_unused]] Entity* pEntity) override;
};

class GiveTreasure : public BehaviorStrategy
{
	static constexpr std::pair<int, int> s_treasureRange{ 50,150 };
public:
	constexpr GiveTreasure() : BehaviorStrategy(2) {}

	virtual Behavior OnEnter([[maybe_unused]] Entity* pEntity) override;
};

class EndGame : public BehaviorStrategy
{
public:
	constexpr EndGame() : BehaviorStrategy(3) {}

	virtual Behavior OnEnter([[maybe_unused]] Entity* pEntity) override;
};

class Teleport : public BehaviorStrategy
{
	int m_linkedTileX = 0;
	int m_linkedTileY = 0;

public:
	constexpr Teleport(std::initializer_list<int> behaviorInputs)
		: BehaviorStrategy(4)
	{
		auto it = behaviorInputs.begin();
		m_linkedTileX = *it;
		m_linkedTileY = *(it + 1);
	}

	virtual Behavior OnEnter([[maybe_unused]] Entity* pEntity) override;
};


class NewBehavior : public BehaviorStrategy
{
	int random;

public:
	constexpr NewBehavior() : BehaviorStrategy(5) { random = 5; }

	virtual Behavior OnEnter([[maybe_unused]] Entity* pEntity) override;
};