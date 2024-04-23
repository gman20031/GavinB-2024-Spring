#include "EnemyComponents.h"

#include <concepts>
#include "GameTags.h"
#include "HealthTracker.h"
#include "../Engine/Actor.h"
#include "world.h"

static bool PlayerInRange(Actor::Position_t playerPos, Actor* enemy, size_t sightRangeSquared);
static void SafeMove(Actor* enemy, int deltaX, int deltaY);
static void MoveRandom(Actor* enemy);
static Actor::Position_t MoveRelatedToPlayer(Actor* enemy, Actor::Position_t playerPos);
static Actor::Position_t GetPlayerLocation(Actor* enemy);


void DirectEnemyLogic::Update()
{
	Actor::Position_t playerPos = GetPlayerLocation(m_pOwner);
	m_oldPosition = playerPos;
	if (PlayerInRange(playerPos, m_pOwner, kSightRange))
	{
		Actor::Position_t newPos = MoveRelatedToPlayer(m_pOwner, playerPos);
		m_pOwner->SetPosition(newPos);
	}
	else
		MoveRandom(m_pOwner);

	//update the tile I am now standing on.
	m_pOwner->GetWorldPtr()->GetTileAt(m_pOwner->GetPosition())->Update();
}	

void ScaredEnemyLogic::Update()
{
	Actor::Position_t playerPos = GetPlayerLocation(m_pOwner);
	m_oldPosition = playerPos;
	if (PlayerInRange(playerPos, m_pOwner, kSightRange))
	{
		Actor::Position_t newPos = MoveRelatedToPlayer(m_pOwner, playerPos);
		m_pOwner->SetPosition(-newPos);
	}
	else
		MoveRandom(m_pOwner);

	//update the tile I am now standing on.
	m_pOwner->GetWorldPtr()->GetTileAt(m_pOwner->GetPosition())->Update();
}

void DirectEnemyLogic::OnCollide()
{
	m_pOwner->SetPosition(m_oldPosition);
	for (Actor* actor : m_pOwner->GetCollidedActors())
	{
		if (actor->HasTag(GameTag::kPlayer))
			actor->GetComponent<HealthTracker>()->Kill();
	}
}

void ScaredEnemyLogic::OnCollide()
{
	m_pOwner->SetPosition(m_oldPosition);
	for (Actor* actor : m_pOwner->GetCollidedActors())
	{
		if (actor->HasTag(GameTag::kPlayer))
			actor->GetComponent<HealthTracker>()->Kill();
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

[[nodiscard]] static Actor::Position_t MoveRelatedToPlayer(Actor* enemy, Actor::Position_t playerPos)
{
	// https://imgur.com/a/ckZGmPe

	int xDistance = playerPos.x - enemy->GetPosition().x;
	int yDistance = playerPos.y - enemy->GetPosition().y;
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

static bool PlayerInRange(Actor::Position_t playerPos, Actor* enemy, size_t sightRangeSquared)
{
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
	if (pTile != nullptr and pTile->HasTag("empty"))
		enemy->SetPosition({ newX,newY });
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

