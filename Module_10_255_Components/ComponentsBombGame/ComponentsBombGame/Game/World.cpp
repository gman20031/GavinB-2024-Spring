#include "World.h"

#include <assert.h>

#include "HealthTracker.h"
#include "PlayerComponents.h"
#include "TileComponents.h"
#include "../System/ConsoleManip.h"

World::World()
	: m_ppGrid(nullptr)
	, m_width(0)
	, m_height(0)
	, m_length(0)
	, m_pPlayer(nullptr)
	, m_gameOver(false)
{
	//
}

World::~World()
{
	for (int i = 0; i < m_width * m_height; ++i)
	{
		delete m_ppGrid[i];
	}
	delete[] m_ppGrid;
	m_ppGrid = nullptr;

	delete m_pPlayer;
	m_pPlayer = nullptr;
}
///////////////////////////////////////////////////////////////
// Retruns the Actor* contained at x,y
///////////////////////////////////////////////////////////////
Actor* World::GetTileAt(int x, int y)
{
	int index = (m_width * y) + x;
	if (x >= m_width or y >= m_height
		or x < 0 or y < 0)
		return nullptr;
	return m_ppGrid[index];
}

///////////////////////////////////////////////////////////////
// Retruns the Actor* contained at x,y
///////////////////////////////////////////////////////////////
Actor* World::GetTileAt(Vector2d<int> position)
{
	return GetTileAt(position.x, position.y);
}

///////////////////////////////////////////////////////////////
// Creates an empty world the size of width * height
///////////////////////////////////////////////////////////////
void World::Init(int width, int height)
{
	// if we have a grid, destroy it
	if (m_ppGrid)
	{
		for (int i = 0; i < m_width * m_height; ++i)	
			delete m_ppGrid[i];

		delete[] m_ppGrid;
		m_ppGrid = nullptr;
	}

	// create and fill the grid with nothing
	m_ppGrid = new Actor* [width * height];
	for (int i = 0; i < width * height; ++i)
	{
		m_ppGrid[i] = nullptr;
	}

	// set the width & height
	m_width = width;
	m_height = height;
	m_length = width*height;
}

///////////////////////////////////////////////////////////////
// Creates the player character and sets its location to x,y
///////////////////////////////////////////////////////////////
void World::CreatePlayer(int x, int y)
{
	assert(x >= 0 && x < m_width);
	assert(y >= 0 && y < m_height);
	m_pPlayer = ActorFactory::Createplayer(this, { x,y }, kPlayerStartingHealth);
	m_EntityStartPositions.emplace_back( x, y );
	m_pAllEntities.emplace_back(m_pPlayer);
}

///////////////////////////////////////////////////////////////
// Creates a number of randomized enemies specified by amount
///////////////////////////////////////////////////////////////
void World::GenerateEnemies(size_t amount)
{
	for (size_t i = 0; i < amount; ++i)
	{
		int x = 0;
		int y = 0;
		// generate X and Y again if first or last element
		do 
		{
			y = rand() % m_height;
			x = rand() % m_width;
		} while ( (x == 0 && y == 0) || (x == (m_height - 1) && y == (m_width - 1)) );

		m_EntityStartPositions.emplace_back(x, y);

		Actor* newEnemy = nullptr;
		switch (rand() % 2)
		{
		case 0: newEnemy = ActorFactory::CreateScaredEnemy(this, { x,y }); break;
		case 1: newEnemy = ActorFactory::CreateDirectEnemy(this, { x,y }); break;
		}
		m_pAllEntities.emplace_back(newEnemy);
		m_pAllEntities.back()->Init(this , {x,y} );

	}
}

///////////////////////////////////////////////////////////////
// returns the index value of m_ppGrid of a position
///////////////////////////////////////////////////////////////
size_t World::Position_tToIndex(Actor::Position_t pos) const
{
	return (size_t)((pos.y * m_width) + pos.x);
}

