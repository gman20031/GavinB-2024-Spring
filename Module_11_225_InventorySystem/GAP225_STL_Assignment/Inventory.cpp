#include "Inventory.h"

#include "CollectorGame.h"
#include "ConsoleManip.h"

#include <conio.h>
#include <iostream>
#include <algorithm>

Inventory::Inventory(CollectorGame* pGame)
	: m_pGame{pGame}
	, m_inventoryCursorX(0), m_inventoryCursorY(0)
{
}

///////////////////////////////////////////////////////
// This should draw the contents of the inventory.
///////////////////////////////////////////////////////
void Inventory::Draw() const
{
	ConsoleManip::ClearConsole();
	ConsoleManip::ChangeConsoleFormatting( CSR_BLINKING_ON VT_ESC CSR_SHAPE_BLINK_UNDER);
	std::cout << VT_ESC CSR_SHOW_ON;

	std::cout << "INVENTORY" << std::endl;
	
	for (size_t i = 0; i < m_pStoredItems.size(); ++i)
	{
		if (i % kInventoryWidth == 0 && i != 0)
			std::cout << '\n';

		m_pStoredItems[i]->Draw();

		if ((i + 1) % kInventoryWidth != 0)
			std::cout << " | ";
	}

	std::cout << '\n';
	PrintSelectedDescription();

	ResetConsoleCursorPos();
}

void Inventory::MoveCursor(int deltaX, int deltaY)
{
	m_inventoryCursorX += deltaX;
	m_inventoryCursorY += deltaY;

	m_inventoryCursorX = std::clamp(m_inventoryCursorX, 0, (int)(kInventoryWidth - 1));
	m_inventoryCursorY = std::clamp(m_inventoryCursorY, 0, ((int)m_pStoredItems.size()-1) / kInventoryWidth);
}


void Inventory::ResetConsoleCursorPos() const
{
	// set Cursor is 1 indexed -- kinda
	int cursor_xPos = (m_inventoryCursorX * (kInventoryWidth + 1)) + 1;
	int cursor_yPos = (m_inventoryCursorY + kTopBuffer) + 1;
	ConsoleManip::SetCursorPosition(cursor_xPos , cursor_yPos );
}

void Inventory::UseSelected()
{
	if (m_pStoredItems.empty())
		return;

	ConsoleManip::ClearConsole();
	size_t index = CursorIndex();

	if (index < m_pStoredItems.size() )
	{
		m_pStoredItems[index]->Use();
		ConsoleManip::Pause();
	}
	MoveCursor(0, 0);
}

void Inventory::DropSelected()
{
	if (m_pStoredItems.empty())
		return;
	
	auto itemIt = m_pStoredItems.begin() + CursorIndex();
	if (m_pGame->DropItem(*itemIt))
		m_pStoredItems.erase(itemIt);
	else
	{
		ConsoleManip::ClearConsole();
		std::cout << "No spot found to drop item\n";
		ConsoleManip::Pause();
	}
	MoveCursor(0, 0);
}

void Inventory::PrintSelectedDescription() const
{
	size_t index = CursorIndex();
	if ( !m_pStoredItems.empty() && index < m_pStoredItems.size())
	{
		m_pStoredItems[index]->PrintDescription();
	}
}

size_t Inventory::CursorIndex() const
{
	return (size_t)(m_inventoryCursorY * kInventoryWidth) + m_inventoryCursorX;
}

///////////////////////////////////////////////////////
// Allow the user to input commands, then execute them.
///////////////////////////////////////////////////////
void Inventory::ProcessInput()
{
	switch (_getch())
	{
	case 'i': m_pGame->SetMode(CollectorGame::Mode::kWorld); break;
	case 'd': MoveCursor(1, 0); break;
	case 'w': MoveCursor(0, -1); break;
	case 's': MoveCursor(0, 1); break;
	case 'a': MoveCursor(-1, 0); break;
	case 'e': UseSelected(); break;
	case 'q': DropSelected(); break;
	}
}

///////////////////////////////////////////////////////
// Adds pItem to this inventory.
///////////////////////////////////////////////////////
void Inventory::AddItem(Item* pItem)
{
	m_pStoredItems.emplace_back(pItem);
}
