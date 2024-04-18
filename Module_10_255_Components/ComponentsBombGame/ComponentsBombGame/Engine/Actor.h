#pragma once

#include "Basic2dCollider.h"
#include "BasicRenderer.h"
#include "Component.h"
#include "Vector2.h"
#include <vector>

class Actor
{
	Component* m_pRenderer = nullptr;
	Component* m_pCollider = nullptr;
	std::vector<Component*> m_pComponentVector;


	virtual void Start() = 0;
public:
	template<class RendererType = BasicRenderer, class ColliderType = Basic2dCollider>
	Actor();
	SimpleVector2 Position;
	std::vector<Actor*> m_pCollidedActors;

	void AddComponent(Component* pNewComponent);
	virtual void Update() = 0;
};

template<class RendererType, class ColliderType>
Actor::Actor()
{

}