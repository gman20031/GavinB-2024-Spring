#pragma once

#include "Component.h"

class Basic2dCollider : public Component
{
public:
	static CounterId s_Id;
	Basic2dCollider(Actor* pOwner) : Component(pOwner, *s_Id) {}
private:

public:


};
