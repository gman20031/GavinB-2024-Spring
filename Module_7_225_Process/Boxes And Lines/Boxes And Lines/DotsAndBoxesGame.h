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
	enum class GridCharacter
	{
		kVerticleLine = '|',
		kHorizontalLine = '-',
		kDot = 'O',
		kBox = ' ',
	};
	inline static const char s_kSelectedColor[] = VT_RED;
	inline static const char s_kSelectedBackColor[] = "41m";
	static constexpr char kInteractKey = 'e';
	Position m_CursorPosition;

	char** m_ppGameCharGrid;
	int m_boardWidth= 0;
	int m_boardHeight= 0;
	int m_boxCount = 0;

	bool m_keepRunning = true;
	bool m_turnFinished = false;

	int m_playerCount = 0;
	int m_currentPlayer = 0;
	int* m_pPlayerScores;


	// Memory and cleanup
	void ResetAll();
	void ResetScore();
	void DeleteGrid();

	// printing
	void Draw() const;//	Print board accurately
	void DrawSelected(char outputChar) const; // require windows.h

	// virtual cursor
	void MoveCursor(Direction direction);
	void SetCursor(Position newPosition);

	// user input
	void GetGameInput();
	void InteractPressed();
	int AskInteger(int min, int max);

	// game board array manip
	void Resize(int width, int height);//	Resizable boards
	void CreateAndFillArray(int height, int width);
	void FillDotRow(char* pRowArray, int width);
	void FillBoxRow(char* pRowArray, int width);
	
	bool IsPositionOutOfBound(Position position) const;
	char GetArrayChar(Position position) const;

	// high level game logic
	void HandleInput(int input);
	void GotoNextPlayer();
	int FindWinnerIndex();

	// low level game logic
	void BoxCompleted(Position position);//	Checks who completed box
	void AddLine(char type);
	bool NoBoxesRemaining() const;//	Check if game is done
	bool CheckBoxCompletion(Position boxPosition) const;//	Checks when box is complete
	char FindLineType(Position target);

	// Initalization
	void IntroSequence();
	void ConclusionSequence();
	bool AskNumberOfPlayers();
	bool AskBoardSize();

public:
	DotsAndBoxesGame(); 
	~DotsAndBoxesGame(); // for destroying the heap allocated 2dArray

	bool Start();
};