#pragma once
#include "Coordinate.h"

#include <vector>
#include <string>

enum class ButtonType
{
	kCharacterChanger,
	kSaveLevel,
	kSaveLevelAs,
	kLoadLevel,
	kQuit,
	kResize,
};

enum class EditorControls
{
	kUp = 'w',
	kDown = 's',
	kRight = 'd',
	kLeft = 'a',
	kInteract = 'e',
};

enum class ObjectChar
{
	kBase = '\0',
	kWall = '#',
	kExit = 'X',
	kEmpty = '.',
	kPlayer = '@',
	kTrap = '0',
	kHorizontalEnemy = '-',
	kVerticalEnemy = '|',
	kCount = 8,
};

class LevelEditor;

class EditorButton
{
private:
	std::string m_name;
	ButtonType m_type;
	ObjectChar m_charChanger;

public:
	EditorButton(const std::string& name, ButtonType type,
		ObjectChar characterChanger = ObjectChar::kBase) :
		m_name(name)
		, m_type(type)
		, m_charChanger(characterChanger)
	{}
	void Interact(LevelEditor* editor) const;

	void Draw() const;
};

class LevelEditor
{
	friend class EditorButton;
private:
	static constexpr ObjectChar kDefaultChar = ObjectChar::kWall;
	bool m_keepEditing;

	Coordinates m_cursorLocation;
	bool m_inLevel;
	ObjectChar m_selectedChar;

	char** m_ppLevelArray;
	int m_levelHeight;
	int m_levelWidth;

	std::vector<std::vector<EditorButton>> m_allButtons;
	//EditorButton* m_pCurrentButton;

	void FillLevel(char fillChar);
	void ChangeArraySize(int newWidth, int newHeight);
	void PrintLevelArray(std::ostream& os) const;
	void DeleteLevelArray();

	void GetKeyInput();
	void Interact();
	void MoveCursor(EditorControls direction);
	Coordinates MoveCursorToButtons(Coordinates newCursorLocation);
	Coordinates MoveCursorToLevel(Coordinates newCursorLocation);

	void Resize();
	void Save();
	void SaveAs();
	void Load();
	void Quit();

	void InitButtons();
	void InitDefaultMap();

	void Print() const;
public:
	LevelEditor();
	~LevelEditor() { DeleteLevelArray(); }

	void Run();
};