#include "DotsAndBoxesGame.h"

#include <iostream>
#include <conio.h>

void DotsAndBoxesGame::IntroSequence()
{
}

#define PRINTLN(str) std::cout << str << '\n'

int DotsAndBoxesGame::AskInteger(int min, int max)
{
	int input = 0;
	for(;;)
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
	PRINTLN("how many players? min 1");
	m_playerCount = AskInteger(1);
	return true;
}

bool DotsAndBoxesGame::AskBoardSize()
{
	PRINTLN("Enter Board Width, 2 - 20");
	m_boardWidth = AskInteger(2,20);
	PRINTLN("Enter Board Height, 2 - 20");
	m_boardHeight = AskInteger(2, 20);
	return true;
}

void DotsAndBoxesGame::Draw()
{
	for (int y = 0; y < m_boardHeight; ++y)
	{
		for (int x = 0; x < m_boardWidth; ++x)
		{
			if (Position{x,y} == m_CursorPosition )
				DrawSelected();
			std::cout << m_ppGameCharGrid[y][x];
		}
	}

}

void DotsAndBoxesGame::DrawSelected()
{
	//CHANGE COLOUR TO SELECTED;
	std::cout << m_ppGameCharGrid[m_CursorPosition.y][m_CursorPosition.x];
	//CHANGE COLOUR TO WHITE;
}

void DotsAndBoxesGame::ChangePlayer(int newPlayer)
{
	m_currentPlayer = newPlayer;
}

void DotsAndBoxesGame::GetGameInput()
{
	int input = _getch();
	HandleInput(input);
}

void DotsAndBoxesGame::HandleInput(int input)
{
}

void DotsAndBoxesGame::MoveCursor(Direction direction)
{
}

void DotsAndBoxesGame::SetCursor(Position newPosition)
{
}

void DotsAndBoxesGame::InteractPressed()
{
}

void DotsAndBoxesGame::AddLine(Position linePosition)
{
}

void DotsAndBoxesGame::Resize(int width, int height)
{
}

void DotsAndBoxesGame::ChangePlayers(int numberPlayers)
{
}

void DotsAndBoxesGame::CheckBoxCompletion(Position boxPostion)
{
}

void DotsAndBoxesGame::BoxCompleted()
{
}

void DotsAndBoxesGame::GivePlayerPoint()
{
}

bool DotsAndBoxesGame::NoBoxesRemaining()
{
	return false;
}

void DotsAndBoxesGame::ResetAll()
{
}

void DotsAndBoxesGame::ResetScore()
{
}

void DotsAndBoxesGame::DeleteGrid()
{
}

DotsAndBoxesGame::~DotsAndBoxesGame()
{
}

void DotsAndBoxesGame::Start()
{
}