///////////////////////////////////////////////////////////////
// Randomizes a location and places a teleporter, then places
// a teleporter at x,y. And giving eachother the positions.
///////////////////////////////////////////////////////////////
Actor* World::CreateTwoTeleporters(int x, int y)
{
	// required to make in pair
	int randomX = rand() % m_width;
	int randomY = rand() % m_height;
	int randomIndex = (randomY * m_height) + randomX;

	auto randomizedTeleporter = ActorFactory::CreateTeleporterTile(this, { randomX,randomY });
	auto returnedTeleporter = ActorFactory::CreateTeleporterTile(this, { x,y });

	randomizedTeleporter->GetComponent<TeleportCollide>()->Init(returnedTeleporter->GetPosition());
	returnedTeleporter->GetComponent<TeleportCollide>()->Init(randomizedTeleporter->GetPosition());

	m_ppGrid[randomIndex] = randomizedTeleporter;
	return returnedTeleporter;
}

///////////////////////////////////////////////////////////////
// Randomizes a tile type through a weighted random table.
// then returns that type
///////////////////////////////////////////////////////////////
World::TileType World::GetRandomTileType(int maxProbability)
{
	int roll = rand() % maxProbability;
	int probabilityIndex = 0;
	while (true)
	{
		// I roll 870, reduce by 800. roll is > 0. go again with element 2,
		// roll is now 70, reduce by 75, roll is < 0. I rolled whatever is at element 2
		roll -= s_tileProbabilities[probabilityIndex].first;
		if (roll < 0)
			break;
		++probabilityIndex;
	}

	return s_tileProbabilities[probabilityIndex].second;
}

///////////////////////////////////////////////////////////////
// Generates a tile of type and places it at x,y
///////////////////////////////////////////////////////////////
Actor* World::CreateActorFromType(ActorFactory::FactoryPrototype type, int x, int y)
{
	using enum TileType;

	switch (type)
	{
	case kEmptyTile:		return ActorFactory::CreateEmptyTile(this, { x,y });
	case kBombTile:			return ActorFactory::CreateBombTile(this, { x,y });
	case kTreasureTile:		return ActorFactory::CreateTreasureTile(this, { x,y });
	case kMimicTile:		return ActorFactory::CreateMimicTile(this, { x,y });
	case kTeleporterTile:	return CreateTwoTeleporters(x, y); // teleporters require a linked position
	default: assert((false && "incorrect type passed into function")); 
	}
	return nullptr;
}

///////////////////////////////////////////////////////////////
// Randomly generates tiles for the entire world, any tile 
// already generated will be skipped.
///////////////////////////////////////////////////////////////
void World::PopulateWorld(int maxProbability)
{
	using enum ActorFactory::FactoryPrototype;
	// populate the rest of the world
	for (int tileIndex = 1; tileIndex < (m_width * m_height) - 1; ++tileIndex)
	{
		// skip this tile if we've already set it
		if (m_ppGrid[tileIndex] != nullptr)
			continue;

		int tileX = tileIndex % m_width;
		int tileY = tileIndex / m_width;

		auto tileType = GetRandomTileType(maxProbability);

		m_ppGrid[tileIndex] = CreateActorFromType(tileType, tileX, tileY);
	}
}

///////////////////////////////////////////////////////////////
// Generates tiles for the entire world , first and last tiles
// will always be empty, and entities will always stat on empty
// tiles
///////////////////////////////////////////////////////////////
void World::GenerateWorld()
{
	using enum TileType;

	// calculate the max probability
	int maxProbability = 0;
	for (int i = 0; i < (int)kCount; ++i)
	{
		maxProbability += s_tileProbabilities[i].first;
	}

	// creates empty tile at each enemy start locations
	for (auto& position : m_EntityStartPositions)
	{
		Actor* temp = ActorFactory::CreateEmptyTile(this, position);
		m_ppGrid[Position_tToIndex(position)] = temp;
	}

	// creates a tile at start and end
	m_ppGrid[0] = ActorFactory::CreateEmptyTile(this, { 0,0 });
	m_ppGrid[m_length - 1] = ActorFactory::CreateExitTile(this, { m_width - 1,m_height - 1 });

	PopulateWorld(maxProbability);
}


