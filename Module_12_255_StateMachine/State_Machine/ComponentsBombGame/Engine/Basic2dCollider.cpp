#include "Basic2dCollider.h"

#include "Actor.h"
#include "../Game/World.h"

Basic2dCollider::Basic2dCollider(Actor* pOwner)
	: Component(pOwner)
{
	// empty
}

Basic2dCollider::Basic2dCollider(const Basic2dCollider& other)
	: Component(other.m_pOwner)
{
	// empty
}

void Basic2dCollider::Update()
{
	World* pWorld = m_pOwner->GetWorldPtr();
	Actor::Position_t ownerPos = m_pOwner->GetPosition();

	for (Actor* actor : pWorld->GetEntityVector() )
	{
		if (*actor == *m_pOwner) 
			continue;

		Actor::Position_t otherPos = actor->GetPosition();
		if (otherPos.x == ownerPos.x and otherPos.y == ownerPos.y)
			m_pCollidedActors.emplace_back(actor);
	}
	if (!m_pCollidedActors.empty())
		m_pOwner->Collide();
	m_pCollidedActors.clear();
}