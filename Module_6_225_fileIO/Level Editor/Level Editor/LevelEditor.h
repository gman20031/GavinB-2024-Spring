#pragma once
#include "Coordinate.h"

#include <string>

enum class ButtonType
{
	kCharacterChanger,
	kSaveLevel,
	kSaveLevelAs,
	KGoBack,
};

	class LevelButton
{
private:

	std::string m_name;
	ButtonType m_type;
public:
	LevelButton(std::string& name, ButtonType type) : m_name(name), m_type(type) {}
	void Interact();

};

class LevelEditor
{
private:
	Coordinates m_cursorLocation;
	char selectedChar;
	char** m_ppLevelArray;

	void GetKeyInput();
	void MoveCursor(); 

	friend class LevelButton;
	LevelButton* m_pAllButtons;

	void SaveLevel();
	void SaveLevelAs();
	void GoBack();
	void ChangeSelectedCharacter(char newChar);

public:



	//SelectorButton;
	//Save button
	//Save as button
	//Go Back
	
	// how do I do this

};