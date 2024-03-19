#pragma once

#include "GameObject.h"
#include "Directions.h"
#include "ObjectMover.h"

class Entity : public GameObject
{
protected:
	friend class ObjectMover;
	inline static ObjectMover s_objectMover;

public:
	Entity(GameObjectType newType) : GameObject(newType) {}

	virtual void Collide(Entity* collidedEntity) override;
	virtual void HitWall() {}
};
