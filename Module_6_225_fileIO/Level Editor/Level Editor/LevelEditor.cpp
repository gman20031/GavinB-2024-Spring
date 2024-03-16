#include "LevelEditor.h"

#include "Prompting.h"
#include "ConsoleManip.h"

#include <iostream>
#include <algorithm>

/////////////////////////// Level Editor Button /////////////////////////////////

void EditorButton::Interact(LevelEditor* editor) const
{

	//eww disgusting switch case, lots of work to add/remove
	switch (m_type)
	{
	case ButtonType::kCharacterChanger: 
		editor->m_selectedChar = m_charChanger;
		break;
	case ButtonType::kSaveLevel:
		editor->Save();
		break;
	case ButtonType::kSaveLevelAs:
		editor->SaveAs();
		break;
	case ButtonType::kLoadLevel:
		editor->Load();
		break;
	case ButtonType::kResize:
		editor->Resize();
		break;
	case ButtonType::kQuit:
		editor->m_keepEditing = false;
		break;
	}
}

void EditorButton::Draw() const
{
	std::cout << m_name;
}

/////////////////////////// Level Editor /////////////////////////////////

///////////////////////////////////////////////////////////////
// Initialization
///////////////////////////////////////////////////////////////

LevelEditor::LevelEditor()
	: m_keepEditing(true)
	, m_cursorLocation({ 0,0 })
	, m_inLevel(false)
	, m_selectedChar(kDefaultChar)
	, m_levelHeight(1)
	, m_levelWidth(1)
	, m_ppLevelArray(nullptr)
	//, m_pCurrentButton(nullptr)
{
	InitButtons();
	InitDefaultMap();
}

void LevelEditor::InitButtons()
{
	m_allButtons.push_back({
		 EditorButton{"Save",   ButtonType::kSaveLevel}
		,EditorButton{"Save As",ButtonType::kSaveLevelAs}
		,EditorButton{"Load",  ButtonType::kLoadLevel}
		,EditorButton{"Resize",   ButtonType::kResize}
		,EditorButton{"Quit",	ButtonType::kQuit}
	});
	m_allButtons.push_back({
		 EditorButton{"Wall",		ButtonType::kCharacterChanger, ObjectChar::kWall	}
		,EditorButton{"Trap",		ButtonType::kCharacterChanger, ObjectChar::kTrap	}
		,EditorButton{"Vert Enemy", ButtonType::kCharacterChanger, ObjectChar::kVerticalEnemy	}
		,EditorButton{"Horz Enemy", ButtonType::kCharacterChanger, ObjectChar::kHorizontalEnemy	}
		,EditorButton{"Exit",		ButtonType::kCharacterChanger, ObjectChar::kExit	}
		,EditorButton{"Player",		ButtonType::kCharacterChanger, ObjectChar::kPlayer	}
	});
}

void LevelEditor::InitDefaultMap()
{
	ChangeArraySize(m_levelWidth, m_levelHeight);
	FillLevel((char)kDefaultChar);
}

///////////////////////////////////////////////////////////////
// Char Array manipulation
///////////////////////////////////////////////////////////////

void LevelEditor::FillLevel(char fillChar)
{
	for (size_t y = 0; y < m_levelHeight; ++y)
	{
		for (size_t x = 0; x < m_levelWidth; ++x)
		{
			m_ppLevelArray[y][x] = fillChar;
		}
	}
}

void LevelEditor::DeleteLevelArray()
{
	for (size_t y = 0; y < m_levelHeight; ++y)
	{
		delete[] m_ppLevelArray[y];
	}
	delete[] m_ppLevelArray;
}




void LevelEditor::ChangeArraySize(int newWidth, int newHeight)
{
	if( m_ppLevelArray != nullptr )
	{
		DeleteLevelArray();
	}

	m_levelWidth = newWidth;
	m_levelHeight = newHeight;

	m_ppLevelArray = new char*[m_levelHeight];
	for (size_t y = 0; y < m_levelHeight; ++y)
	{
		m_ppLevelArray[y] = new char[m_levelWidth];
	}
}

///////////////////////////////////////////////////////////////
// Utility Button Functions
///////////////////////////////////////////////////////////////

static bool ConfirmChoice()
{
	char input = PromptAndGetChar("Are you sure?(y/n)", { 'y','n' });
	return(input == 'y');
}

void LevelEditor::Resize()
{
	if (!ConfirmChoice())
		return;
	int x = PromptAndGetInteger("enter X value, 0-64", 0, 64);
	int y = PromptAndGetInteger("enter Y value, 0-64", 0, 64);
	ChangeArraySize(x, y);
}

void LevelEditor::Save()
{
	ConsoleManip::ChangeConsoleColour(1);
}

void LevelEditor::SaveAs()
{
	ConsoleManip::ChangeConsoleColour(1);
}

void LevelEditor::Load()
{
	ConsoleManip::ChangeConsoleColour(1);
}

