
#include <tuple>
#include "GameObjectFactory.h"

#include "Player.h"
#include "MapTiles.h"
#include "Enemies.h"

static std::tuple<
	GameObjectFactory::Registrar<Player>,

	GameObjectFactory::Registrar<EmptyTile>,
	GameObjectFactory::Registrar<TrapTile>,
	GameObjectFactory::Registrar<WallTile>,
	GameObjectFactory::Registrar<ExitTile>,

	GameObjectFactory::Registrar<HorizontalEnemy>,
	GameObjectFactory::Registrar<VerticalEnemy>> registrar;

/*
	kWall
	kExit
	kEmpty
	kPlayer
	kTrap
	kHorizontalEnemy
	kVerticalEnemy
*/