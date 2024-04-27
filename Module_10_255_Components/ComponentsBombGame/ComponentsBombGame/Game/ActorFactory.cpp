#include "ActorFactory.h"

#include <concepts>

#include "World.h"
#include "Appearances.h"
#include "GameTags.h"

#include "../Engine/ActorTags.h"
#include "EnemyComponents.h"
#include "PlayerComponents.h"
#include "TileComponents.h"
#include "HealthTracker.h"


using namespace ActorFactory;
using enum TileAppearance;

static Actor* CreateAndSetActorAppearance(TileAppearance newSprite, World* pWorld, Actor::Position_t Pos)
{
	Actor* newActor = new Actor;
	newActor->GetComponent<BasicRenderer>()->ChangeSprite( BasicRenderer::sprite_t(newSprite) );
	
	newActor->Init(pWorld, Pos);
	return newActor;
}

Actor* ActorFactory::CreateEmptyTile(World* pWorld, Actor::Position_t Pos)
{
	Actor* newActor = CreateAndSetActorAppearance(kEmpty, pWorld, Pos);
	newActor->AddComponent<ActorTags>()->GiveTag(GameTag::kEmpty);
	return newActor;
}

Actor* ActorFactory::CreateBombTile(World* pWorld, Actor::Position_t Pos)
{
	Actor* newActor = CreateAndSetActorAppearance(kBomb, pWorld, Pos);
	newActor->AddComponent<ExplodeOnCollide>();
	
	
	return newActor;
}

Actor* ActorFactory::CreateMimicTile(World* pWorld, Actor::Position_t Pos)
{
	Actor* newActor = CreateAndSetActorAppearance(kTreasure, pWorld, Pos);
	newActor->AddComponent<ExplodeOnCollide>();
	
	return newActor;
}

Actor* ActorFactory::CreateExitTile(World* pWorld, Actor::Position_t Pos)
{
	Actor* newActor = CreateAndSetActorAppearance(kExit, pWorld, Pos);
	newActor->AddComponent<EndGameOnCollide>();
	
	return newActor;
}

Actor* ActorFactory::CreateTreasureTile(World* pWorld, Actor::Position_t Pos)
{
	Actor* newActor = CreateAndSetActorAppearance(kTreasure, pWorld, Pos);
	newActor->AddComponent<GiveTreasureCollide>();
	newActor->AddComponent<ActorTags>()->GiveTag("treasure");
	return newActor;
}

///////////////////////////////////////////////////////////////
// TeleportCollide Component Requires Init of linked position
///////////////////////////////////////////////////////////////
Actor* ActorFactory::CreateTeleporterTile(World* pWorld, Actor::Position_t Pos)
{
	Actor* newActor = CreateAndSetActorAppearance(kTeleporter, pWorld, Pos);
	newActor->GetComponent<BasicRenderer>()->SetFormatting(TEXT_YEL);
	newActor->AddComponent<TeleportCollide>();
	
	return newActor;
}

Actor* ActorFactory::CreateDirectEnemy(World* pWorld, Actor::Position_t Pos)
{
	Actor* newActor = CreateAndSetActorAppearance(kDirectEnemy, pWorld, Pos);
	newActor->AddComponent<HealthTracker>()->SetHealth(1);
	newActor->AddComponent<EnemyLogic>()->Init(EnemyLogic::EnemyType::kDirect);
	newActor->GetComponent<BasicRenderer>()->SetFormatting(TEXT_RED);

	return newActor;
}

Actor* ActorFactory::CreateScaredEnemy(World* pWorld, Actor::Position_t Pos)
{
	Actor* newActor = CreateAndSetActorAppearance(kRandomEnemy, pWorld, Pos);
	newActor->AddComponent<HealthTracker>()->SetHealth(1);
	newActor->AddComponent<EnemyLogic>()->Init(EnemyLogic::EnemyType::kScared);
	newActor->GetComponent<BasicRenderer>()->SetFormatting(TEXT_RGB(255, 0, 0));

	return newActor;
}

Actor* ActorFactory::Createplayer(World* pWorld, Actor::Position_t Pos, int startingHealth)
{
	Actor* newActor = CreateAndSetActorAppearance(kPlayer, pWorld, Pos);
	newActor->AddComponent<PlayerMover>();
	newActor->AddComponent<MoneyCounter>();
	newActor->AddComponent<MimicFinder>();
	newActor->AddComponent<HealthTracker>()->SetHealth(startingHealth);
	newActor->AddComponent<PlayerScore>(); // this requires information from the others so must be here
	newActor->AddComponent<PlayerUI>(); // this must be placed last bc its constuctor. I know its dumb
	newActor->AddComponent<ActorTags>()->GiveTag(GameTag::kPlayer);
	newActor->GetComponent<BasicRenderer>()->SetFormatting(TEXT_RGB(0,255,255));

	return newActor;
}
