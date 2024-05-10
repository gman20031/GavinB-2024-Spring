#include "HealthTracker.h"

#include "../Engine/Actor.h"
#include "World.h"

HealthTracker::HealthTracker(const HealthTracker& original, Actor* pOwner)
	: Component(pOwner)
	, m_health(original.m_health)
	, m_dead(original.m_dead)
{
}

void HealthTracker::Update()
{
	if (m_health <= 0)
		m_dead = true;
}

void HealthTracker::SetHealth(int newHealth)
{
	m_health = newHealth;
	Update();
}

void HealthTracker::ModifyHealth(int healthChange)
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
