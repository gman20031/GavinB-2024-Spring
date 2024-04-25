#include "Basic2dCollider.h"

#include "Actor.h"
#include "../Game/World.h"

Basic2dCollider::Basic2dCollider(Actor* pOwner)
	: Component(pOwner, s_id)
{
}

Basic2dCollider::Basic2dCollider(const Basic2dCollider& other)
	: Component(other.m_pOwner, s_id)
{
	// empty
}

Component* Basic2dCollider::Clone(Actor* pOwner)
{
	return new Basic2dCollider(pOwner);
}

void Basic2dCollider::Update()
{
	std::vector<Actor*>* CollidedActors = &m_pOwner->m_pCollidedActors;
	World* pWorld = m_pOwner->GetWorldPtr();
	Actor::Position_t ownerPos = m_pOwner->GetPosition();

	for (Actor* actor : pWorld->m_allActors)
	{
		if (*actor == *m_pOwner) 
			continue;

		Actor::Position_t otherPos = actor->GetPosition();
		if (otherPos.x == ownerPos.x and otherPos.y == ownerPos.y)
			CollidedActors->emplace_back(actor);
	}
}