void LevelEditor::Quit()
{
	if (!ConfirmChoice())
		return;
	std::cout << "would you like to save? (y/n)" << '\n';
	if (PromptAndGetChar("Would you like to save?", { 'y','n' }) == 'y')
		Save();
	m_keepEditing = false;

}
///////////////////////////////////////////////////////////////
// input handling
///////////////////////////////////////////////////////////////

void LevelEditor::GetKeyInput()
{
	char input = (char)_getch();
	switch (input)
	{
	case (char)EditorControls::kInteract: Interact(); break;
	case (char)EditorControls::kUp: [[fallthrough]];
	case (char)EditorControls::kDown: [[fallthrough]];
	case (char)EditorControls::kLeft: [[fallthrough]];
	case (char)EditorControls::kRight:	MoveCursor(static_cast<EditorControls>(input)); break;
	default: return;
	}
}

void LevelEditor::Interact()
{
	if (m_inLevel)
		m_ppLevelArray[m_cursorLocation.y][m_cursorLocation.x] = (char)m_selectedChar;
	else
		m_allButtons[m_cursorLocation.y][m_cursorLocation.x].Interact(this);
}

Coordinates LevelEditor::MoveCursorToButtons(Coordinates newCursorLocation)
{
	newCursorLocation.y = (int)m_allButtons.size()- 1 ;
	newCursorLocation.x = std::clamp(newCursorLocation.x, 0, ((int)m_allButtons[newCursorLocation.y].size() - 1));
	m_inLevel = false;
	return newCursorLocation;
}

Coordinates LevelEditor::MoveCursorToLevel(Coordinates newCursorLocation)
{
	newCursorLocation.y = 0;
	newCursorLocation.x = std::clamp(newCursorLocation.x, 0, (m_levelWidth - 1));
	m_inLevel = true;
	return newCursorLocation;
}

void LevelEditor::MoveCursor(EditorControls direction)
{
	Coordinates newCursorLocation = m_cursorLocation;
	
	//Get next location
	switch (direction)
	{
	case EditorControls::kUp: newCursorLocation.y -= 1; break;
	case EditorControls::kDown: newCursorLocation.y += 1; break;
	case EditorControls::kLeft: newCursorLocation.x -= 1; break;
	case EditorControls::kRight: newCursorLocation.x += 1; break;
	}

	// Check if going out between buttons and level
	if (m_inLevel)
	{
		if (newCursorLocation.y < 0)
			newCursorLocation = MoveCursorToButtons(newCursorLocation);
		else
		{
			newCursorLocation.x = std::clamp(newCursorLocation.x, 0, (m_levelWidth - 1) );
			newCursorLocation.y = std::clamp(newCursorLocation.y, 0, (m_levelHeight - 1) );
		}
	}
	else if (!m_inLevel)
	{
		if (newCursorLocation.y > (int)(m_allButtons.size() - 1) )
			newCursorLocation = MoveCursorToLevel(newCursorLocation);
		else
		{
			newCursorLocation.y = std::clamp(newCursorLocation.y, 0, ((int)m_allButtons.size() - 1) );
			newCursorLocation.x = std::clamp(newCursorLocation.x, 0, ((int)m_allButtons[newCursorLocation.y].size()-1) );
		}
	}
	m_cursorLocation = newCursorLocation;
}

///////////////////////////////////////////////////////////////
// Running
///////////////////////////////////////////////////////////////

void LevelEditor::PrintLevelArray(std::ostream& os) const
{
	for (size_t y = 0; y < m_levelHeight; ++y)
	{
		for (size_t x = 0; x < m_levelWidth; ++x)
		{
			os << m_ppLevelArray[y][x] << ' ';
		}
		os << '\n';
	}
}

void LevelEditor::Print() const
{
	for (size_t y = 0; y < m_allButtons.size(); ++y)
	{
		for (size_t x = 0; x < m_allButtons.at(y).size(); ++x)
		{
			if (!m_inLevel and (m_cursorLocation.x == x and m_cursorLocation.y == y))
			{
				ConsoleManip::ChangeConsoleColour(CONSOLE_RED);
				m_allButtons[y][x].Draw();
				ConsoleManip::ChangeConsoleColour(CONSOLE_WHITE);
				std::cout << " | ";
				continue;
			}
			m_allButtons[y][x].Draw();
			std::cout << " | ";
		}
		std::cout << '\n';
	}

	for (int y = 0; y < m_levelHeight; ++y)
	{
		for (int x = 0; x < m_levelWidth; ++x)
		{
			if (m_inLevel and (m_cursorLocation.x == x and m_cursorLocation.y == y) )
			{
				ConsoleManip::ChangeConsoleColour(CONSOLE_RED);
				std::cout << m_ppLevelArray[y][x] << ' ';
				ConsoleManip::ChangeConsoleColour(CONSOLE_WHITE);
				continue;
			}
			std::cout << m_ppLevelArray[y][x] << ' ';
		}
		std::cout << '\n';
	}
}

void LevelEditor::Run()
{
	while (m_keepEditing)
	{
		system("cls");
		Print();
		GetKeyInput();
	}

}













