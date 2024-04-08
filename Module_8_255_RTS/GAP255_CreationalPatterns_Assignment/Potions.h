#pragma once

#include "IUseable.h"
#include "Random.h"

class Unit;

#ifdef OLD
	// Potion //

	class Potion : public IUseable
	{
		Unit* m_pUser;
		int m_heal;

	public:
		Potion(Unit* pUser, int amount);
		virtual ~Potion() = default;
		virtual void Use() override;
	};

	// Buff //

	class Buff : public IUseable
	{
		Unit* m_pUser;
		int m_attack;

	public:
		Buff(Unit* pUser, int amount);
		virtual ~Buff() = default;
		virtual void Use() override;
	};
#endif


enum class ConsumableType
{
	kHealthPotion,
	kAttackBuff,
};

class Consumable : public IUseable
{
	Unit* m_pUser;
	ConsumableType m_type;
	int m_amount;

public:
	Consumable(Unit* pUser, int amount, ConsumableType type);
	virtual void Use() override;
};

Consumable* CreateConsumable(Unit* user, ConsumableType type);


