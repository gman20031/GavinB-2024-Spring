#pragma once

#include <utility>

#include "../engine/Actor.h"

enum class TileAppearances
{
	kEmpty = '.',
	kBomb = '*',
	kUsedBomb = '#',
	kExit = 'H',
	kTreasure = '$',
	kTeleporter = '&',
	kCount
};

class World
{
	using TileType = AllTiles;
	using TileProbability = std::pair<int, TileType>;

	inline static const TileProbability s_tileProbabilities[(int)TileType::kCount]
	{
		{800, TileType::kEmpty},
		{75, TileType::kBomb},
		{75, TileType::kTreasure},
		{50, TileType::kMimic},
		{5 , TileType::kTeleporter},
	};

	int m_width, m_height;
	std::vector<int> m_entityStartIndecies;
	friend class Basic2dCollider;
	std::vector< Actor* > m_allEnemies;
	std::vector<Actor*> m_allActors;

	Actor* m_pPlayer;
	Actor** m_ppGrid;
	bool m_gameOver;
public:
	World();
	~World();

	Actor* GetPlayerPointer() { return m_pPlayer; }
	Actor* GetTileAt(int x, int y);

	// initialization
	void Init(int width, int height);
	void CreatePlayer(int x = 0, int y = 0);
	void GenerateEnemies(size_t amount);
	void GenerateWorld();
	void ProcessEntity(Actor* entity);

	// update
	void Draw();
	void Update();

	// end
	void EndGame();
	bool IsGameOver() const { return m_gameOver; }
};
