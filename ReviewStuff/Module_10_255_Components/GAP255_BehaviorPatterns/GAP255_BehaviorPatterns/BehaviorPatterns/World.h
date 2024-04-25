// World.h
#pragma once

#include "TileFactories.h"

#include <utility>

class Tile;
class Player;
class Enemy;
class Entity;

class World
{
	using TileType = TileFactory::TileType;
	using TileProbability = std::pair<int, TileFactory::TileType>;

    inline static const TileProbability s_tileProbabilities[(int)TileType::kCount]
	{
		{800, TileType::kEmpty},
		{75, TileType::kBomb},
		{75, TileType::kTreasure},
		{50, TileType::kMimic},
		{5 , TileType::kTeleporter},
	};
    
    int m_width, m_height;
	std::vector< int > m_EntityStartIndecies;
	std::vector< Enemy* > m_allEnemies;
	Player* m_pPlayer;
	Tile** m_ppGrid;
    bool m_gameOver;

public:
	World();
	~World();

	Player* GetPlayerPointer() { return m_pPlayer; }
	Tile* GetTileAt(int x, int y);

	// initialization
	void Init(int width, int height);
	void CreatePlayer(int x = 0, int y = 0);
	void GenerateEnemies(size_t amount);
	void GenerateWorld();
	void ProcessEntity(Entity* entity);

	// update
	void Draw();
	void Update();

    // end
    void EndGame();
    bool IsGameOver() const { return m_gameOver; }
};

