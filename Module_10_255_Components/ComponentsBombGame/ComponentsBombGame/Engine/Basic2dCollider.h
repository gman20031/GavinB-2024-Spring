#pragma once

#include <vector>
#include "Component.h"

class Actor;
class World;

class Basic2dCollider : public Component
{
public:
	NEW_STATIC_ID;
	Basic2dCollider(Actor* pOwner);
	Basic2dCollider(const Basic2dCollider& other);
	std::vector<Actor*> m_pCollidedActors;
private:
	
public:

	std::vector<Actor*>& CollidedActors() { return m_pCollidedActors; }
	virtual void Update() override;
};
