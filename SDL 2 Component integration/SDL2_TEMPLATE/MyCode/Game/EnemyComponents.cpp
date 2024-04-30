#include "EnemyComponents.h"

#include <concepts>
#include <random>

#include "../System/Vector2d.h"
#include "../System/G_Rand.h"

#include "../Engine/Actor.h"

#include "GameTags.h"
#include "HealthTracker.h"
#include "world.h"

////////////////////////////////////////////////////////////
// If the enemy is within range of player, it will do a 
// specialized move based on type.
// otherwise will move randomly and never step on any non
// empty tile and will not leave arena to their doom.
////////////////////////////////////////////////////////////
void EnemyLogic::Update()
{
	Actor::Position_t ownerPos  = m_pOwner->GetPosition();
	Actor::Position_t playerPos = GetPlayerLocation();
	m_oldPosition = ownerPos;
	if (PlayerInSight(playerPos) )
	{
		if (playerPos == ownerPos)
			return;
		Actor::Position_t moveDistances = NormalVectorTowardsPlayer(playerPos);
		switch (m_type)
		{
		case EnemyType::kDirect: MovePosition(moveDistances); break;
		case EnemyType::kScared: MovePosition(-moveDistances); break;
		}
	}
	else
	{
		SafeMove(GetRandomMove());
	}

	//update the tile I am now standing on now.
	m_pOwner->GetWorldPtr()->UpdateTile(m_pOwner->GetPosition());
}

////////////////////////////////////////////////////////////
// Sets the position of the actor back to before it steped
// For every actor collided with, if it was the player
// Kills it. 
////////////////////////////////////////////////////////////
void EnemyLogic::OnCollide()
{
	m_pOwner->SetPosition(m_oldPosition);
	for (Actor* actor : m_pOwner->GetComponent<Basic2dCollider>()->CollidedActors())
	{
		ActorTags* pTags = actor->GetComponent<ActorTags>();
		if (pTags)
		{
			if (pTags->HasTag(GameTag::kPlayer))
				actor->GetComponent<HealthTracker>()->Kill();
		}
	}
}

////////////////////////////////////////////////////////////
// Sets the enemy type to to type givem
////////////////////////////////////////////////////////////
void EnemyLogic::Init(EnemyType type)
{
	m_type = type;
}

////////////////////////////////////////////////////////////////////////
//								 Helper functions
////////////////////////////////////////////////////////////////////////

static int Square(int number) {
	return (number * number);
}

////////////////////////////////////////////////////////////
// Moves the position of the enemy based on the distances
// given.
////////////////////////////////////////////////////////////
void EnemyLogic::MovePosition(Actor::Position_t moveDistances)
{
	Actor::Position_t newPos = m_pOwner->GetPosition() + moveDistances;
	m_pOwner->SetPosition(newPos);
}

////////////////////////////////////////////////////////////
// Moves the position of the enemy based on the distances
// given.
////////////////////////////////////////////////////////////
void EnemyLogic::MovePosition(Direction dir)
{
	using enum Direction;
	switch(dir)
	{
	case kUp:	 MovePosition({  0,-1 }); break;
	case kDown:	 MovePosition({  0, 1 }); break;
	case kRight: MovePosition({  1, 0 }); break;
	case kLeft:	 MovePosition({ -1, 0 }); break;
	default:	 MovePosition({  0, 0 }); break;
	}
}

////////////////////////////////////////////////////////////
// Returns the locatio of the player as a Vector2d<int>
////////////////////////////////////////////////////////////
Actor::Position_t EnemyLogic::GetPlayerLocation()
{
	return m_pOwner->GetWorldPtr()->GetPlayerPointer()->GetPosition();
}

////////////////////////////////////////////////////////////
// Returns a normalized vector2d<int> that is pointing
// in the direction of the player.
////////////////////////////////////////////////////////////
[[nodiscard]] Actor::Position_t EnemyLogic::NormalVectorTowardsPlayer(Actor::Position_t playerPos)
{										
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
	int xDistance = playerPos.x - m_pOwner->GetPosition().x;		 
	int yDistance = playerPos.y - m_pOwner->GetPosition().y;		
	int absX = std::abs(xDistance);					
	int absY = std::abs(yDistance);					
													
	int deltaX = 0;
	int deltaY = 0;

	// if player is in the same collumn(y)
	if (absX == 0)
	{
		deltaY = (yDistance / absY);
		return { deltaX, deltaY };
	}

	// if player is in the same row (x)
	if (absY == 0)
	{
		deltaX = (xDistance / absX);
		return { deltaX, deltaY };
	}

	// if player is closer horizontally than verically
	if (absX < absY)
		deltaX = (xDistance / absX);

	// if player is closer vertically than horziontally
	if (absY < absX)
		deltaY = (yDistance / absY);

	// if the player is exactly 1 square diagonally
	if (absY == absX)
		deltaX = (xDistance / absX);

	return { deltaX, deltaY };
}

////////////////////////////////////////////////////////////
// Returns true if the player is within a number of squares 
// specified by the sight range of the enemy
////////////////////////////////////////////////////////////
bool EnemyLogic::PlayerInSight(Actor::Position_t playerPos)
{
	int sightRangeSquared = kSightRange * kSightRange;
	int dX = Square(playerPos.x - m_pOwner->GetPosition().x);
	int dY = Square(playerPos.y - m_pOwner->GetPosition().y);
	int distanceSquared = dX + dY;

	return(distanceSquared < sightRangeSquared);
}

////////////////////////////////////////////////////////////
// Attempts to move in the direction given, if the tile
// the enemy is attempting to move to does not have the tag
// "empty" the enemy will not move.
////////////////////////////////////////////////////////////
void EnemyLogic::SafeMove(Vector2d<int> newDirections)
{
	World* pWorld = m_pOwner->GetWorldPtr();
	auto pos = m_pOwner->GetPosition();
	int newX = pos.x + newDirections.x;
	int newY = pos.y + newDirections.y;

	Actor* pTile = pWorld->GetTileAt(newX, newY);
	if(pTile)
	{
		auto pTags = pTile->GetComponent<ActorTags>();
		if(pTags)
		{
			if (pTags->HasTag(GameTag::kEmpty))
			{
				Actor::Position_t newPosition(newX, newY);
				m_pOwner->SetPosition(newPosition);
			}
		}
	}
}

////////////////////////////////////////////////////////////
// Returns a random vector2d<int> that will result in the 
// enemy moving 1 tile up,down,left, or right.
////////////////////////////////////////////////////////////
Vector2d<int> EnemyLogic::GetRandomMove()
{
	using enum Direction;
	uint64_t dir = G_Rand::SC_Rand(0, 3);
	switch ((Direction)dir)
	{
	case kUp:	 return { 0,-1 };
	case kDown:	 return { 0, 1 };
	case kRight: return { 1, 0 };
	case kLeft:	 return { -1,0 };
	}
	return { 0,0 };
}

