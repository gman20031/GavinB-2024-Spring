#pragma once

#include "GameObject.h"


class Sword : public GameObject
{
	CREATE_CHAR(ObjectChar::kSwordItem)
private:
	virtual void Collide(Entity* collidedEntity) override;
public:
	Sword() : GameObject(s_displayCharacter) {}
};
