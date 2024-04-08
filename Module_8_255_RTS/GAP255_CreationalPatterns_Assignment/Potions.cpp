#include "Potions.h"
#include "Unit.h"

#ifdef OLD
// Potion //

Potion::Potion(Unit* pUser, int amount)
    : m_pUser{ pUser }
    , m_heal{ amount }
{
}

void Potion::Use()
{
    m_pUser->ModifyHealth(m_heal);
}

// Buff //

Buff::Buff(Unit* pUser, int amount)
    : m_pUser{ pUser }
    , m_attack{ amount }
{
}

void Buff::Use()
{
    m_pUser->ModifyAttack(m_attack);
}
#endif


Consumable::Consumable(Unit* pUser, int amount, ConsumableType type)
	: m_pUser(pUser)
	, m_amount(amount)
	, m_type(type)
{
}

void Consumable::Use()
{
	using enum ConsumableType;
	switch(m_type)
	{
	case kHealthPotion: m_pUser->ModifyHealth(m_amount); break;
	case kAttackBuff:m_pUser->ModifyAttack(m_amount); break;
	}
}

Consumable* CreateConsumable(Unit* user, ConsumableType type)
{
	return new Consumable(user, Random::GetRandomInRange(1, 3), type);
}
