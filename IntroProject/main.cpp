// Enemy.h

#include <memory>
#include "Vector2.h"

class Enemy
{
public:
	using PositionVector = Vector2<int>;
private:
	PositionVector m_position;
public:
	Enemy(const PositionVector& position);
};

// Enemy.cpp
#include "Enemy.h"
Enemy::Enemy(const PositionVector& position)
	: m_position{ position }
{}

// EnemySpawner.h
#include <memory>
class EnemySpawner
{
private:
	using EnemyPtr = std::shared_ptr<Enemy>;
public:
	EnemyPtr Spawn(Enemy::PositionVector position);
};

// EnemySpawner.cpp
#include "EnemySpawner.h"
#include "Enemy.h"

EnemySpawner::EnemyPtr EnemySpawner::Spawn(Enemy::PositionVector position)
{
	return std::make_shared<Enemy>(position);
}

// main.cpp
#include "EnemySpawner.h"

int main()
{
	EnemySpawner spawner;

	std::shared_ptr<Enemy> enemy = spawner.Spawn(Vector2<int>{5, 10});

	//Play game

	return 0;
}