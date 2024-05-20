#pragma once

#include <vector>
#include "Component.h"

class Actor;

class Basic2dCollider : public Component
{
public:
	ID_FROM_NAME("Basic2dCollider");
	std::vector<Actor*> m_pCollidedActors;
private:
	
public:
	Basic2dCollider(Actor* pOwner);
	Basic2dCollider(const Basic2dCollider& other);

	std::vector<Actor*>& CollidedActors() { return m_pCollidedActors; }
	virtual void Update() override;
};
