#include "World.h"

#include "../System/ConsoleManip.h"
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

Actor* World::GetTileAt(int x, int y)
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
}

void World::CreatePlayer(int x, int y)
{
	assert(x >= 0 && x < m_width);
	assert(y >= 0 && y < m_height);
	//m_pPlayer = new Player(x, y, this);
	int playerIndex = (y * m_width) + x;
	m_entityStartIndecies.emplace_back(playerIndex);
}

void World::GenerateEnemies(size_t amount)
{
}

void World::GenerateWorld()
{
}

void World::ProcessEntity(Actor* entity)
{
}

void World::Draw()
{
}

void World::Update()
{
}

void World::EndGame()
{
}
