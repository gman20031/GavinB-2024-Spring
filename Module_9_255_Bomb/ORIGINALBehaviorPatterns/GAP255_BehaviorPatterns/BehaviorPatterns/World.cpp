// World.cpp
#include "World.h"
#include "Tile.h"
#include "Player.h"

#include "FloorTile.h"
#include "TreasureTile.h"
#include "BombTile.h"
#include "MimicTile.h"
#include "EndTile.h"

#include <iostream>
#include <assert.h>

using std::cout;
using std::endl;

const World::TileProbability World::s_tileProbabilities[(int)TileType::k_numTiles] =
{
    World::TileProbability(800, TileType::k_floor),
    World::TileProbability(75, TileType::k_bomb),
    World::TileProbability(75, TileType::k_treasure),
    World::TileProbability(50, TileType::k_mimic),
};

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
	m_pPlayer = new Player(x, y);
}

void World::GenerateWorld()
{
    // calculate the max probability
    int maxProbability = 0;
    for (int i = 0; i < (int)TileType::k_numTiles; ++i)
    {
        maxProbability += s_tileProbabilities[i].first;
    }

    // create the start and end tiles
    int lastIndex = (m_width * m_height) - 1;
    m_ppGrid[lastIndex] = new EndTile;  // special tile for ending the level; there is only one of these
    m_ppGrid[0] = new FloorTile;  // guarantee that the starting location is open

    // guarantee at least one mimic
    int randomTile = (rand() % (lastIndex - 1)) + 1;
    assert(m_ppGrid[randomTile] == nullptr);  // if this fires, it means our math is wrong
    m_ppGrid[randomTile] = new MimicTile;

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
            roll -= s_tileProbabilities[probabilityIndex].first;
            if (roll < 0)
                break;
            ++probabilityIndex;
        }

        assert(probabilityIndex >= 0 && probabilityIndex < (int)TileType::k_numTiles);

		switch (s_tileProbabilities[probabilityIndex].second)
		{
            case TileType::k_floor:
                m_ppGrid[tileIndex] = new FloorTile;
				break;

            case TileType::k_bomb:
                m_ppGrid[tileIndex] = new BombTile;
				break;

            case TileType::k_treasure:
                m_ppGrid[tileIndex] = new TreasureTile;
				break;

            case TileType::k_mimic:
                m_ppGrid[tileIndex] = new MimicTile;
                break;

			default:
                cout << "ERROR: Invalid type type.\n";
                break;
		}
	}
}

void World::Draw()
{
    system("cls");

    m_pPlayer->DrawUi();

	for (int y = 0; y < m_height; ++y)
	{
		for (int x = 0; x < m_width; ++x)
		{
			if (m_pPlayer && m_pPlayer->GetX() == x && m_pPlayer->GetY() == y)
			{
				m_pPlayer->Draw();
			}
			else
			{
				int index = (y * m_width) + x;
				m_ppGrid[index]->Draw();
			}
		}
		cout << endl;
	}
}

void World::Update()
{
    if (!m_pPlayer->Update())
    {
        m_pPlayer->Kill();  // ending the game prematurely does not result in a win
        EndGame();
        return;
    }

    int x = m_pPlayer->GetX();
    int y = m_pPlayer->GetY();

    // this is a death arena, so check to see if we went over the edge of the world
    if (x < 0 || y < 0 || x >= m_width || y >= m_height)
    {
        m_pPlayer->Kill();
        EndGame();
        return;
    }

    // process the tile the player is on
    int index = (y * m_width) + x;
    m_ppGrid[index]->OnEnter(m_pPlayer);
}

void World::EndGame()
{
    if (!m_pPlayer->IsDead())
    {
        cout << "\n\nYou won!\n\n";
        cout << "Your final score is: " << m_pPlayer->CalculateScore() << "\n";
    }
    else
    {
        cout << "\n\nYou have died.\n\n";
    }

    m_gameOver = true;
}
