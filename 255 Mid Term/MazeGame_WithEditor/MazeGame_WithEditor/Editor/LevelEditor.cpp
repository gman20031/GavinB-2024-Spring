#include "LevelEditor.h"

#include "../SharedGameFiles/Prompting.h"

#include "../SharedGameFiles/MapFileLoader.h"

#include <assert.h>
#include <iostream>
#include <algorithm>
#include <conio.h>


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
	ConsoleManip::DrawToConsole(m_name.c_str());
}
void EditorButton::DrawSelected() const
{
	ConsoleManip::DrawToConsole(m_name.c_str(), kSelectedColour);
}


/////////////////////////// Level Editor /////////////////////////////////

///////////////////////////////////////////////////////////////
// Initialization
///////////////////////////////////////////////////////////////

LevelEditor::LevelEditor()
	: m_keepEditing(false)
	, m_cursorLocation({ 0,0 })
	, m_inLevel(false)
	, m_selectedChar(kDefaultChar)
	, m_levelHeight(1)
	, m_levelWidth(1)
	, m_enemyCount(0)
	, m_switchCount(0)
	, m_fileStream()
	, m_chosenFile()
{
	m_currentFilePath = MapFileLoader::kdefaultFilePath;
	InitButtons();
	InitDefaultMap();
}

void LevelEditor::InitButtons()
{
	m_allButtons.push_back({
		 EditorButton{"Save",   ButtonType::kSaveLevel}
		,EditorButton{"Save As",ButtonType::kSaveLevelAs}
		,EditorButton{"Load",   ButtonType::kLoadLevel}
		,EditorButton{"Resize",  ButtonType::kResize}
		,EditorButton{"Quit",	ButtonType::kQuit}
	});
	m_allButtons.push_back({
		 EditorButton{"Path",		 ButtonType::kCharacterChanger, ObjectChar::kEmpty	}
		,EditorButton{"Wall",		 ButtonType::kCharacterChanger, ObjectChar::kWall	}
		,EditorButton{"Trap",		 ButtonType::kCharacterChanger, ObjectChar::kTrap	}
		,EditorButton{"Vert Enemy",  ButtonType::kCharacterChanger, ObjectChar::kVerticalEnemy	}
		,EditorButton{"Horz Enemy",  ButtonType::kCharacterChanger, ObjectChar::kHorizontalEnemy}
		,EditorButton{"Rand Enemy",  ButtonType::kCharacterChanger, ObjectChar::kRandomEnemy	}
		,EditorButton{"Direct Enemy",ButtonType::kCharacterChanger, ObjectChar::kDirectEnemy	}
		
	});
	m_allButtons.push_back({
		 EditorButton{"Door",		 ButtonType::kCharacterChanger, ObjectChar::kClearDoor	}
		,EditorButton{"Hidden Door", ButtonType::kCharacterChanger, ObjectChar::kHiddenDoor	}
		,EditorButton{"Toggle Plate",ButtonType::kCharacterChanger, ObjectChar::kTogglePlate}
		,EditorButton{"Sword",		 ButtonType::kCharacterChanger, ObjectChar::kSwordItem}
		,EditorButton{"Exit",		 ButtonType::kCharacterChanger, ObjectChar::kExit	}
		,EditorButton{"Player",		 ButtonType::kCharacterChanger, ObjectChar::kPlayer	}
	});
}
///////////////////////////////////////////////////////////////
/// 
///////////////////////////////////////////////////////////////
void LevelEditor::InitDefaultMap()
{
	ChangeArraySize(m_levelWidth, m_levelHeight);
	FillLevel((char)kDefaultChar);
}

///////////////////////////////////////////////////////////////
/// Fills the level from the array 1:1
///////////////////////////////////////////////////////////////
void LevelEditor::FillLevel(char fillChar)
{
	for (auto& character : m_levelArray)
	{
		character = fillChar;
	}
}

///////////////////////////////////////////////////////////////
/// Fills the array with specified character
///////////////////////////////////////////////////////////////
void LevelEditor::FillLevelFromArray(char* array)
{
	int i = 0;
	for (auto& character : m_levelArray)
	{
		character = array[i];
		++i;
	}
}

///////////////////////////////////////////////////////////////
/// Directly changes the array to specified size with .Resize()
///////////////////////////////////////////////////////////////
void LevelEditor::ChangeArraySize(int newWidth, int newHeight)
{

	m_levelWidth = newWidth;
	m_levelHeight = newHeight;

	m_levelArray.Resize(newHeight, newWidth);
}

