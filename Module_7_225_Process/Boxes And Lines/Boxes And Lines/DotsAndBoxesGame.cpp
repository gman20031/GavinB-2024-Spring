#include "DotsAndBoxesGame.h"

#include <conio.h>
#include <assert.h>
#include <algorithm>

#define PRINTLN(str) std::cout << str << '\n'

bool operator==(const Position& lhs, const Position& rhs)
{
	return(
		lhs.x == rhs.x
		and lhs.y == rhs.y
		);
}

DotsAndBoxesGame::DotsAndBoxesGame()
	:m_CursorPosition{ 0,0 }
	,m_ppGameCharGrid(nullptr)
	,m_pPlayerScores(nullptr)
{
}

//--------------------------------------------
// Printing
//--------------------------------------------


void DotsAndBoxesGame::Draw() const
{
	for (int y = 0; y < m_boardHeight; ++y)
	{
		for (int x = 0; x < m_boardWidth; ++x)
		{
			if (Position{ x,y } == m_CursorPosition)
				DrawSelected(m_ppGameCharGrid[y][x]);
			else
				std::cout << m_ppGameCharGrid[y][x];
		}
		std::cout << '\n';
	}
	PRINTLN("Current Player: " << (m_currentPlayer + 1));
}

void DotsAndBoxesGame::DrawSelected(char outputChar) const
{
	
	ConsoleManip::PrintInColor(outputChar, s_kSelectedBackColor);
	//printf(VT_ESC "%c" VT_ESC VT_DEF, outputChar);

}


//--------------------------------------------
// Virtual Cursor
//--------------------------------------------

void DotsAndBoxesGame::MoveCursor(Direction direction)
{
	// Needed to ensure I dont leave the bounds of the game.
	Position newPosition = m_CursorPosition;
	switch (direction)
	{
	case Direction::kUp:	newPosition.y -= 1; break;
	case Direction::kDown:  newPosition.y += 1; break;
	case Direction::kRight: newPosition.x += 1; break;
	case Direction::kLeft:  newPosition.x -= 1; break;
	}
	newPosition.y = std::clamp(newPosition.y, 0, m_boardHeight-1);
	newPosition.x = std::clamp(newPosition.x, 0, m_boardWidth-1);
	m_CursorPosition = newPosition;
}


void DotsAndBoxesGame::SetCursor(Position newPosition)
{
	m_CursorPosition = newPosition;
}

//--------------------------------------------
// User input
//--------------------------------------------


void DotsAndBoxesGame::GetGameInput()
{
	int input = _getch();
	HandleInput(input);
}

void DotsAndBoxesGame::HandleInput(int input)
{
	switch (input)
	{
	case (char)Direction::kUp:	
	case (char)Direction::kDown: 
	case (char)Direction::kRight: 
	case (char)Direction::kLeft:  MoveCursor(static_cast<Direction>(input)); break;
	case kInteractKey: InteractPressed(); break;
	default: return;
	}
}

int DotsAndBoxesGame::AskInteger(int min, int max)
{
	int input = 0;
	for (;;)
	{
		std::cin >> input;
		if (input <= max and input >= min and std::cin.good())
			return input;
	}
}

int DotsAndBoxesGame::AskInteger(int min)
{
	int input = 0;
	for (;;)
	{
		std::cin >> input;
		if (input >= min and std::cin.good())
			return input;
	}
}

bool DotsAndBoxesGame::AskNumberOfPlayers()
{
	PRINTLN("how many players? 1 - 4");
	m_playerCount = AskInteger(1, 4);
	return true;
}

bool DotsAndBoxesGame::AskBoardSize()
{
	PRINTLN("Enter Board Width, 2 - 20");
	m_boardWidth = AskInteger(2, 20);
	PRINTLN("Enter Board Height, 2 - 20");
	m_boardHeight = AskInteger(2, 20);
	return true;
}

void DotsAndBoxesGame::InteractPressed()
{
	using enum GridCharacter;
	if (GetArrayChar(m_CursorPosition) == (char)kBox)
	{
		switch (CorrectCharacterAt(m_CursorPosition))
		{
		case (char)kVerticleLine:	AddLine((char)kVerticleLine); break;
		case (char)kHorizontalLine:	AddLine((char)kHorizontalLine); break;
		default: return;
		}
	}
}

