#pragma once
#include "../SharedGameFiles/GameCharacterInfo.h"
#include "../SharedGameFiles/ConsoleManip.h"
#include "../SharedGameFiles/TwoDimensionalArray.h"
#include "../SharedGameFiles/Vector2.h"


#include <vector>
#include <string>
#include <filesystem>
#include <fstream>

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

class LevelEditor;

class EditorButton
{
private:
	inline static const char* kSelectedColour = TEXT_RED;
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
	void DrawSelected() const;
};

class LevelEditor
{
	friend class EditorButton;
private:
	inline static const char* kSelectedColour = TEXT_RED;
	static constexpr ObjectChar kDefaultChar = ObjectChar::kWall;
	bool m_keepEditing;
	bool m_inLevel;

	std::vector<std::vector<EditorButton>> m_allButtons;
	Vector2 m_cursorLocation;
	ObjectChar m_selectedChar;

	TwoDimensionalArray<char> m_levelArray;
	int m_levelHeight;  
	int m_levelWidth;
	int m_enemyCount;
	int m_switchCount;

	std::fstream m_fileStream;
	std::string m_currentFilePath;
	std::string m_chosenFile;

	void FillLevel(char fillChar);
	void ChangeArraySize(int newWidth, int newHeight);
	void FillLevelFromArray(char* array);
	void PrintLevelArray(std::ostream& os) const;
	bool LevelIsLegal() const;

	void GetKeyInput();
	void Interact();
	void MoveCursor(EditorControls direction);
	Vector2 MoveCursorToButtons(Vector2 newCursorLocation);
	Vector2 MoveCursorToLevel(Vector2 newCursorLocation);

	void ChangeCharacter(char newCharacter);
	void Save();
	void SaveAs();
	void Quit();

	void InitButtons();
	void InitDefaultMap();

	void Print() const;
public:
	LevelEditor();
	~LevelEditor() = default;

	bool IsRunning() const { return m_keepEditing; };
	void Resize(); 
	void Load();
	void Run();
};