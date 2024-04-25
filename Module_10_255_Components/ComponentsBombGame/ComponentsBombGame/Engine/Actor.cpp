#include "Actor.h"

#include <assert.h>

Actor::Actor(id_t RendererID, id_t ColliderID)
	: m_position(0,0)
	, m_uniqueId(s_actorCount++)
	, m_pWorld(nullptr)
{	
	AddComponent(RendererID);
	AddComponent(ColliderID);
}

Actor::~Actor()
{
	for (auto& entry : m_ComponentMap)
		delete entry.second;
}

////////////////////////////////////////////////////////////
// adds ComponentPtr to the map and vector of actor
// returns the componentPtr if successful
////////////////////////////////////////////////////////////
Component* Actor::AddComponent(Component* pNewComponent , id_t componentId)
{
	assert(pNewComponent != nullptr);
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
[[nodiscard("Component Unused")]] Component* Actor::GetComponent(id_t id)
{
	auto entry = m_ComponentMap.find(id);
	if (entry == m_ComponentMap.end())
		return nullptr;
	return entry->second;
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
	if (!this) // debug test
		std::cout << "breakpoint\n";
	
	// Update Components -> for every collison run on Collide.
	
	// allow for movement and logic
	for (auto& entry : m_ComponentMap)
	{
		if (entry.first == Basic2dCollider::s_id)
			continue;
		entry.second->Update();
	}

	GetComponent<Basic2dCollider>()->Update();
}

////////////////////////////////////////////////////////////
// for each actor collided with
// Runs onCollide for every component,
// passing in collided Actor
////////////////////////////////////////////////////////////
void Actor::Collide()
{
	for (auto pEntry = m_ComponentMap.begin(); pEntry != m_ComponentMap.end(); ++pEntry)
	{
		pEntry->second->OnCollide();
	}	
}

void Actor::Render()
{
	GetComponent<BasicRenderer>()->Render();
}

bool operator==(const Actor& lhs, const Actor& rhs)
{
	// seems the simplilest solution to, 
	// what if two of actors with all the same components, are standing on the same location
	// even with checking all the data of all the components for further information, it could still fail
	// this cannot fail, as it should be impossible for two actors to have the same id
	return (lhs.m_uniqueId == rhs.m_uniqueId);
}

