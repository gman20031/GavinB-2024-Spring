#pragma once

#include <utility>

#include "ActorFactory.h"

class World
{
	using TileType = ActorFactory::FactoryPrototype;
	using TileProbability = std::pair<int, TileType>;
	static constexpr size_t kPlayerStartingHealth = 10;

	inline static const TileProbability s_tileProbabilities[(int)TileType::kCount]
	{
		{800, TileType::kEmptyTile},
		{75, TileType::kBombTile},
		{75, TileType::kTreasureTile},
		{50, TileType::kMimicTile},
		{5 , TileType::kTeleporterTile},
	};

	int m_width, m_height, m_length;
	std::vector<Actor::Position_t> m_EntityStartPositions;
	std::vector< Actor* > m_pAllEntities;

	Actor* m_pPlayer;
	Actor** m_ppGrid;
	bool m_gameOver;

private:
	void PopulateWorld(int maxProbability);
	void KillOutOfBounds(Actor* entity) const;

	size_t Position_tToIndex(Actor::Position_t pos) const;
	Actor* CreateActorFromType(TileType type, int x, int y);
	Actor* CreateTwoTeleporters(int x, int y);
	TileType GetRandomTileType(int maxProbability);
public:
	World();
	~World();

	Actor* GetPlayerPointer() { return m_pPlayer; }
	Actor* GetTileAt(int x, int y);
	Actor* GetTileAt(Vector2d<int> position);

	// initialization
	void Init(int width, int height);
	void CreatePlayer(int x = 0, int y = 0);
	void GenerateEnemies(size_t amount);
	void GenerateWorld();
	
	// play
	void UpdateTile(Vector2d<int> tilePosition);
	const std::vector< Actor* >& GetEntityVector() const { return m_pAllEntities; }

	// update
	void Draw() const;
	void Update();

	// end
	void EndGame();
	bool IsGameOver() const { return m_gameOver; }
};
