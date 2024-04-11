#include "Enemy.h"

#include <iostream>

#include "World.h"
#include "Player.h"

////////////////////////////// Enemy //////////////////////////////

Enemy::Enemy(char displayChar, EnemyMover* pMover, int x, int y, World* pWorld)
	: Entity(x, y, pWorld)
	, m_pMover(pMover)
	, m_displayChar(displayChar)
{
}

void Enemy::Update()
{
	m_pMover->Move(this);
}

void Enemy::Draw()
{
	std::cout << m_displayChar;
}

Enemy* Enemy::Clone()
{
	return new Enemy(*this);
}

void Enemy::Init(int x, int y, World* pWorld)
{
	m_x = x;
	m_y = y;
	m_pWorld = pWorld;
}

////////////////////////////// Enemy Mover //////////////////////////////

// Finds and returns player position data
EnemyMover::Postion EnemyMover::FindPlayerLocation(Enemy* enemy) const
{
	return {
		enemy->m_pWorld->GetPlayerPointer()->GetX(),
		enemy->m_pWorld->GetPlayerPointer()->GetY()
	};
}

// Retruns true if player is within enemy sight range
bool EnemyMover::PlayerInRange(Postion playerPos, Enemy* enemy) const
{
	int dX = Square(playerPos.x - enemy->m_x);
	int dY = Square(playerPos.y - enemy->m_y);
	int distanceSquared = dX + dY;

	return(distanceSquared < enemy->kSightRangeSquared);
}

// Sets the X and Y pos of enemy based on x and y change
void EnemyMover::ChangePostion(Enemy* enemy, int deltaX, int deltaY) const
{
	enemy->m_x += deltaX;
	enemy->m_y += deltaY;
}

void EnemyMover::SafeMove(Enemy* enemy, int deltaX, int deltaY) const
{
	int newX = enemy->m_x + deltaX;
	int newY = enemy->m_y + deltaY;

	World* pWorld = enemy->m_pWorld;
	if (pWorld->GetTileAt(newX, newY)->GetAppearanceType() == AppearanceStrategy::Appearance::kEmpty)
		ChangePostion(enemy, deltaX, deltaY);

}

// Moves the enemy in a random cardinal direction
void EnemyMover::MoveRandom(Enemy* enemy) const
{
	int direction = rand() % 4;
	World*& pWorld = enemy->m_pWorld;
	switch (direction)
	{
	case 0: SafeMove(enemy, -1, -1); break;
	case 1: SafeMove(enemy, 1, -1); break;
	case 2: SafeMove(enemy, -1, 1); break;
	case 3: SafeMove(enemy,  1,  1); break;
	}
}

// Moves directly away from the player
void EnemyMover::RunAway(Enemy* enemy, Postion playerPos) const
{
	int dX = 0;
	int dY = 0;

	if (enemy->GetX() < playerPos.x)
		dX = 1;
	if (enemy->GetX() > playerPos.x)
		dX = -1;
	if (enemy->GetY() < playerPos.y)
		dY = 1;
	if (enemy->GetY() > playerPos.y)
		dY = -1;

	ChangePostion(enemy, dX, dY);
}

// Moves directly towards the player
void EnemyMover::Chase(Enemy* enemy, Postion playerPos) const
{
	int dX = 0;
	int dY = 0;

	if (enemy->GetX() < playerPos.x)
		dX = -1;
	if (enemy->GetX() > playerPos.x)
		dX = 1;
	if (enemy->GetY() < playerPos.y)
		dY = -1;
	if (enemy->GetY() > playerPos.y)
		dY = 1;

	ChangePostion(enemy, dX, dY);
}

// Moves the enemy
void EnemyMover::Move(Enemy* enemy) const
{
	using enum MoveType;
	Postion playerPos = FindPlayerLocation(enemy);
	if (PlayerInRange(playerPos, enemy))
	{
		switch (m_moveType)
		{
		case kChase: Chase(enemy, playerPos); break;
		case kRunAway: RunAway(enemy, playerPos); break;
		default: MoveRandom(enemy); break;
		}
	}
	else
		MoveRandom(enemy);
}