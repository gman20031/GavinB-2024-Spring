#pragma once

#include "../System/Vector2d.h"

#include "../Engine/ComponentFactory.h"

class EnemyLogic : public Component
{
public:
	ID_FROM_NAME("EnemyLogic");
	enum class Direction
	{
		kUp, 
		kDown,
		kLeft, 
		kRight,
		kCount,
	} static ;
	enum class EnemyType
	{ 
		kDirect,
		kScared,
		kCount,
	} static ;
private:
	static constexpr size_t kSightRange = 5;
	Vector2d<int> m_oldPosition;
	EnemyType m_type = EnemyType::kCount;
private:
	bool PlayerInSight(Vector2d<int> playerPos);
	Vector2d<int> GetRandomMove();
	void SafeMove(Vector2d<int> newDirections);
	[[nodiscard]] Vector2d<int> NormalVectorTowardsPlayer(Vector2d<int> playerPos);
	Vector2d<int> GetPlayerLocation();
	void MovePosition(Vector2d<int> moveDistances);
	void MovePosition(Direction dir);

public:
	EnemyLogic(Actor* pOwner) : Component(pOwner), m_oldPosition(0, 0) {}

	void Init(EnemyType type);
	virtual void Update() override;
	virtual void OnCollide() override;

};