char DotsAndBoxesGame::CorrectCharacterAt(Position target)
{
	using enum GridCharacter;
	bool horizontal = false;
	bool vertical = false;

	if (GetArrayChar(target) != ' ')
		return GetArrayChar(target);

	if(GetArrayChar(Position{ target.y, target.x + 1 }) == (char)kDot
	or GetArrayChar(Position{ target.y, target.x - 1 }) == (char)kDot)
		horizontal = true;

	if(GetArrayChar(Position{ target.y - 1,target.x  }) == (char)kDot 
	or GetArrayChar(Position{ target.y + 1,target.x  }) == (char)kDot)
		vertical = true;

	if (horizontal)
		return (char)kHorizontalLine;
	if (vertical)
		return (char)kVerticleLine;
	return '\0';
}

//--------------------------------------------
// Game board array manipulation
//--------------------------------------------

static void FillCardinalDirections(Position start, Position cardinalDirections[4])
{
	cardinalDirections[0] = Position{ start.x,    start.y + 1 };
	cardinalDirections[1] = Position{ start.x,    start.y - 1 };
	cardinalDirections[2] = Position{ start.x - 1,start.y };
	cardinalDirections[3] = Position{ start.x + 1,start.y };
}

char DotsAndBoxesGame::GetArrayChar(Position position) const
{
	if(PositionOutOfBound(position) ) 
		return ('\0');
	return m_ppGameCharGrid[position.y][position.x];
}

bool DotsAndBoxesGame::PositionOutOfBound(Position position) const
{
	return (
		position.x >= m_boardWidth
	or	position.x < 0
	or	position.y >= m_boardHeight
	or  position.y < 0
	);
}

void DotsAndBoxesGame::AddLine(char type)
{
	using enum GridCharacter;
	int xPos = m_CursorPosition.x;
	int yPos = m_CursorPosition.y;

	m_ppGameCharGrid[yPos][xPos] = type;
	m_turnFinished = true;

	Position CardinalDirections[4];
	FillCardinalDirections(m_CursorPosition, CardinalDirections);
	for (auto& position : CardinalDirections)
	{
		if (PositionOutOfBound(position))
			continue;
		if(GetArrayChar(position) == (char)kBox)
		{
			if (CheckBoxCompletion(position))
			{
				BoxCompleted(position);
			}
		}
	}
}

void DotsAndBoxesGame::FillDotRow(char* pRowArray, int width)
{
	using enum GridCharacter;
	for (size_t i = 0; i < width; ++i)
	{
		if (i == width - 1)
		{
			pRowArray[i] = (char)kDot;
			continue;
		}
		pRowArray[i] = (char)kDot;
		++i;
		pRowArray[i] = ' ';
	}
	pRowArray[width] = '\0';
}

void DotsAndBoxesGame::FillBoxRow(char* pRowArray, int width)
{
	using enum GridCharacter;
	for (size_t i = 0; i < width; ++i)
	{
		if (i == width - 1)
		{
			pRowArray[i] = ' ';
			continue;
		}
		pRowArray[i] = (char)kBox;
		++m_boxCount;
		++i;
		pRowArray[i] = ' ';
	}
	pRowArray[width] = '\0';
}
void DotsAndBoxesGame::CreateAndFillArray(int height, int width)
{
	int newWidth = (width * 2) - 1;
	int newHeight = (height * 2) - 1;

	Resize(newWidth + 1, newHeight + 1);

	for (int y = 0; y < newHeight; ++y)
	{
		if (y == newHeight-1)
		{
			FillDotRow(m_ppGameCharGrid[y], newWidth);
			continue;
		}
		FillDotRow(m_ppGameCharGrid[y], newWidth);
		++y;
		FillBoxRow(m_ppGameCharGrid[y], newWidth);

	}
	m_boardWidth = newWidth;
	m_boardHeight = newHeight;
}

bool DotsAndBoxesGame::NoBoxesRemaining() const
{
	return(m_boxCount == 0);
}

