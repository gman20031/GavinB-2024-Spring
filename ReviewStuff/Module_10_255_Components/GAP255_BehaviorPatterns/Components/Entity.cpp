#include "Entity.h"

#include "World.h"

Entity::Entity(int x, int y, World* pWorld)
	: m_x(x)
	, m_y(y)
	, m_pWorld(pWorld)
{

}

void Entity::Damage(int amount)
{
	m_hitPoints -= amount;

	if (m_hitPoints < 0)
		m_hitPoints = 0;
}

