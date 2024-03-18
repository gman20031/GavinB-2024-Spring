#pragma once

#include "Entity.h"
#include "Directions.h"

class Player : public Entity
{
	CREATE_CHAR_DRAW(ObjectCharacter::kPlayer)
private:
	static constexpr size_t kMoveSpeed = 1;
	virtual void Collide( Entity* collidedEntity) override;

	bool m_alive = true;

	//kill playeer()
	//sawp player with()

public:
	Player() : Entity() {}

	virtual bool IsPlayer() override{ return true; }
	virtual void Update() override;
};