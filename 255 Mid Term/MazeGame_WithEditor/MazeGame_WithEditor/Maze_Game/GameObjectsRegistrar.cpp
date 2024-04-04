
#include <tuple>
#include "GameObjectFactory.h"

#include "Player.h"
#include "MapTiles.h"
#include "Enemies.h"
#include "DoorTiles.h"
#include "Items.h"

// this tuple contains ever Registrar object that is being created 
// in order to register a subclass into the factory.
// 
// it is in this CPP file to keep anyone from attempting to acess them, and keep every
// class that has been registered in this one file.
// 
// I dont dont know why the tuple was used, it was a reccomendation from Rez about the factory class,

/*
* Currently Registered Objects
	kBase = '\0',
	kEmpty = '.',
	kWall = '#',
	kExit = 'X',
	kPlayer = '@',
	kTrap = '0',
	kHorizontalEnemy = '-',
	kVerticalEnemy = '|',
	kRandomEnemy = '&',
	kDirectEnemy = '$',
	kClearDoor = '~',
	kHiddenDoor = 'D',
	kSword Item = '+'
*/

static std::tuple<
	GameObjectFactory::Registrar<Player>,

	GameObjectFactory::Registrar<EmptyTile>,
	GameObjectFactory::Registrar<TrapTile>,
	GameObjectFactory::Registrar<WallTile>,
	GameObjectFactory::Registrar<ExitTile>,
	GameObjectFactory::Registrar<ToggleTile>,

	GameObjectFactory::Registrar<HorizontalEnemy>,
	GameObjectFactory::Registrar<VerticalEnemy>,
	GameObjectFactory::Registrar<RandEnemy>,
	GameObjectFactory::Registrar<DirectEnemy>,

	GameObjectFactory::Registrar<ClearDoor>,
	GameObjectFactory::Registrar<HiddenDoor>,
	
	GameObjectFactory::Registrar<Sword>>registrar;
