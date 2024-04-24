#include "Actor.h"

#include <assert.h>

Actor::Actor(id_t RendererID, id_t ColliderID)
	: m_pRenderer(ComponentFactory::Create(RendererID, this))
	, m_pCollider(ComponentFactory::Create(ColliderID, this))
	, m_position(0,0)
	, m_uniqueId(s_actorCount++)
	, m_pWorld(nullptr)
{	
	// AddComponent(m_pRenderer, RendererID);
	// AddComponent(m_pCollider, ColliderID);
	m_ComponentMap.emplace(RendererID, m_pRenderer);
	m_ComponentMap.emplace(ColliderID, m_pCollider);

}

Actor::Actor(const Actor& original)
	: m_position(original.m_position)
	, m_pWorld(original.m_pWorld)
	, m_pRenderer(original.m_pRenderer->Clone(this))
	, m_pCollider(original.m_pCollider->Clone(this))
	, m_uniqueId(s_actorCount++)
{
	// AddComponent(m_pRenderer, m_pRenderer->m_id);
	// AddComponent(m_pCollider, m_pCollider->m_id);
	m_ComponentMap.emplace(m_pRenderer->m_id, m_pRenderer);
	m_ComponentMap.emplace(m_pCollider->m_id, m_pCollider);
	for (Component* entry : original.m_pComponentVector)
		AddComponent(entry->m_id);
}

Actor::~Actor()
{
	if (m_pCollider) delete m_pCollider;
	if (m_pRenderer) delete m_pRenderer;
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

void Actor::RemoveComponent(id_t id)
{
	m_pRemovedComponents.emplace_back(id);
}

void Actor::DeleteRemovedComponents()
{
	for(id_t removedID : m_pRemovedComponents)
	{
		m_ComponentMap.erase(removedID);
		for (auto it = m_pComponentVector.begin(); it != m_pComponentVector.end(); )
		{
			if ((*it)->m_id == removedID)
			{	
				delete* it;
				it = m_pComponentVector.erase(it);
				continue;
			}
			++it;
		}
	}
	m_pRemovedComponents.clear();
}

////////////////////////////////////////////////////////////
// Returns component attached to actor with matching id
// Returns nullptr if Id is not found
////////////////////////////////////////////////////////////
[[nodiscard("Component Unused")]] Component* Actor::GetComponent(id_t id)
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

void Actor::Init(World* pWorld, Position_t startPosition)
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
	//if (HasTag("treasure")) // debug test
	//	std::cout << "treausre\n";
	
	// Update Components -> for every collison run on Collide.
	
	// allow for movement and logic
	for (auto& component : m_pComponentVector)
		component->Update();

	// check if they then collided
	m_pCollider->Update();

	// then do collision stuff
	if( !m_pCollidedActors.empty() )
	{
		for (auto& component : m_pComponentVector)
			component->OnCollide();
	}

	DeleteRemovedComponents();
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

