#include "Actor.h"

#include <assert.h>

Actor::Actor(id_t RendererID, id_t ColliderID)
	: m_pRenderer(ComponentFactory::Create(RendererID, this))
	, m_pCollider(ComponentFactory::Create(ColliderID, this))
	, m_position(0.f,0.f)
	, m_uniqueId(s_actorCount++)
{	
	// empty
}

Actor::Actor(const Actor& original)
	: m_position(original.m_position)
	, m_pWorld(original.m_pWorld)
	, m_pRenderer(original.m_pRenderer->Clone())
	, m_pCollider(original.m_pCollider->Clone())
	, m_uniqueId(s_actorCount++)
{
	for (Component* entry : original.m_pComponentVector)
		AddComponent(entry->m_id);
}

Actor::~Actor()
{
	if (m_pCollider) delete m_pCollider;
	if (m_pRenderer)delete m_pRenderer;
	for (auto& component : m_pComponentVector)
		if (component) delete component;
}

////////////////////////////////////////////////////////////
// adds ComponentPtr to the map and vector of actor
// returns the componentPtr if successful
////////////////////////////////////////////////////////////
Component* Actor::AddComponent(Component* pNewComponent , id_t componentId)
{
	assert(pNewComponent != nullptr);
	m_pComponentVector.emplace_back(pNewComponent);
	m_ComponentMap.emplace(componentId, pNewComponent);
	return pNewComponent;
}

////////////////////////////////////////////////////////////
// Uses the ComponentId to add a ComponentPtr to the Map
// and Vector attached to the actor
////////////////////////////////////////////////////////////
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

bool Actor::RemoveTag(const std::string& checkedTag)
{
	for (auto it = m_tags.begin(); it != m_tags.end(); ++it)
	{
		if (*it == checkedTag)
		{
			m_tags.erase(it);
			return true;
		}
	}
	return false;
}

bool Actor::HasTag(const std::string& checkedTag)
{
	for (auto& currentTag : m_tags)
	{
		if (currentTag == checkedTag)
			return true;
	}
	return false;
}

Actor* Actor::Clone()
{
	return new Actor(*this);
}

void Actor::Start(World* pWorld, Position_t startPosition)
{
	m_pWorld = pWorld;
	m_position = startPosition;
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


bool operator==(const Actor& lhs, const Actor& rhs)
{
	// seems the simplilest solution to, 
	// what if two of actors with all the same components, are standing on the same location
	// even with checking all the data of all the components for further information, it could still fail
	// this cannot fail, as it should be impossible for two actors to have the same id
	return (lhs.m_uniqueId == rhs.m_uniqueId);
}

