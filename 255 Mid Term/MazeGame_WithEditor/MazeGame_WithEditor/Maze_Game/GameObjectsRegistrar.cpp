
#include <tuple>
#include "GameObjectFactory.h"

#include "Player.h"
#include "MapTiles.h"
#include "Enemies.h"

// this tuple contains ever Registrar object that is being created 
// in order to register a subclass into the factory.
// 
// it is in this CPP file to keep anyone from attempting to acess them, and keep every
// class that has been registered in this one file.
// 
// I dont dont know why the tuple was used, it was a reccomendation from Rez about the factory class,

static std::tuple<
	GameObjectFactory::Registrar<Player>,

	GameObjectFactory::Registrar<EmptyTile>,
	GameObjectFactory::Registrar<TrapTile>,
	GameObjectFactory::Registrar<WallTile>,
	GameObjectFactory::Registrar<ExitTile>,

	GameObjectFactory::Registrar<HorizontalEnemy>,
	GameObjectFactory::Registrar<VerticalEnemy>,
	GameObjectFactory::Registrar<RandEnemy>> registrar;

/*
	kWall
	kExit
	kEmpty
	kPlayer
	kTrap
	kHorizontalEnemy
	kVerticalEnemy
	kRandEnemy
*/