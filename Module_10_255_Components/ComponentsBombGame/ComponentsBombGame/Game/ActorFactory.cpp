#include "ActorFactory.h"

#include <concepts>

#include "World.h"
#include "Appearances.h"

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
	newActor->GiveTag("treasure");
	
	return newActor;
}

///////////////////////////////////////////////////////////////
// TeleportCollide Component Requires Init of linked position
///////////////////////////////////////////////////////////////
Actor* ActorFactory::CreateTeleporterTile(World* pWorld, Actor::Position_t Pos)
{
	Actor* newActor = CreateAndSetActorAppearance(kTeleporter, pWorld, Pos);
	newActor->AddComponent<TeleportCollide>();
	
	return newActor;
}

Actor* ActorFactory::CreateDirectEnemy(World* pWorld, Actor::Position_t Pos)
{
	Actor* newActor = CreateAndSetActorAppearance(kDirectEnemy, pWorld, Pos);
	newActor->AddComponent<HealthTracker>()->SetHealth(1);
	newActor->AddComponent<DirectEnemyLogic>();
	
	return newActor;
}

Actor* ActorFactory::CreateScaredEnemy(World* pWorld, Actor::Position_t Pos)
{
	Actor* newActor = CreateAndSetActorAppearance(kRandomEnemy, pWorld, Pos);
	newActor->AddComponent<HealthTracker>()->SetHealth(1);
	newActor->AddComponent<ScaredEnemyLogic>();
	
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

	
	return newActor;
}