///////////////////////////////////////////////////////////////
/// Checks to see if level has exactly 1 player and 1 exit
///////////////////////////////////////////////////////////////
bool LevelEditor::LevelIsLegal() const
{
	int playerCount = 0;
	int exitCount = 0;

	for (const auto& character : m_levelArray)
	{
		switch (character)
		{
		case (char)ObjectChar::kPlayer: ++playerCount; break;
		case (char)ObjectChar::kExit: ++exitCount; break;
		default: break;
		}
	}
	return(playerCount == 1 and exitCount == 1);
}


///////////////////////////////////////////////////////////////
/// Prompts user with ""Are you sure?(y/n)" then returns if
/// the input == 'y' (handling case)
///////////////////////////////////////////////////////////////
static bool ConfirmChoice()
{
	char input = PromptAndGetChar("Are you sure?(y/n)", { 'y','n' });
	return(input == 'y');
}

///////////////////////////////////////////////////////////////
/// Prompts and resizes the map
///////////////////////////////////////////////////////////////
void LevelEditor::Resize()
{
	if (!ConfirmChoice())
		return;
	if (!m_keepEditing)
		m_keepEditing = true;

	int x = PromptAndGetInteger("enter X value, 0-20", 0, 20);
	int y = PromptAndGetInteger("enter Y value, 0-20", 0, 20);
	ChangeArraySize(x, y);
	FillLevel((char)kDefaultChar);
}

///////////////////////////////////////////////////////////////
/// Saves the file to the mapFiles folder.
///////////////////////////////////////////////////////////////
void LevelEditor::Save()
{
	if (!LevelIsLegal())
	{
		std::cout << "level is not playable, requires 1 player and 1 exit\n";
		Pause();
		return;
	}
	if (m_chosenFile.empty())
	{
		SaveAs();
		return;
	}

	std::string fullFilePath = m_currentFilePath + m_chosenFile;
	m_fileStream.open(fullFilePath, std::ios::out);

	// this should probably be in the level Loading class...
	if (!m_fileStream.is_open())
	{
		std::cout << "Cant open " << m_chosenFile << '\n';
	}
	else
	{
		m_fileStream << m_enemyCount;
		m_fileStream << ' ';
		m_fileStream << m_switchCount;
		m_fileStream << ' ';
		m_fileStream << '\n';
		PrintLevelArray(m_fileStream);
		m_fileStream.close();
		std::cout << "map saved sucessfully\n";
	}
	Pause();
}

///////////////////////////////////////////////////////////////
/// Prompt user to name the file then calls Save();
///////////////////////////////////////////////////////////////
void LevelEditor::SaveAs()
{
	printf(VT_ESC CSR_SHOW_ON);
	std::string newFileName = PromptAndGetString("Enter name of file:") + ".txt";
	bool fileExists = false;
	for (const auto& entry : std::filesystem::directory_iterator(m_currentFilePath))
	{
		if (entry.path().filename() == newFileName)
			fileExists = true;
	}

	if (fileExists)
	{
		if (PromptAndGetChar("File already exists, overrite file? (y/n)", { 'y','n' }) == 'n')
		{ 
			return;
		}
	}
	else
	{
		m_chosenFile = newFileName;
	}
	printf(VT_ESC CSR_SHOW_OFF);
	Save();
}

///////////////////////////////////////////////////////////////
/// Prompts user to pick map, then loads that map
///////////////////////////////////////////////////////////////
void LevelEditor::Load()
{
	if (!ConfirmChoice())
		return;
	if (!m_keepEditing)
		m_keepEditing = true;

	m_chosenFile = ChooseFromFileDirectory(m_currentFilePath);

	auto MapArray = MapFileLoader::CreateMapInformation(m_currentFilePath + m_chosenFile);
	m_enemyCount = MapArray.m_enemyCount;
	m_switchCount = MapArray.m_switchCount;
	ChangeArraySize(MapArray.m_width, MapArray.m_height);
	FillLevelFromArray(MapArray.m_charArray);

	Pause();
}

///////////////////////////////////////////////////////////////
/// Prompts if user wants to quit, then quits if y
///////////////////////////////////////////////////////////////
void LevelEditor::Quit()
{
	if (!ConfirmChoice())
		return;

	std::cout << "would you like to save? (y/n)" << '\n';
	if (PromptAndGetChar("Would you like to save?", { 'y','n' }) == 'y')
		Save();

	m_inLevel = false;
	m_keepEditing = false;
}

