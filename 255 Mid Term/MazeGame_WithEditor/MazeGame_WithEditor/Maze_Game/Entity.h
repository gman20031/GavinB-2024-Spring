#pragma once

#include "GameObject.h"
#include "Directions.h"
#include "ObjectMover.h"

////////////////////////////////////////////////////////////////
/// To minimize inheritance, it is assumed all inheritors of Enitity
/// are enemy units.
////////////////////////////////////////////////////////////////
class Entity : public GameObject
{
protected:
	friend class ObjectMover;
	inline static ObjectMover s_objectMover;
	enum class movementType
	{
		kNone,
		kPlayer,
		kRandom,
		kDirect,
		kBouncing,
	};
	movementType m_moveType;
	Direction m_currentDirection;
	bool m_collidedWithPlayer = false;
public:
	Entity(GameObjectType newType, movementType moveType, Direction currDirection)
		: GameObject(newType)
		, m_moveType(moveType)
		, m_currentDirection(currDirection)
	{}

	virtual void Update() override;
	virtual void Collide(Entity* collidedEntity) override;
	virtual void HitWall() { return; }
	virtual void Kill() override;
};
