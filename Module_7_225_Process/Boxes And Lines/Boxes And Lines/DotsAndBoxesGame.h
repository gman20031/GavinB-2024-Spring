#pragma once

#include "ConsoleManip.h"

struct Position
{
	int x;
	int y;
};
bool operator==(const Position& lhs, const Position& rhs);
enum class Direction
{
	kUp = 'w',
	kDown = 's',
	kRight = 'd',
	kLeft = 'a',
};

//Box and Dots and box and dots and box and dots
class DotsAndBoxesGame
{
	enum class GridCharacters
	{
		kVerticleLine = '|',
		kHorizontalLine = '-',
		kDot = '0',
		kBox = ' ',
	};
	inline static const char s_kSelectedColor[] = VT_RED;
	static constexpr char kInteractKey = 'e';
	Position m_CursorPosition;

	char** m_ppGameCharGrid;
	int m_boardWidth= 0;
	int m_boardHeight= 0;
	int m_boxCount = 0;

	bool m_keepRunning = true;
	bool m_extraTurn = false;

	int m_playerCount = 0;
	int m_currentPlayer = 0;
	int* m_pPlayerScores;


	// printing
	void Draw() const;//	Print board accurately
	void DrawSelected(char outputChar) const; // require windows.h

	// virtual cursor
	void MoveCursor(Direction direction);
	void SetCursor(Position newPosition);

	// user input
	void GetGameInput();
	void HandleInput(int input);
	void InteractPressed();
	int AskInteger(int min, int max);
	int AskInteger(int min); //overloaded for ease of use
	bool AskNumberOfPlayers();
	bool AskBoardSize();

	// game board array manip
	char GetArrayChar(Position position) const;
	void AddLine(char type);
	bool NoBoxesRemaining() const;//	Check if game is done
	bool CheckBoxCompletion(Position boxPosition) const;//	Checks when box is complete
	void BoxCompleted();//	Checks who completed box
	
	// Memory and cleanup
	void ResetAll();
	void Resize(int width, int height);//	Resizable boards
	void ResetScore();
	void DeleteGrid();
	
	// other game stuff
	void IntroSequence();
	void ConclusionSequence();
	void ProcessPlayerScoring();

public:
	DotsAndBoxesGame(); 
	~DotsAndBoxesGame(); // for destroying the heap allocated 2dArray

	bool Start();
};