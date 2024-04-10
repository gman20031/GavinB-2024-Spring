// World.h
#pragma once

#include <utility>
#include "TileFactories.h"

class Tile;
class Player;

class World
{
	using _TileType = TileFactory::TileType;
    typedef std::pair<int, TileFactory::TileType> TileProbability;

    inline static const TileProbability s_tileProbabilities[(int)_TileType::kCount]
	{
		World::TileProbability(800, _TileType::kEmpty),
		World::TileProbability(75, _TileType::kBomb),
		World::TileProbability(75, _TileType::kTreasure),
		World::TileProbability(50, _TileType::kMimic),
	};
    
    int m_width, m_height;
	Tile** m_ppGrid;
	Player* m_pPlayer;
    bool m_gameOver;

public:
	World();
	~World();

	// initialization
	void Init(int width, int height);
	void CreatePlayer(int x = 0, int y = 0);
	void GenerateWorld();

	// update
	void Draw();
	void Update();

    // end
    void EndGame();
    bool IsGameOver() const { return m_gameOver; }
};

