#include "Trigger.h"
#include "Game.h"

Trigger::Trigger(size_t x, size_t y, char appearance, Effect effect)
	: m_position{x,y}
	, m_appearance(appearance)
	, m_effect(effect)
{
	//
}

void Trigger::SetEffect(Effect newEffect)
{
	m_effect = newEffect;
}

void Trigger::OnStep(Player* pPlayer) const
{
	m_effect(pPlayer);
}
