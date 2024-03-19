#pragma once

#include "Entity.h"

class Player : public Entity
{
	CREATE_CHAR(GameObjectType::kPlayer)
private:
	static constexpr size_t kMoveSpeed = 1;
	virtual void Collide( Entity* collidedEntity) override;

	bool m_alive = true;
public:
	Player() : Entity(s_displayCharacter) {}

	virtual bool IsPlayer() override{ return true; }
	virtual void Update() override;
};