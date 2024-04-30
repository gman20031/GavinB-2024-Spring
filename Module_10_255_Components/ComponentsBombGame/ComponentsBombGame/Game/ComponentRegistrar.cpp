#include <utility>
#include "../Engine/ComponentFactory.h"


#include "EnemyComponents.h"
#include "HealthTracker.h"
#include "TileComponents.h"
#include "PlayerComponents.h"
#include "../Engine/Basic2dCollider.h"
#include "../Engine/BasicRenderer.h"
#include "../Engine/ActorTags.h"

/*
	Current Registered Components

	Basic2dCollider
	BasicRenderer
	ActorTags

	Direct Enemy Logic
	Scared Enemy Logic

	HealthTracker

	ExplodeOnCollide
	GiveTreasureCollide
	TeleportCollide
	EndGameOnCollide

	-- player
	PlayerUI
	PlayerMover
	MoneyCounter
	PlayerScore
	MimicFinder
*/

static std::tuple<
	ComponentFactory::Registrar<Basic2dCollider>,
	
	//ComponentFactory::Registrar<BasicRenderer>,
	ComponentFactory::Registrar<ConsoleRenderer>,

	ComponentFactory::Registrar<ActorTags>,

	ComponentFactory::Registrar<EnemyLogic>,

	ComponentFactory::Registrar<HealthTracker>,

	ComponentFactory::Registrar<ExplodeOnCollide>,
	ComponentFactory::Registrar<GiveTreasureCollide>,
	ComponentFactory::Registrar<TeleportCollide>,
	ComponentFactory::Registrar<EndGameOnCollide>,

	ComponentFactory::Registrar<PlayerUI>,
	ComponentFactory::Registrar<PlayerMover>,
	ComponentFactory::Registrar<MoneyCounter>,
	ComponentFactory::Registrar<PlayerScore>,
	ComponentFactory::Registrar<MimicFinder>> registrar;
