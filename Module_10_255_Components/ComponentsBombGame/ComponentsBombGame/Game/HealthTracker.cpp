#include "HealthTracker.h"

#include "../Engine/Actor.h"
#include "World.h"

HealthTracker::HealthTracker(const HealthTracker& original, Actor* pOwner)
	: Component(pOwner, s_id)
	, m_health(original.m_health)
	, m_dead(original.m_dead)
{
}

void HealthTracker::Update()
{
	if (m_health <= 0)
		m_dead = true;
}

void HealthTracker::SetHealth(size_t newHealth)
{
	m_health = newHealth;
	Update();
}

void HealthTracker::ModifyHealth(size_t healthChange)
{
	m_health += healthChange;
	Update();
}

void  HealthTracker::Kill()
{
	m_health = 0;
	m_dead = true;
}

bool HealthTracker::IsDead() const
{
	return m_dead;
}
