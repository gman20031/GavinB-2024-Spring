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
	m_allActors.emplace_back(m_pPlayer);
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
		m_allEnemies.emplace_back(newEnemy);
		m_allEnemies.back()->Init(this , {x,y} );
		m_allActors.emplace_back(newEnemy);

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
// Generates an empty tile at the starting location of every
// entity currenlty contained in m_EntityStartPositions
///////////////////////////////////////////////////////////////
void World::ClearEntityStartLocations()
{
	for (auto& position : m_EntityStartPositions)
	{
		Actor* temp = ActorFactory::CreateEmptyTile(this, position);
		m_ppGrid[Position_tToIndex(position)] = temp;
	}
}

///////////////////////////////////////////////////////////////
// Generates an empty tile at the first and last positions
///////////////////////////////////////////////////////////////
void World::CreateStartAndEndTiles()
{
	m_ppGrid[0] = ActorFactory::CreateEmptyTile(this, { 0,0 });
	m_ppGrid[m_length - 1] = ActorFactory::CreateExitTile(this, { m_width - 1,m_height - 1 });
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
	case kTeleporterTile:	return CreateTwoTeleporters(x, y);
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

	ClearEntityStartLocations();
	CreateStartAndEndTiles();
	PopulateWorld(maxProbability);
}




///////////////////////////////////////////////////////////////
// Calls the render component of every actor in the world.
// if a entity actor is at a position, it is rendered and the
// tile is not
///////////////////////////////////////////////////////////////
void World::Draw() const
{
	ConsoleManip::ClearConsole();
	m_pPlayer->GetComponent<PlayerUI>()->DrawUI();

	for (int y = 0; y < m_height; ++y)
	{
		for (int x = 0; x < m_width; ++x)
		{
			bool stop = false;
			for (auto& enemy : m_allEnemies)
			{
				//enemy->GetPosition().x
				if (enemy->GetPosition().x == x and enemy->GetPosition().y == y)
				{
					enemy->GetComponent<BasicRenderer>()->Render();
					stop = true;
				}
			}
			if (stop)
				continue;
			if (m_pPlayer and m_pPlayer->GetPosition().x == x and m_pPlayer->GetPosition().y == y)
				m_pPlayer->GetComponent<BasicRenderer>()->Render();
			else
			{
				int index = (y * m_width) + x;
				m_ppGrid[index]->GetComponent<BasicRenderer>()->Render();
			}
		}
		std::cout << std::endl;
	}

}

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

void World::UpdateTile(Vector2d<int> tilePosition)
{
	Actor* pTile = GetTileAt(tilePosition);
	if (pTile)
		pTile->Update();
}

void World::Update()
{
	m_pPlayer->Update();
	KillOutOfBounds(m_pPlayer);
	Actor* actor = nullptr;
	for (auto it = m_allEnemies.begin(); it != m_allEnemies.end(); /*EMPTY*/ )
	{
		actor = *it;
		actor->Update();
		KillOutOfBounds(actor);
		if (actor->GetComponent<HealthTracker>()->IsDead())
		{
			delete actor;
			it = m_allEnemies.erase(it);
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
