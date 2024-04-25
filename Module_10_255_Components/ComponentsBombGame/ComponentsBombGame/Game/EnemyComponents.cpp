#include "EnemyComponents.h"

#include <concepts>
#include "GameTags.h"
#include "HealthTracker.h"
#include "../Engine/Actor.h"
#include "../System/Vector2d.h"
#include "world.h"

static bool PlayerInRange(Actor::Position_t playerPos, Actor* enemy, int sightRange);
static void SafeMove(Actor* enemy, int deltaX, int deltaY);
static void MoveRandom(Actor* enemy);
static Actor::Position_t GetNormalMoveTowardsPlayer(Actor::Position_t enemyPos, Actor::Position_t playerPos);
static Actor::Position_t GetPlayerLocation(Actor* enemy);
static void MoveActorPosition(Actor* enemy, Actor::Position_t moveDistances);

void DirectEnemyLogic::Update()
{
	Actor::Position_t ownerPos = m_pOwner->GetPosition();
	Actor::Position_t playerPos = GetPlayerLocation(m_pOwner);
	m_oldPosition = ownerPos;
	if (PlayerInRange(playerPos, m_pOwner, (int)kSightRange))
	{
		Actor::Position_t moveDistances = GetNormalMoveTowardsPlayer(ownerPos, playerPos);
		MoveActorPosition(m_pOwner, moveDistances);
	}
	else
		MoveRandom(m_pOwner);

	//update the tile I am now standing on.
	Actor* tile = m_pOwner->GetWorldPtr()->GetTileAt(m_pOwner->GetPosition());
	if (tile) tile->Update();
}	

void ScaredEnemyLogic::Update()
{
	Actor::Position_t ownerPos = m_pOwner->GetPosition();
	Actor::Position_t playerPos = GetPlayerLocation(m_pOwner);
	m_oldPosition = ownerPos;
	if (PlayerInRange(playerPos, m_pOwner, (int)kSightRange))
	{
		Actor::Position_t moveDistances = GetNormalMoveTowardsPlayer(ownerPos, playerPos);
		MoveActorPosition(m_pOwner, -moveDistances);
	}
	else
		MoveRandom(m_pOwner);

	//update the tile I am now standing on.
	Actor* tile = m_pOwner->GetWorldPtr()->GetTileAt(m_pOwner->GetPosition());
	if(tile)
		tile->Update();
}

void DirectEnemyLogic::OnCollide()
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

void ScaredEnemyLogic::OnCollide()
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

template<Number T>
static T Square(T number) {
	return (number * number);
}

static Actor::Position_t GetPlayerLocation(Actor* enemy)
{
	return enemy->GetWorldPtr()->GetPlayerPointer()->GetPosition();
}

void MoveActorPosition(Actor* enemy, Actor::Position_t moveDistances)
{
	Actor::Position_t newPos = enemy->GetPosition() + moveDistances;
	enemy->SetPosition(newPos);
}


[[nodiscard]] static Actor::Position_t GetNormalMoveTowardsPlayer(Actor::Position_t enemyPos, Actor::Position_t playerPos)
{												
	// https://imgur.com/a/ckZGmPe				// . -1 . 	 
												// -1 E +1 	 
	int xDistance = playerPos.x - enemyPos.x;	// . +1 . 	 
	int yDistance = playerPos.y - enemyPos.y;		
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

	return { deltaX, deltaY };
}

static bool PlayerInRange(Actor::Position_t playerPos, Actor* enemy, int sightRange)
{
	int sightRangeSquared = sightRange * sightRange;
	int dX = Square(playerPos.x - enemy->GetPosition().x);
	int dY = Square(playerPos.y - enemy->GetPosition().y);
	int distanceSquared = dX + dY;

	return(distanceSquared < sightRangeSquared);
}

static void SafeMove(Actor* enemy, int deltaX, int deltaY)
{
	World* pWorld = enemy->GetWorldPtr();

	auto pos = enemy->GetPosition();
	int newX = pos.x + deltaX;
	int newY = pos.y + deltaY;

	Actor* pTile = pWorld->GetTileAt(newX, newY);
	if(pTile)
	{
		auto pTags = pTile->GetComponent<ActorTags>();
		if(pTags)
		{
			if (pTags->HasTag(GameTag::kEmpty))
				enemy->SetPosition({ newX,newY });
		}
	}
}

static void MoveRandom(Actor* enemy)
{
	int direction = rand() % 4;

	switch (direction)
	{
	case 0: SafeMove(enemy, -1, 0); break;
	case 1: SafeMove(enemy, 1, 0); break;
	case 2: SafeMove(enemy, 0, 1); break;
	case 3: SafeMove(enemy, 0, -1); break;
	}
}

