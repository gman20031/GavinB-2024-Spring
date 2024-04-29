#pragma once

#include "PlayerCharacter.h"
#include "Item.h"

class Tile;

class CollectorGame
{
public:
	enum class Direction
	{
		kUp,
		kDown,
		kRight,
		kLeft,
		kCount,
	};

	enum class Mode
	{
		kWorld,
		kInventory
	};

private:
	const size_t m_width;
	const size_t m_height;
	std::vector<Tile> m_Tiles;

	Mode m_currentMode;
	Inventory m_playerInventory;
	PlayerCharacter m_player;

public:
	CollectorGame(size_t w, size_t h);
	~CollectorGame();

	void Play();
	void SetMode(Mode mode) { m_currentMode = mode; }
	bool DropItem(Item* pItem);

private:
	static void SetTile(Tile* pTile, GameObject* pObject);

	void MovePlayer(int dx, int dy);
	bool InBounds(int x, int y) const;
	bool TileIsEmpty(int x, int y) const;

	void ProcessWorldMode();
	void ProcessInventoryMode();
};

