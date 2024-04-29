#include "CollectorGame.h"

#include "Inventory.h"
#include "Item.h"
#include "PlayerCharacter.h"
#include "Tile.h"
#include "ConsoleManip.h"

#include <conio.h>
#include <iostream>
#include <random>
#include <time.h>
#include <memory>

CollectorGame::CollectorGame(size_t width, size_t height)
	: m_width{ width }
	, m_height{ height }
	, m_currentMode{Mode::kWorld}
	, m_playerInventory{this}
	, m_player{&m_playerInventory}
{
	m_Tiles.reserve(width * height);
	int index = 0;
	for (size_t y = 0; y < height; ++y)
	{
		for (size_t x = 0; x < width; ++x)
		{
			m_Tiles.emplace_back( x,y );
			++index;
		}
	}
}

CollectorGame::~CollectorGame()
{
	// EMPTY
}

static char PromptAndGetChar(const std::string& prompt, std::initializer_list<char> charList)
{
	char input;
	for (;;)
	{
		std::cout << (prompt);
		input = (char)tolower(_getch());
		for (auto& it : charList)
		{
			if (input == tolower(it))
				return input;
		}
	}
}

void UseBomb(Item* pItem)
{
	std::cout << "The bomb seems to be filled without enough plastic explosive to level buildings\n"
		<< "Using the bomb will explode all near walls.\n"
		<< "Would you like to use the bomb?, press E again to use the bomb'\n";
	int input = tolower(_getch());
	
	if (input != 'e')
		return;
	std::cout << "The bomb was made of cake, nothing happens.\n";
}

///////////////////////////////////////////////////////////////
// Plays the game.
///////////////////////////////////////////////////////////////
void CollectorGame::Play()
{
	SetTile( &m_Tiles[0], &m_player);

	Item items[]{
		  {'$', "Twenty-Dollar Bill", "A bill of paper money.",
			[](Item*) {std::cout << "The bill looks quite.. stretchy, feels a bit like fruit leather\n"; } }

		, {'^', "Key", "A nondescript brass key.",
			[](Item*) {std::cout << "On further inspection, the key is actually a piece of chocolate.\nQuite Useless.\n"; } }
		
		, {'&', "Sleeping Bag", "A six-foot cocoon of warm cloth.",
			[](Item*) {std::cout << "This cocoon of warm cloth, is actually a piece of cotton candy."
						<<"\nNot reccommened to actually sleep in\n"; } }
		
		, {'!', "Knife" , "Everyday knife used in the kitchen.",
			[](Item*) {std::cout << "Upon testing the knife, cracks have formed, and the handle seems to made of marshmellow\n"
						<< "Its probably better to not touch this anymore\n"; }}
		
		, {'*', "Bomb" , "Blows up all walls within 1 tile.", &UseBomb }
	};
	int itemCount = (int)std::size(items);

	srand((unsigned)time(nullptr));

	for (size_t i = 0; i < itemCount; ++i)
	{
		for(;;)
		{
			size_t randX = rand() % m_width;
			size_t randY = rand() % m_height;
			size_t index = randX + randY * m_width;
			Tile* pTile = &m_Tiles[index];
			if (pTile->GetContents() == nullptr)
			{
				SetTile(pTile, &items[i]);
				break;
			}
		}
	}

	std::cout << "wasd to move, i to open inventory, e to use, q to drop.\n";

	while (true)
	{
		switch (m_currentMode)
		{
		case Mode::kWorld: ProcessWorldMode();	break;
		case Mode::kInventory: ProcessInventoryMode(); break;
		}
	}
}

bool CollectorGame::DropItem(Item* pItem)
{
	using enum Direction;
	size_t currentX = m_player.GetTile()->GetX();
	size_t currentY = m_player.GetTile()->GetY();

	//randomize directions
	Direction directions[(int)kCount]{ kUp, kDown, kLeft, kRight };
	for (Direction* ptr = directions; ptr != &directions[(int)kCount]; ++ptr)
	{
		int newIndex = rand() % 4;
		Direction temp = directions[newIndex];
		directions[newIndex] = *ptr;
		*ptr = temp;
	}

	int nextX = -1;
	int nextY = -1;
	for(Direction& direction : directions)
	{
		int targetX = currentX;
		int targetY = currentY;
		switch (direction)
		{
		case kUp:	 targetY += -1; break;
		case kDown:	 targetY +=  1; break;
		case kRight: targetX +=  1; break;
		case kLeft:	 targetX += -1; break;
		}

		if (InBounds(targetX, targetY) && TileIsEmpty(targetX, targetY))
		{
			nextX = targetX;
			nextY = targetY;
			break;
		}
	} 
	// couldnt find a good location to place the tile
	if (nextX == -1 && nextY == -1)
		return false;

	Tile* pTargetTile = &m_Tiles[ (nextY * m_width) + nextX];
	SetTile(pTargetTile, pItem);
	return true;
}

///////////////////////////////////////////////////////////////
// Sets a Tile's content, and sets the content's Tile.
///////////////////////////////////////////////////////////////
void CollectorGame::SetTile(Tile* pTile, GameObject* pObject)
{
	if(pTile != nullptr)
		pTile->SetContents(pObject);

	if(pObject != nullptr)
		pObject->SetTile(pTile);
}

///////////////////////////////////////////////////////////////
// Draws and updates the main game.
///////////////////////////////////////////////////////////////
void CollectorGame::ProcessWorldMode()
{
	ConsoleManip::ClearConsole();
	ConsoleManip::ChangeConsoleFormatting(CSR_SHOW_OFF);

	int index = 0;
	for (size_t y = 0; y < m_height; ++y)
	{
		for (size_t x = 0; x < m_width; ++x)
		{
			m_Tiles[index].Draw();
			++index;
		}
		std::cout << '\n';
	}

	char input = (char)_getch();
	switch (input)
	{
	case 'w': MovePlayer(0, -1); break;
	case 's': MovePlayer(0, +1); break;
	case 'a': MovePlayer(-1, 0); break;
	case 'd': MovePlayer(+1, 0); break;
	case 'i': m_currentMode = Mode::kInventory; break;
	}
}

///////////////////////////////////////////////////////////////
// Moves the player dx (horizontal) and dy (vertical).
///////////////////////////////////////////////////////////////
void CollectorGame::MovePlayer(int dx, int dy)
{
	Tile* pCurrentTile = m_player.GetTile();
	size_t targetX = pCurrentTile->GetX() + dx;
	size_t targetY = pCurrentTile->GetY() + dy;


	if ( ! InBounds((int)targetX , (int)targetY) )
		return;

	Tile* pTargetTile = &m_Tiles[targetX + targetY * m_width];
	pTargetTile->OnEnter(&m_player);

	SetTile(pCurrentTile, nullptr);
	SetTile(pTargetTile, &m_player);
}

bool CollectorGame::InBounds(int x, int y) const
{
	if (x < 0 || x >= (int)m_width)
		return false;

	if (y < 0 || y >= (int)m_height)
		return false;

	return true;
}

bool CollectorGame::TileIsEmpty(int x, int y) const
{
	if ( m_Tiles[(y * m_width) + x].GetContents() )
		return false;
	return true;
}

///////////////////////////////////////////////////////////////
// Draws and executes the inventory screen.
///////////////////////////////////////////////////////////////
void CollectorGame::ProcessInventoryMode()
{
	m_playerInventory.Draw();
	m_playerInventory.ProcessInput();
}