bool DotsAndBoxesGame::CheckBoxCompletion(Position boxPosition) const
{
	using enum GridCharacter;

	int count = 0;

	
	Position CardinalDirections[4];
	FillCardinalDirections(boxPosition, CardinalDirections);
	for (auto& position : CardinalDirections)
	{
		if(PositionOutOfBound(position) )
			continue;
		if ( GetArrayChar(position) == (char)kVerticleLine
		  or GetArrayChar(position) == (char)kHorizontalLine)
			++count;
	}
	
	//int xPos = boxPosition.x;
	//int yPos = boxPosition.y;
	//// for all cardinal directions
	//if (GetArrayChar( { xPos + 1,yPos } ) == (char)kVerticleLine
	//or	GetArrayChar( { xPos - 1,yPos } ) == (char)kVerticleLine
	//or	GetArrayChar( { xPos,yPos + 1 } ) == (char)kHorizontalLine
	//or	GetArrayChar( { xPos,yPos - 1 } ) == (char)kHorizontalLine)
	//	++count;


	// Boxes have four lines
	return (count == 4);
}

void DotsAndBoxesGame::BoxCompleted(Position position)
{
	m_ppGameCharGrid[position.y][position.x] = ((char)m_currentPlayer + '1');
	++(m_pPlayerScores[m_currentPlayer]);
	m_turnFinished = false;
	--m_boxCount;
}

//--------------------------------------------
// Cleanup
//--------------------------------------------

void DotsAndBoxesGame::ResetAll()
{
	ResetScore();
	DeleteGrid();
}

void DotsAndBoxesGame::Resize(int width, int height)
{
	DeleteGrid();

	m_ppGameCharGrid = (char**)(calloc(height, sizeof(char*)));

	for (int y = 0; y < height; ++y)
	{
		assert(m_ppGameCharGrid != nullptr);
		m_ppGameCharGrid[y] = (char*)(calloc(width, sizeof(char)));
	}
}

void DotsAndBoxesGame::ResetScore()
{
	for (size_t i = 0; i < m_playerCount; ++i)
		m_pPlayerScores[i] = 0;
}

void DotsAndBoxesGame::DeleteGrid()
{
	if (m_ppGameCharGrid == nullptr)
		return;
	for (int y = 0; y < m_boardHeight; ++y)
	{
		free(m_ppGameCharGrid[y]);
	}
	free(m_ppGameCharGrid);
	m_ppGameCharGrid = nullptr;
}


DotsAndBoxesGame::~DotsAndBoxesGame()
{
	DeleteGrid();
	delete m_pPlayerScores;
}

//--------------------------------------------
// Initialization
//--------------------------------------------

void DotsAndBoxesGame::IntroSequence()
{
	PRINTLN("Welcome to dots and boxes\n"
		<< "W A S D moves the cursor, press e to place your line\n"
		<< "Please enjoy\n");
	system("pause");
	AskNumberOfPlayers();
	AskBoardSize();
	m_pPlayerScores = new int[m_playerCount];
	ResetScore();
	CreateAndFillArray(m_boardWidth, m_boardHeight);
}

int DotsAndBoxesGame::FindWinnerIndex()
{
	int highscore = 0;
	int winningPlayer = 0;
	for (int i = 0; i < m_playerCount; ++i)
	{
		if (m_pPlayerScores[i] > highscore)
		{
			highscore = m_pPlayerScores[i];
			winningPlayer = i;
		}
	}
	return winningPlayer;
}

void DotsAndBoxesGame::ConclusionSequence()
{
	PRINTLN("Game finished");
	system("pause");
	system("cls");
	int winner = FindWinnerIndex();
	PRINTLN("Player :" << (winner + 1) << " won with " << m_pPlayerScores[winner]);
	PRINTLN("Play again?");
	// idk
}

void DotsAndBoxesGame::GotoNextPlayer()
{
	PRINTLN("Turn complete");
	m_turnFinished = false;
	if (m_currentPlayer == m_playerCount - 1)
		m_currentPlayer = 0;
	else
		++m_currentPlayer;
	PRINTLN("New player:" << (m_currentPlayer + 1));
	system("pause");
}

bool DotsAndBoxesGame::Start()
{
	ConsoleManip::EnableVTMode();
	ConsoleManip::ChangeConsoleTitle("Dots And Boxes");

	IntroSequence();
	while (m_keepRunning)
	{
		system("cls");
		Draw();
		if (NoBoxesRemaining())
			ConclusionSequence();
		GetGameInput();
		if (m_turnFinished)
			GotoNextPlayer();
	}
	return true;
}



























