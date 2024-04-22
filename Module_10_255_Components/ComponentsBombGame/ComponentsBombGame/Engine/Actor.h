#pragma once

#include "ComponentFactory.h"
#include "Basic2dCollider.h"
#include "BasicRenderer.h"
#include "../System/Vector2d.h"

#include <vector>
#include <unordered_map>

class World;

class Actor
{
public:
	friend bool operator==(const Actor& lhs, const Actor& rhs);
	inline static size_t s_actorCount = 0;
	using Position_t = Vector2d<int>;
	using id_t = Component::IdType;
private:
	Component* const m_pRenderer = nullptr;
	Component* const m_pCollider = nullptr;
	std::vector<Component*> m_pComponentVector;
	std::unordered_map<id_t, Component*> m_ComponentMap;
	std::vector<Actor*> m_pCollidedActors;
	std::vector<std::string> m_tags;

	Position_t m_position;
	World* m_pWorld;
	const size_t m_uniqueId;

public:
	Actor(id_t RendererID = BasicRenderer::s_id , id_t ColliderID = Basic2dCollider::s_id);
	Actor(const Actor& original);
	Actor* Clone();
	//Actor operator=(const Actor& rhs);
	~Actor();

	Component* AddComponent(Component* pNewComponent, id_t);
	Component* AddComponent(id_t id);
	[[nodiscard("Component Unused")]] Component* GetComponent(id_t componentId);

	void GiveTag(const std::string& tag) { m_tags.emplace_back(tag); }
	bool RemoveTag(const std::string& tag);
	bool HasTag(const std::string& tag);

	Position_t GetPosition() const { return m_position; }
	void SetPosition(Position_t newPos) { m_position = newPos; }
	World* GetWorldPtr() const { return m_pWorld; }

	const std::vector<Actor*>& GetCollidedActorst() { return m_pCollidedActors; }
	void Start(World* pWorld, Position_t startPosition);
	void Update(); 
	void Render() { m_pRenderer->Render(); }
};



