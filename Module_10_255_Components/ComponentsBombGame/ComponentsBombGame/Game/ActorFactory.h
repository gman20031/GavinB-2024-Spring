#pragma once

#include "../Engine/Actor.h"
#include "World.h"

enum class FactoryPrototypes
{
	kEmptyTile,
	kBombTile,
	kMimicTile,
	kExitTile,
	kTreasureTile,
	kTeleporterTile,
	kDirectEnemy,
	kRandomEnemy,
	kPlayer,
	kCount,
};

static Actor emptyTile;
	//	Renderer( '.' )
	//+ nothing
static Actor bombTile;
	//	Renderer( '*' )
	//+ Explode on collide
static Actor mimicTile;
	//	Renderer( '$' )
	//+ Explode on collide
static Actor exitTile;
	//	Renderer( 'H' )
	//+ End on collide
static Actor treasureTile;
	//	Renderer( '$' )
	//+ Money on collide
static Actor teleporterTile;
	//	Renderer( '&' )
	//+ Teleport on collide
static Actor directEnemy;
	//	Renderer( '!' )
	//+ Teleport on collide
static Actor randomEnemy;
	//	
static Actor player;

class ActorFactory
{

};
