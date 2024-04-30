#include "ActorFactory.h"

#include <concepts>

#include "World.h"
#include "Appearances.h"
#include "GameTags.h"

#include "../Engine/SDL_integration/WindowRenderer2D.h"

#include "../Engine/ActorTags.h"
#include "EnemyComponents.h"
#include "PlayerComponents.h"
#include "TileComponents.h"
#include "HealthTracker.h"


using namespace ActorFactory;

static Actor* CreateAndSetActorAppearance(const char* spriteFile, SDL_Renderer* pRenderer, World* pWorld, Actor::Position_t Pos)
{
	Actor* newActor = new Actor(WindowRenderer2D::s_id);
	newActor->GetComponent<WindowRenderer2D>()->Init(pRenderer, spriteFile);
	newActor->Init(pWorld, Pos);
	return newActor;
}

Actor* ActorFactory::CreateEmptyTile(World* pWorld, Actor::Position_t Pos , SDL_Renderer* pRenderer)
{
	Actor* newActor = CreateAndSetActorAppearance( "Game/Sprites/EmptyTile.bmp", pRenderer, pWorld, Pos);
	newActor->AddComponent<ActorTags>()->GiveTag(GameTag::kEmpty);
	return newActor;
}

Actor* ActorFactory::CreateBombTile(World* pWorld, Actor::Position_t Pos, SDL_Renderer* pRenderer)
{
	Actor* newActor = CreateAndSetActorAppearance("Game/Sprites/Bomb.bmp", pRenderer, pWorld, Pos);
	newActor->AddComponent<ExplodeOnCollide>();


	return newActor;
}

Actor* ActorFactory::CreateMimicTile(World* pWorld, Actor::Position_t Pos, SDL_Renderer* pRenderer)
{
	Actor* newActor = CreateAndSetActorAppearance("Game/Sprites/Treasure.bmp", pRenderer, pWorld, Pos);
	newActor->AddComponent<ExplodeOnCollide>();

	return newActor;
}

Actor* ActorFactory::CreateExitTile(World* pWorld, Actor::Position_t Pos, SDL_Renderer* pRenderer)
{
	Actor* newActor = CreateAndSetActorAppearance("Game/Sprites/Exit.bmp", pRenderer, pWorld, Pos);
	newActor->AddComponent<EndGameOnCollide>();

	return newActor;
}

Actor* ActorFactory::CreateTreasureTile(World* pWorld, Actor::Position_t Pos, SDL_Renderer* pRenderer)
{
	Actor* newActor = CreateAndSetActorAppearance("Game/Sprites/Treasure.bmp", pRenderer, pWorld, Pos);
	newActor->AddComponent<GiveTreasureCollide>();
	return newActor;
}

///////////////////////////////////////////////////////////////
// TeleportCollide Component Requires Init of linked position
///////////////////////////////////////////////////////////////
Actor* ActorFactory::CreateTeleporterTile(World* pWorld, Actor::Position_t Pos, SDL_Renderer* pRenderer)
{
	Actor* newActor = CreateAndSetActorAppearance("Game/Sprites/Teleporter.bmp", pRenderer, pWorld, Pos);
	newActor->AddComponent<TeleportCollide>();

	return newActor;
}

Actor* ActorFactory::CreateDirectEnemy(World* pWorld, Actor::Position_t Pos, SDL_Renderer* pRenderer)
{
	Actor* newActor = CreateAndSetActorAppearance("Game/Sprites/DirectEnemy.bmp", pRenderer, pWorld, Pos);
	newActor->AddComponent<HealthTracker>()->SetHealth(1);
	newActor->AddComponent<EnemyLogic>()->Init(EnemyLogic::EnemyType::kDirect);

	return newActor;
}

Actor* ActorFactory::CreateScaredEnemy(World* pWorld, Actor::Position_t Pos, SDL_Renderer* pRenderer)
{
	Actor* newActor = CreateAndSetActorAppearance("Game/Sprites/ScaredEnemy.bmp", pRenderer, pWorld, Pos);
	newActor->AddComponent<HealthTracker>()->SetHealth(1);
	newActor->AddComponent<EnemyLogic>()->Init(EnemyLogic::EnemyType::kScared);

	return newActor;
}

Actor* ActorFactory::Createplayer(World* pWorld, Actor::Position_t Pos, int startingHealth, SDL_Renderer* pRenderer)
{
	Actor* newActor = CreateAndSetActorAppearance( "Game/Sprites/Player.bmp", pRenderer, pWorld, Pos);
	newActor->AddComponent<PlayerMover>();
	newActor->AddComponent<MoneyCounter>();
	newActor->AddComponent<MimicFinder>();
	newActor->AddComponent<HealthTracker>()->SetHealth(startingHealth);
	newActor->AddComponent<PlayerScore>(); // this requires information from the others so must be here
	newActor->AddComponent<PlayerUI>(); // this must be placed last bc its constuctor. I know its dumb
	newActor->AddComponent<ActorTags>()->GiveTag(GameTag::kPlayer);

	return newActor;
}
