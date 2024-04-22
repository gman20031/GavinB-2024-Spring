#include "EnemyComponents.h"

#include <concepts>
#include "GameTags.h"
#include "../Engine/Actor.h"
#include "world.h"

bool PlayerInRange(Actor::Position_t playerPos, Actor* enemy, size_t sightRangeSquared);
void SafeMove(Actor* enemy, int deltaX, int deltaY);
void MoveRandom(Actor* enemy);
Actor::Position_t MoveRelatedToPlayer(Actor* enemy, Actor::Position_t playerPos);
Actor::Position_t GetPlayerLocation(Actor* enemy);


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
}

void DirectEnemyLogic::OnCollide()
{
	m_pOwner->SetPosition(m_oldPosition);
}

void ScaredEnemyLogic::OnCollide()
{
	m_pOwner->SetPosition(m_oldPosition);
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
https://imgur.com/a/ckZGmPe

	int xDistance = enemy->GetPosition().x;
	int yDistance = enemy->GetPosition().y;
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

