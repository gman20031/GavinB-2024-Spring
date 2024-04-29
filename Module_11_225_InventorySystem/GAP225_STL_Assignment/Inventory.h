#pragma once

#include <vector>

class CollectorGame;
class Item;

///////////////////////////////////////////////////////////////
// This is where most of your work should be done.
// You are free to change the API in any way you like,
// as long as the functionality described is still implemented.
///////////////////////////////////////////////////////////////
class Inventory
{
private:
	static constexpr int kInventoryWidth = 3;
	static constexpr size_t kTopBuffer = 1; // numer of lines printed at the top of screen
	int m_inventoryCursorX, m_inventoryCursorY;

	std::vector<Item*> m_pStoredItems;
	CollectorGame* const m_pGame;

private:
	void MoveCursor(int deltaX, int deltaY);
	void ResetConsoleCursorPos() const;
	void UseSelected();
	void DropSelected();
	void PrintSelectedDescription() const;
	size_t CursorIndex() const;
public:
	Inventory(CollectorGame* pGame);

	void Draw() const;
	void ProcessInput();

	void AddItem(Item* pItem);
};

