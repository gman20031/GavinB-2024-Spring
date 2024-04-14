#include "Enemy.h"

#include <iostream>
#include <assert.h>
#include <math.h>

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

constexpr void Enemy::Init(int x, int y, World* pWorld)
{
	m_x = x;
	m_y = y;
	m_pWorld = pWorld;
}

////////////////////////////// Enemy Mover //////////////////////////////

// Finds and returns player position data
EnemyMover::Position EnemyMover::FindPlayerLocation(Enemy* enemy) const
{
	return {
		enemy->m_pWorld->GetPlayerPointer()->GetX(),
		enemy->m_pWorld->GetPlayerPointer()->GetY()
	};
}

// Retruns true if player is within enemy sight range
bool EnemyMover::PlayerInRange(Position playerPos, Enemy* enemy) const
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
	World* pWorld = enemy->m_pWorld;

	int newX = enemy->m_x + deltaX;
	int newY = enemy->m_y + deltaY;

	if (pWorld->GetTileAt(newX, newY) != nullptr		
	and pWorld->GetTileAt(newX, newY)->GetAppearanceType() == AppearanceStrategy::Appearance::kEmpty)
		ChangePostion(enemy, deltaX, deltaY);
}

// Moves the enemy in a random cardinal direction
void EnemyMover::MoveRandom(Enemy* enemy) const
{
	int direction = rand() % 4;

	switch (direction)
	{
	case 0: SafeMove(enemy, -1,  0); break;
	case 1: SafeMove(enemy,  1,  0); break;
	case 2: SafeMove(enemy,  0,  1); break;
	case 3: SafeMove(enemy,  0, -1); break;
	}

}


/*
 Running Away:										|Chasing:												   | Chasing:											  | Chasing:
   Old:												|	Old:												   | 	Old:											  | 	Old:
   . . . 											|	. ! . 												   | 	. . !											  | 	. ! .
   ? . .											|	. . .												   | 	. . .											  | 	. . .
   . . @											|	@ . .												   | 	@ . .											  | 	. @ .
   													|														   | 													  | 	
   xDistance = (2) - (0) = 2						|	xDistance = (0) - (1) = -1							   | 	xDistance = (0) - (1) = -2						  | 	xDistance = (1) - (1) = 0
   yDistance = (2) - (1) = 1						|	yDistance = (2) - (0) = 2							   | 	yDistance = (2) - (0) = 2						  | 	yDistance = (2) - (0) = 2
   absX = 2											|	absX = 1											   | 	absX = 2										  | 	absX = 0
   absY = 1											|	absY = 2											   | 	absY = 2										  | 	absY = 2
   													|														   | 													  | 	
   absY < absX										|	absX < absY											   | 	absX = absY										  | 	absY = 0
   	dY = -(yDistance / absY) = -( 1 / 1 )  = - 1	|		dX = (xDistance / absX) = ( -1 / 1 )  = -1		   | 		dX = (xDistance / absX) = ( -2 / 2 )  = -1	  | 		dY = (yDistance / absY) = ( 2 / 2 )  = 1
   	ChangePostion(enemy, 0 , dY)					|		ChangePostion(enemy, dX , 0)					   | 		ChangePostion(enemy, dX , 0)				  | 		ChangePostion(enemy, 0 , dY)
   													|														   | 													  | 		
   new:												|	new:												   | 	new:											  | 	new:
   ? . . 											|	! . .  // cannot move diagonally so this is equally as | 	. ! . 											  | 	. . . 
   . . .											|	. . .  // effective as moving downwards				   | 	. . . 											  | 	. ? . 
   . . @											|	@ . .												   | 	@ . .											  | 	. @ .
*/

[[nodiscard]] static EnemyMover::Position MoveRelatedToPlayer(Enemy* enemy, EnemyMover::Position playerPos)
{
	// see diagram above

	int xDistance = playerPos.x - enemy->GetX();
	int yDistance = playerPos.y - enemy->GetY();
	int absX = std::abs(xDistance);
	int absY = std::abs(yDistance);

	int deltaX = 0;
	int deltaY = 0;

	if (absX == 0)
	{
		deltaY = (yDistance / absY);
		return { deltaX, deltaY };
	}

	if (absY == 0)
	{
		deltaX = (xDistance / absX);
		return { deltaX, deltaY };
	}

	if (absX < absY)
		deltaX = (xDistance / absX);

	if (absY < absX)
		deltaY = (yDistance / absY);

	return { deltaX, deltaY };
}

// Moves directly away from the player
void EnemyMover::RunAway(Enemy* enemy, Position playerPos) const
{
	Position deltaValues = MoveRelatedToPlayer(enemy, playerPos);
	ChangePostion(enemy, -deltaValues.x, -deltaValues.y);
}

// Moves directly towards the player
void EnemyMover::Chase(Enemy* enemy, Position playerPos) const
{
	Position deltaValues = MoveRelatedToPlayer(enemy, playerPos);
	ChangePostion(enemy, deltaValues.x, deltaValues.y);
}

// Moves the enemy
void EnemyMover::Move(Enemy* enemy) const
{
	using enum MoveType;
	Position playerPos = FindPlayerLocation(enemy);
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