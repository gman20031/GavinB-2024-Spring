#include "Actor.h"

#include <assert.h>

Actor::~Actor()
{
	if (m_pCollider) delete m_pCollider;
	if (m_pRenderer)delete m_pRenderer;
	for (auto& component : m_pComponentVector)
		if (component) delete component;
}

Component* Actor::AddComponent(Component* pNewComponent , id_t componentId)
{
	assert(pNewComponent != nullptr);
	m_pComponentVector.emplace_back(pNewComponent);
	m_ComponentMap.emplace(componentId, pNewComponent);
	return pNewComponent;
}

Component* Actor::AddComponent(id_t componentId)
{
	Component* pComponent = ComponentFactory::Create(componentId, this);
	return AddComponent(pComponent, componentId);
}

////////////////////////////////////////////////////////////
// Returns component attached to actor with matching id
// Returns nullptr if Id is not found
////////////////////////////////////////////////////////////
Component* Actor::GetComponent(id_t id)
{
	auto entry = m_ComponentMap.find(id);
	if (entry == m_ComponentMap.end()) return nullptr;
	return entry->second;
}


////////////////////////////////////////////////////////////
// Checks collider for any collisions
// for all components actor has, calls:
//	Update()
//	and OnCollide() for all collisions occured
////////////////////////////////////////////////////////////
void Actor::Update()
{
	// Update Components -> for every collison run on Collide.
	m_pCollider->Update();
	
	for (auto& component : m_pComponentVector)
	{
		component->Update();
		if (m_pCollidedActors.size() >= 1) 
			component->OnCollide();
	}
	m_pCollidedActors.clear();
}
