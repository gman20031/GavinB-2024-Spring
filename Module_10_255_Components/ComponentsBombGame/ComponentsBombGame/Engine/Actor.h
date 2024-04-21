#pragma once

#include "Basic2dCollider.h"
#include "BasicRenderer.h"
#include "Component.h"
#include "Vector2.h"

#include <vector>
#include <unordered_map>

class Actor
{
	Component* m_pRenderer = nullptr;
	Component* m_pCollider = nullptr;
	std::vector<Component*> m_pComponentVector;
	std::unordered_map<size_t, Component*> m_ComponentMap;
	std::vector<Actor*> m_pCollidedActors;

	virtual void Start() = 0;
public:
	template<class RendererType = BasicRenderer, class ColliderType = Basic2dCollider>
	constexpr Actor();

	constexpr Component* AddComponent(Component* pNewComponent);
	template<typename... ArgT> constexpr Component* AddComponent(size_t componentId, ArgT... args);
	constexpr [[nodiscard("Component Unused")]] Component* GetComponent(size_t componentId);
	virtual void Update() = 0;
};

template<class RendererType, class ColliderType>
constexpr Actor::Actor()
{

}

template<typename... ArgT>
constexpr Component* AddComponent(size_t componentId, ArgT... args)
{

}