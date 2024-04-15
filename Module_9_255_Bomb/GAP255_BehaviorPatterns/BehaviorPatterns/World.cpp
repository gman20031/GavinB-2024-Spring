// World.cpp
#include "World.h"
#include "Tile.h"
#include "Player.h"
#include "Console.h"
#include "EnemyFactory.h"

#include <assert.h>

World::World()
	: m_ppGrid(nullptr)
	, m_width(0)
	, m_height(0)
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

Tile* World::GetTileAt(int x, int y)
{
	int index = (m_width * y) + x;
	if (x >= m_width or y >= m_height
	 or x < 0 or y < 0)
		return nullptr;
	return m_ppGrid[index];
}

void World::Init(int width, int height)
{
	// if we have a grid, destroy it
	if (m_ppGrid)
	{
        for (int i = 0; i < m_width * m_height; ++i)
        {
            delete m_ppGrid[i];
        }
        delete[] m_ppGrid;
        m_ppGrid = nullptr;
    }

	// create and fill the grid with nothing
	m_ppGrid = new Tile*[width*height];
	for (int i = 0; i < width*height; ++i)
	{
		m_ppGrid[i] = nullptr;
	}

	// set the width & height
	m_width = width;
	m_height = height;
}

void World::CreatePlayer(int x, int y)
{
	assert(x >= 0 && x < m_width);
	assert(y >= 0 && y < m_height);
	m_pPlayer = new Player(x, y, this);
	int playerIndex = (y * m_width) + x;
	m_EntityStartIndecies.emplace_back(playerIndex);
}

void World::GenerateEnemies(size_t amount)
{
	int lastIndex = (m_width * m_height) - 1;

	for (size_t i = 0; i < amount; ++i)
	{
		int randomIndex = (rand() % (lastIndex - 1)) + 1;
		m_EntityStartIndecies.emplace_back(randomIndex);
		EnemyMover::MoveType type = (EnemyMover::MoveType)(rand() % 2); // randomize enemy

		m_allEnemies.emplace_back( EnemyFactory::Create(type) );
		int x = randomIndex % m_width;
		int y = randomIndex / m_width;
		m_allEnemies.back()->Init(x, y, this);
	}
}

void World::GenerateWorld()
{
	using enum TileType;

    // calculate the max probability
    int maxProbability = 0;
    for (int i = 0; i < (int)kCount; ++i)
	{
		maxProbability += s_tileProbabilities[i].first;
	}

	// guarantee that the starting locations for all entities are open
	for (auto& index : m_EntityStartIndecies)
	{
		m_ppGrid[index] = TileFactory::Create(kEmpty);
	}

	// create the start and end tiles
	int lastIndex = (m_width * m_height) - 1;
	m_ppGrid[lastIndex] = TileFactory::Create(kExit);  // special tile for ending the level; there is only one of these

	// guarantee at least one mimic
	int randomTile = (rand() % (lastIndex - 1)) + 1;
	assert(m_ppGrid[randomTile] == nullptr);  // if this fires, it means our math is wrong
	m_ppGrid[randomTile] = TileFactory::Create(kMimic);

	// populate the rest of the world
	for (int tileIndex = 1; tileIndex < (m_width * m_height) - 1; ++tileIndex)
	{
        // skip this tile if we've already set it
        if (m_ppGrid[tileIndex] != nullptr)
            continue;

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

		if (s_tileProbabilities[probabilityIndex].second == kTeleporter)
		{
			// required to make in pair
			int randomX = rand() % m_width;
			int randomY = rand() % m_height;
			int randomIndex = (randomY * m_height) + randomX;
			int tileX = tileIndex % m_width;
			int tileY = tileIndex / m_width;
			m_ppGrid[tileIndex] = TileFactory::Create(kTeleporter, { randomX, randomY });
			m_ppGrid[randomIndex] = TileFactory::Create(kTeleporter, { tileX , tileY });
		}
		else
			m_ppGrid[tileIndex] = TileFactory::Create(s_tileProbabilities[probabilityIndex].second);

	}
}

void World::Draw()
{
	ConsoleClear();
    //system("cls");

    m_pPlayer->DrawUi();

	for (int y = 0; y < m_height; ++y)
	{
		for (int x = 0; x < m_width; ++x)
		{
			bool stop = false;
			for (auto& enemy : m_allEnemies)
			{
				if (enemy->GetX() == x and enemy->GetY() == y)
				{
					enemy->Draw();
					stop = true;
				}
			}
			if (stop)
				continue;
			if (m_pPlayer and m_pPlayer->GetX() == x and m_pPlayer->GetY() == y)
				m_pPlayer->DrawSelf();
			else
			{
				int index = (y * m_width) + x;
				m_ppGrid[index]->Draw();
			}
		}
		std::cout << std::endl;
	}
}

void World::ProcessEntity(Entity* entity)
{
	int x = entity->GetX();
	int y = entity->GetY();

	// this is a death arena, so check to see if we went over the edge of the world
	if (x < 0 or y < 0 or x >= m_width or y >= m_height)
	{
		entity->Kill();
		return;
	}

	int index = (y * m_width) + x;
	m_ppGrid[index]->OnEnter(entity);
}

void World::Update()
{
	m_pPlayer->Update();
	ProcessEntity(m_pPlayer);
	Entity* enemy;
	for (auto it = m_allEnemies.begin(); it != m_allEnemies.end(); )
	{
		enemy = *it;
		enemy->Update();
		ProcessEntity(enemy);

		if (enemy->GetX() == m_pPlayer->GetX()
		and enemy->GetY() == m_pPlayer->GetY())
			m_pPlayer->Kill();

		if (enemy->IsDead())
		{
			delete enemy;
			it = m_allEnemies.erase(it);
			continue;
		}
		++it;
	}

    if (m_pPlayer->IsDead())
    {
        EndGame();
        return;
    }
}

void World::EndGame()
{
    if (!m_pPlayer->IsDead())
    {
        std::cout << "\nYou won!\n";
        std::cout << "Your final score is: " << m_pPlayer->CalculateScore() << "\n";
    }
    else
    {
        std::cout << "\nYou have died.\n";
    }

    m_gameOver = true;
}
