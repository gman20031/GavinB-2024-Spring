#pragma once

#include <conio.h>
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <array>
#include <assert.h>

#include "Vector2.h"
#include "Trigger.h"


enum class Direction : unsigned char
{
	kNorth,
	kSouth,
	kEast,
	kWest
};

class Player
{
	using Color = WORD;

private:
	Vector2<size_t> m_position;
	Direction m_direction;
	Color m_color;

public:
	Player(size_t x, size_t y, Direction direction, Color color)
		: m_position{ x, y }
		, m_direction{ direction }
		, m_color{ color }
	{}

	Vector2<size_t>& GetPosition() { return m_position; }
	void SetDirection(Direction direction) { m_direction = direction; }
	Color& GetColor() { return m_color; }

	char GetAppearance()
	{
		switch (m_direction)
		{
		case Direction::kNorth: return '^';
		case Direction::kSouth: return 'v';
		case Direction::kEast:  return '>';
		case Direction::kWest:  return '<';
		}
		return '?';
	}
};

class Game
{
	using ConsoleHandle = HANDLE;
	using Color = WORD;

private:
	inline static const std::string kfileName = "PlayerInfo.txt";

	size_t m_width;
	size_t m_height;
	Player m_player;
	ConsoleHandle m_handle;
	Color m_defaultColor;
	bool m_quit;

	std::array<Trigger, 2> m_triggers =
	{
		Trigger{ 3,3,'?', [](Player* pPlayer)
			{
				pPlayer->SetDirection(Direction::kNorth);
			}
		},
		Trigger{ 6,5,'%', [](Player* pPlayer)
			{
				--(pPlayer->GetColor());
			}
		}
	};


public:
	Game(size_t w, size_t h)
		: m_width{ w }
		, m_height{ h }
		, m_player{ 0, 0, Direction::kNorth, 0x02 }
		, m_handle{ GetStdHandle(STD_OUTPUT_HANDLE) }
		, m_defaultColor{ 0x07 }
		, m_quit{ false }
	{
		//
	}

	void RunGameLoop()
	{
		while (!m_quit)
		{
			system("cls");
			Draw();
			Update();
		}
	}

	void LoadPlayer()
	{
		std::fstream playerFile;
		playerFile.open(kfileName , std::ios_base::in);
		if (playerFile.is_open() == false)
			return;

		Vector2<size_t> position(0,0);
		Direction direction = Direction::kNorth;
		WORD color = 0;
		char appearance = 0;

		playerFile >> position;
		playerFile >> color;
		playerFile >> appearance;
		
		playerFile.close();

		using enum Direction;
		switch (appearance)
		{
		case '^': direction = kNorth;break;
		case 'v': direction = kSouth;break;
		case '>': direction = kEast; break;
		case '<': direction = kWest; break;
		}

		m_player.SetDirection(direction);
		m_player.GetPosition() = position;
		m_player.GetColor() = color;
	}

	void SavePlayer()
	{
		std::fstream playerFile;
		playerFile.open(kfileName, std::ios_base::out);
		assert(playerFile.is_open());

		playerFile << m_player.GetPosition() << '\n';
		playerFile << m_player.GetColor() << '\n';
		playerFile << m_player.GetAppearance() << '\n';

		playerFile.close();
	}

private:
	void Draw()
	{
		const Vector2<size_t>& pPlayerPosition = m_player.GetPosition();

		for (size_t y = 0; y < m_height; ++y)
		{
			for (size_t x = 0; x < m_width; ++x)
			{
				if (x == pPlayerPosition.m_x && y == pPlayerPosition.m_y)
				{
					SetConsoleTextAttribute(m_handle, m_player.GetColor());
					std::cout << m_player.GetAppearance();
					SetConsoleTextAttribute(m_handle, m_defaultColor);
					continue;
				}
				bool triggerFound = false;
				for (auto& trigger : m_triggers)
				{
					if (trigger.GetPosition().m_x == x && trigger.GetPosition().m_y == y)
					{
						trigger.Draw();
						triggerFound = true;
						break;
					}
				}
				if (triggerFound)
					continue;
				std::cout << '.';

			}
			std::cout << std::endl;
		}
	}

	void Update()
	{
		switch (_getch())
		{
		case 'w': MovePlayer(0, -1); break;
		case 'a': MovePlayer(-1, 0); break;
		case 's': MovePlayer(0, 1);  break;
		case 'd': MovePlayer(1, 0);  break;
		case 'q': m_quit = true;	 break;
		case 'p': SavePlayer();		 break;
		case 'o': LoadPlayer();		 break;
		case 'c': ++m_player.GetColor(); break;
		}
	}

	void MovePlayer(int dx, int dy)
	{
		Vector2<size_t>& playerPosition = m_player.GetPosition();
		Vector2<size_t> newPosition = playerPosition;
		newPosition.m_x += dx;
		newPosition.m_y += dy;

		if (dx > 0)
			m_player.SetDirection(Direction::kEast);
		else if (dx < 0)
			m_player.SetDirection(Direction::kWest);
		else if (dy < 0)
			m_player.SetDirection(Direction::kNorth);
		else
			m_player.SetDirection(Direction::kSouth);

		if (   newPosition.m_x < 0 || newPosition.m_x >= m_width
			|| newPosition.m_y < 0 || newPosition.m_y >= m_height)
		{
			return;
		}

		playerPosition = newPosition;

		for (auto& trigger : m_triggers)
		{
			if (trigger.GetPosition() == newPosition)
				trigger.OnStep(&m_player);
		}

	}
};

