#pragma once

#include "Component.h"

class BasicRenderer : public Component
{
public:
	static CounterId s_Id;
	BasicRenderer(Actor* pOwner) : Component(pOwner, *s_Id) {}
private:

public:


};