///////////////////////////////////////////////////////////////
/// Changes the character currently being targeted by cursor
/// with specified character
///////////////////////////////////////////////////////////////
void LevelEditor::ChangeCharacter(char newCharacter)
{
	char& target = m_levelArray[m_cursorLocation.y][m_cursorLocation.x];
	using enum ObjectChar;
	static char enemyCharacters[] =
	{
		(char)kVerticalEnemy,
		(char)kHorizontalEnemy,
		(char)kRandomEnemy,
		(char)kDirectEnemy,
	};

	for (const auto& enemyChar : enemyCharacters)
	{
		if (newCharacter == enemyChar)
			++m_enemyCount;
		if (target == enemyChar)
			--m_enemyCount;
	}

	if (newCharacter == (char)ObjectChar::kTogglePlate)
		++m_switchCount;
	if (target == (char)ObjectChar::kTogglePlate)
		--m_switchCount;

	target = (newCharacter);
}

///////////////////////////////////////////////////////////////
// uses _getch to get user input and then handles that input
///////////////////////////////////////////////////////////////
void LevelEditor::GetKeyInput()
{
	char input = (char)tolower(_getch());
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
		ChangeCharacter((char)m_selectedChar);
	else
		m_allButtons[m_cursorLocation.y][m_cursorLocation.x].Interact(this);
}



///////////////////////////////////////////////////////////////
/// Changes the position of the users cursor
///////////////////////////////////////////////////////////////
void LevelEditor::MoveCursor(EditorControls direction)
{
	Vector2 newCursorLocation = m_cursorLocation;
	
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
Vector2 LevelEditor::MoveCursorToButtons(Vector2 newCursorLocation)
{
	newCursorLocation.y = (int)m_allButtons.size() - 1; // bottom row
	newCursorLocation.x %= ((int)m_allButtons[newCursorLocation.y].size());
	m_inLevel = false;
	return newCursorLocation;
}
Vector2 LevelEditor::MoveCursorToLevel(Vector2 newCursorLocation)
{
	newCursorLocation.y = 0;
	newCursorLocation.x %= (m_levelWidth - 1);
	m_inLevel = true;
	return newCursorLocation;
}

///////////////////////////////////////////////////////////////
/// Directly prints the whole array with line breaks to OS
///////////////////////////////////////////////////////////////
void LevelEditor::PrintLevelArray(std::ostream& os) const
{
	int i = 0;
	for (const auto& character : m_levelArray)
	{
		++i;
		os << character << ' ';
		if (i % m_levelWidth == 0)
			os << '\n';
	}

}

///////////////////////////////////////////////////////////////
/// Prints the whole level editor menu to the console
///////////////////////////////////////////////////////////////
void LevelEditor::Print() const
{
	for (size_t y = 0; y < m_allButtons.size(); ++y)
	{
		for (size_t x = 0; x < m_allButtons.at(y).size(); ++x)
		{
			if (!m_inLevel and (m_cursorLocation.x == x and m_cursorLocation.y == y))
				m_allButtons[y][x].DrawSelected();
			else
				m_allButtons[y][x].Draw();

			std::cout << " | ";
		}
		std::cout << '\n';
	}

	for (int y = 0; y < m_levelHeight; ++y)
	{
		for (int x = 0; x < m_levelWidth; ++x)
		{
			if (m_inLevel and (m_cursorLocation.x == x and m_cursorLocation.y == y))
				ConsoleManip::DrawToConsole((m_levelArray[y][x]), kSelectedColour);
			else
				ConsoleManip::DrawToConsole((m_levelArray[y][x]));
			//std::cout << ' ';
		}
		std::cout << '\n';
	}
	std::cout << "Currently selected character: " << (char)m_selectedChar << '\n';
	std::cout << "Enemy count: " << m_enemyCount << '\n';
	std::cout << "Switch  count: " << m_switchCount  << '\n';
}

///////////////////////////////////////////////////////////////
/// Starts the loop to run the level edior
///////////////////////////////////////////////////////////////
void LevelEditor::Run()
{
	printf(VT_ESC CSR_SHOW_OFF);
	m_keepEditing = true;
	while (m_keepEditing)
	{
		ConsoleManip::ClearConsole();
		Print();
		GetKeyInput();
	}
	printf(VT_ESC CSR_SHOW_ON);

}