#include "../System/HighResTimer.h"
///////////////////////////////////////////////////////////////
// Calls the render component of every actor in the world.
// if a entity actor is at a position, it is rendered and the
// tile is not
///////////////////////////////////////////////////////////////
void World::Draw() const
{

	ConsoleManip::ChangeConsoleFormatting(CSR_SHOW_OFF VT_ESC TEXT_DEF);
	ConsoleManip::ClearConsole();

	int topBuffer = m_pPlayer->GetComponent<PlayerUI>()->DrawUI();

	// print entire grid of tiles
	for (size_t i = 1; i <= m_length; ++i) // starts at 1 to avoid (0 % width) == 0
	{
		m_ppGrid[i - 1]->Render(); // started at 1

		if (i % m_width == 0)
			std::cout << '\n';
	}

	for (Actor* entity : m_pAllEntities)
	{
		auto pos = entity->GetPosition();
		ConsoleManip::SetCursorPosition(pos.x + 1, pos.y + topBuffer + 1); // Cursor positioning is 1 indexed
		entity->Render();
	}

	ConsoleManip::SetCursorPosition( 1 , m_height + topBuffer + 1); // Cursor positioning is 1 indexed
}

///////////////////////////////////////////////////////////////
// Checks the location of the actor, if it is out of bounds,
// kills the actor
///////////////////////////////////////////////////////////////
void World::KillOutOfBounds(Actor* entity) const
{
	auto pos = entity->GetPosition();
	int x = pos.x;
	int y = pos.y;

	// this is a death arena, so check to see if we went over the edge of the world
	if (x < 0 or y < 0 or x >= m_width or y >= m_height)
	{
		entity->GetComponent<HealthTracker>()->Kill();
		return;
	}
}

///////////////////////////////////////////////////////////////
// Checks if there is a tile at tilePosition, if there is,
// updates that tile
///////////////////////////////////////////////////////////////
void World::UpdateTile(Vector2d<int> tilePosition)
{
	Actor* pTile = GetTileAt(tilePosition);
	if (pTile)
		pTile->Update();
}

///////////////////////////////////////////////////////////////
// Updates all entities in the scene, updating the tiles
// that the entities now stand on.
///////////////////////////////////////////////////////////////
void World::Update()
{
	m_pPlayer->Update();
	KillOutOfBounds(m_pPlayer);
	Actor* pActor = nullptr;
	for (auto it = m_pAllEntities.begin(); it != m_pAllEntities.end(); /*EMPTY*/)
	{
		pActor = *it;

		if (*pActor == *m_pPlayer)
		{
			++it;
			continue;
		}

		pActor->Update();
		KillOutOfBounds(pActor);
		if (pActor->GetComponent<HealthTracker>()->IsDead())
		{
			delete pActor;
			it = m_pAllEntities.erase(it);
			continue;
		}
		++it;
	}

	if (m_pPlayer->GetComponent<HealthTracker>()->IsDead())
	{
		EndGame();
		return;
	}
}

///////////////////////////////////////////////////////////////
// Sets the m_gameOver flag.
// if the player is dead, prints a loss
// if the plaer is alive, prints a win
///////////////////////////////////////////////////////////////
void World::EndGame()
{
	if (!m_pPlayer->GetComponent<HealthTracker>()->IsDead())
	{
		std::cout << "\nYou won!\n";
		std::cout << "Your final score is: " << m_pPlayer->GetComponent<PlayerScore>()->GetScore() << "\n";
	}
	else
	{
		std::cout << "\nYou have died.\n";
	}

	m_gameOver = true;
}
