#pragma once

#include "../../Engine/Component/Component.h"

class PlayerMover : public Component
{
public:
	ID_FROM_NAME("PlayerMover");
private:

private: // method

public:
	PlayerMover(Actor* pActor) : Component(pActor) {}

};



