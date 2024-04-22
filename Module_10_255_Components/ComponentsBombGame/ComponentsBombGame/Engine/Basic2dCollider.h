#pragma once

#include <vector>
#include "Component.h"

class Actor;
class World;

class Basic2dCollider : public Component
{
public:
	NEW_STATIC_ID;
	Basic2dCollider(Actor* pOwner) : Component(pOwner, s_id), m_pCollidedActors(nullptr) {}
	Basic2dCollider(const Basic2dCollider& other);
	Basic2dCollider(const Basic2dCollider& other, Actor* pOwner);
private:
	std::vector<Actor*>* m_pCollidedActors;
public:
	virtual Component* Clone(Actor* pOwner) override;

	void Init(std::vector<Actor*>* pcollidedActors);
	virtual void Update() override;
};
