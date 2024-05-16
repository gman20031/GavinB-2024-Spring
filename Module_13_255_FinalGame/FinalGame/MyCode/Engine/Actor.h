#pragma once
#include <unordered_map>


#include "ComponentFactory.h"
#include "Basic2dCollider.h"
#include "Renderer.h"
#include "System/Vector2d.h"


class Actor
{
public:
	friend bool operator==(const Actor& lhs, const Actor& rhs);
	using Position_t = Vector2d<int>;
	using id_t = Component::IdType;

protected:
	// 

private:
	inline static uint32_t s_actorCount = 0; // to obtain unique Id.
	uint32_t m_uniqueId = 0;  // to check if two actors are the same.

	std::unordered_map<id_t, Component*> m_ComponentMap;

	Position_t m_position;
	World* m_pWorld;

public:
	Actor();
	~Actor();
	
	template<SubComponent ComponentType> ComponentType* AddComponent();
	Component* AddComponent(Component* pNewComponent, id_t);
	Component* AddComponent(id_t id);

	[[nodiscard("Component Unused")]] Component* GetComponent(id_t componentId);
	template<SubComponent ComponentType> 
	[[nodiscard("Component Unused")]] ComponentType* GetComponent();

	Position_t GetPosition() const { return m_position; }
	void SetPosition(Position_t newPos) { m_position = newPos; }

	void Init(World* pWorld, Position_t startPosition);
	void Update(); 
	void Collide();
	void Render();
};

template<SubComponent ComponentType>
inline ComponentType* Actor::AddComponent()
{
	ComponentType* newComponent = new ComponentType(this);
	AddComponent(newComponent, ComponentType::s_id);
	return newComponent;
}

template<SubComponent ComponentType>
inline ComponentType* Actor::GetComponent()
{
	return static_cast<ComponentType*>(GetComponent(ComponentType::s_id));
}
