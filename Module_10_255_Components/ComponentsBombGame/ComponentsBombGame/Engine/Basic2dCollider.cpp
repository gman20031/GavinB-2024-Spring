#include "Basic2dCollider.h"

#include "Actor.h"
#include "../Game/World.h"

Basic2dCollider::Basic2dCollider(const Basic2dCollider& other)
	: Component(other.m_pOwner, s_id)
	, m_pCollidedActors(other.m_pCollidedActors)
{
	// empty
}

Basic2dCollider::Basic2dCollider(const Basic2dCollider& other, Actor* pOwner)
	: Component(m_pOwner, s_id)
	, m_pCollidedActors(other.m_pCollidedActors)
{
	// empty
}

Component* Basic2dCollider::Clone(Actor* pOwner)
{
	return new Basic2dCollider(*this, pOwner);
}

void Basic2dCollider::Init(std::vector<Actor*>* pCollidedActors)
{
	m_pCollidedActors = pCollidedActors;
}

void Basic2dCollider::Update()
{
	World* pWorld = m_pOwner->GetWorldPtr();
	for (Actor* enemy : pWorld->m_allActors)
	{
		if (*enemy == *m_pOwner) 
			continue;

		Actor::Position_t v1 = enemy->GetPosition();
		Actor::Position_t v2 = m_pOwner->GetPosition();
		if (v1.x == v2.x and v1.y == v2.y)
			m_pCollidedActors->emplace_back(enemy);
	}
}
