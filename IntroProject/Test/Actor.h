#pragma once

#include "ComponentFactory.h"
#include "Basic2dCollider.h"
#include "BasicRenderer.h"
#include "Vector2.h"

#include <vector>
#include <unordered_map>

class Actor
{
	using id_t = Component::IdType;

	Component* m_pRenderer = nullptr;
	Component* m_pCollider = nullptr;
	std::vector<Component*> m_pComponentVector;
	std::unordered_map<id_t, Component*> m_ComponentMap;
	std::vector<Actor*> m_pCollidedActors;

public:
	template<SubComponent RendererType = BasicRenderer, SubComponent ColliderType = Basic2dCollider>
	Actor(void);
	Actor() { m_pRenderer = new BasicRenderer(this); m_pCollider = new Basic2dCollider(this); }
	~Actor();

	Component* AddComponent(Component* pNewComponent, id_t);
	Component* AddComponent(id_t id);
	[[nodiscard("Component Unused")]] Component* GetComponent(id_t componentId);

	virtual void Start() {};
	void Update(); 
	void Render() { m_pRenderer->Render(); }
};

template<SubComponent RendererType, SubComponent ColliderType>
inline Actor::Actor()
{
	m_pRenderer = new RendererType;
	m_pCollider = new ColliderType;
}