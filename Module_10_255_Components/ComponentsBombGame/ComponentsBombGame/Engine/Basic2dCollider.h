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
	//Basic2dCollider(const Basic2dCollider& other, Actor* pOwner);
private:
	
public:
	virtual Component* Clone(Actor* pOwner) override;

	virtual void Update() override;
};
