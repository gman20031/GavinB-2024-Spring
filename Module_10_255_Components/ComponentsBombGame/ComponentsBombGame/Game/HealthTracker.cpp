#include "HealthTracker.h"

#include "../Engine/Actor.h"
#include "World.h"

void HealthTracker::Update()
{
	if (m_health <= 0)
		m_dead = true;
}

void HealthTracker::ChangeHealth(size_t healthChange)
{
	m_health += healthChange;
}

bool HealthTracker::Kill()
{
	m_dead = true;
}

bool HealthTracker::IsDead() const
{
	return m_dead;
}
