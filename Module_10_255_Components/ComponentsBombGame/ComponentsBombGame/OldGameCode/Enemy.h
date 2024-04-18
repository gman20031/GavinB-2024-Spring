#pragma once

#include "Entity.h"

class EnemyMover;

static constexpr int Square(int val) { return val * val; }

class Enemy : public Entity
{
	static constexpr int kSightRange = 5;
	static constexpr int kSightRangeSquared = Square(kSightRange);

	friend class EnemyMover;
	EnemyMover* m_pMover;

	char m_displayChar;

public:
	Enemy(char displayChar, EnemyMover* pMover , int x, int y, World* pWorld);
	Enemy(const Enemy& original) = default;

	virtual Enemy* Clone();
	void Init(int x, int y, World* pWorld);

	virtual void Update();
	virtual void Draw();
};

class EnemyMover
{
public:
	enum class MoveType
	{
		kChase,
		kRunAway,
		kCount,
	} static;
	struct Position
	{
		int x, y;
	};

protected:
	MoveType m_moveType;

	Position FindPlayerLocation(Enemy* enemy) const;
	bool PlayerInRange(Position playerPos, Enemy* enemy) const;
	void ChangePostion(Enemy* enemy, int deltaX, int deltaY) const;
	void MoveRandom(Enemy* enemy) const;
	void SafeMove(Enemy* enemy,int deltaX, int deltaY) const;

	void RunAway(Enemy* enemy, Position playerPos) const;
	void Chase(Enemy* enemy, Position playerPos) const;
public:
	EnemyMover(MoveType moveType) : m_moveType(moveType) {}
	void Move(Enemy* enemy) const;
};
