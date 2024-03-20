#include "DotsAndBoxesGame.h"

#include <conio.h>

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
			std::cout << m_ppGameCharGrid[y][x];
		}
	}

}

void DotsAndBoxesGame::DrawSelected(char outputChar) const
{
	ConsoleManip::PrintInColor(outputChar, s_kSelectedColor);
}


//--------------------------------------------
// Virtual Cursor
//--------------------------------------------

void DotsAndBoxesGame::MoveCursor(Direction direction)
{
	// Needed to ensure I dont leave the bounds of the game.
	switch (direction)
	{
	case Direction::kUp:	  m_CursorPosition.y -= 1; break;
	case Direction::kDown:  m_CursorPosition.y += 1; break;
	case Direction::kRight: m_CursorPosition.x += 1; break;
	case Direction::kLeft:  m_CursorPosition.x -= 1; break;
	}
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
	using enum GridCharacters;
	switch (GetArrayChar(m_CursorPosition))
	{
	case (char)kVerticleLine:	AddLine((char)kVerticleLine); break;
	case (char)kHorizontalLine:	AddLine((char)kHorizontalLine); break;
	default: return;
	}
}

//--------------------------------------------
// Game board array manipulation
//--------------------------------------------

static void FillCardinalDirections(Position start, Position cardinalDirections[4])
{
	cardinalDirections[0] = Position{ start.y, start.x + 1 };
	cardinalDirections[1] = Position{ start.y,start.x - 1 };
	cardinalDirections[2] = Position{ start.y - 1,start.x };
	cardinalDirections[3] = Position{ start.y + 1,start.x };
}

char DotsAndBoxesGame::GetArrayChar(Position position) const
{
	return m_ppGameCharGrid[position.y][position.x];
}

void DotsAndBoxesGame::AddLine(char type)
{
	using enum GridCharacters;
	int xPos = m_CursorPosition.x;
	int yPos = m_CursorPosition.y;

	m_ppGameCharGrid[yPos][xPos] = type;

	Position CardinalDirections[4];
	FillCardinalDirections(m_CursorPosition, CardinalDirections);
	for (auto& position : CardinalDirections)
	{
		if (CheckBoxCompletion(position))
		{
			ProcessPlayerScoring();
			m_ppGameCharGrid[position.y][position.x] = (char)m_currentPlayer;
		}	
	}
}

bool DotsAndBoxesGame::NoBoxesRemaining() const
{
	return(m_boxCount == 0);
}

bool DotsAndBoxesGame::CheckBoxCompletion(Position boxPosition) const
{
	using enum GridCharacters;
	int xPos = boxPosition.x;
	int yPos = boxPosition.y;
	int count = 0;

	/*
	Position CardinalDirections[4];
	FillCardinalDirections(m_CursorPosition, CardinalDirections);
	for (auto& position : CardinalDirections)
	{
		if ( at(position) == (char)kVerticleLine
		  or at(position) == (char)kHorizontalLine)
			++count;
	}
	*/

	// for all cardinal directions
	if (GetArrayChar( { xPos + 1,yPos } ) == (char)kVerticleLine
	or	GetArrayChar( { xPos - 1,yPos } ) == (char)kVerticleLine
	or	GetArrayChar( { xPos,yPos + 1 } ) == (char)kHorizontalLine
	or	GetArrayChar( { xPos,yPos - 1 } ) == (char)kHorizontalLine)
		++count;


	// Boxes have four lines
	return (count == 4);
}

void DotsAndBoxesGame::BoxCompleted()
{
	m_extraTurn = true;
	++m_pPlayerScores[m_currentPlayer];
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
}

//--------------------------------------------
// Initialization
//--------------------------------------------

void DotsAndBoxesGame::IntroSequence()
{
	PRINTLN("Welcome to dots and boxes\n"
		  <<"W A S D moves the cursor, press e to place your line\n"
		  <<"Please enjoy\n");
	system("pause");
	AskNumberOfPlayers();
	AskBoardSize();
}

void InsertionSort(int* sortedArray, int arrayLength)
{
	for (int* it = sortedArray + 1; it < sortedArray + arrayLength; ++it)
	{
		// compare current integer selected to all earlier integers
		for (int* subIt = it; subIt > sortedArray; --subIt)
		{
			if (*(subIt) < *(subIt - 1))
			{
				int temp = *subIt;
				*(subIt) = *(subIt - 1);
				*(subIt - 1) = temp;
			}
		}
	}
}

void DotsAndBoxesGame::ConclusionSequence()
{
	PRINTLN("the map is full");
	// idk
}

void DotsAndBoxesGame::ProcessPlayerScoring()
{
	++m_pPlayerScores[m_currentPlayer];
	m_extraTurn = true;
}

bool DotsAndBoxesGame::Start()
{
	ConsoleManip::EnableVTMode();
	ConsoleManip::ChangeConsoleTitle("Dots And Boxes");

	// intro
		// how many players
		// size of grid
	// process player input
	// check if games complete
	// print winner
	// ask to play again

	IntroSequence();
	while (m_keepRunning)
	{
		Draw();
		GetGameInput();
		if (NoBoxesRemaining())
		{
			ConclusionSequence();
		}
	}
	return true;
}



























