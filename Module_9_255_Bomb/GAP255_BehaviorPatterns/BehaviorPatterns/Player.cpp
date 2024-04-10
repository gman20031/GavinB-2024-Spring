// Player.cpp
#include "Player.h"
#include <iostream>
#include <conio.h>

#include "World.h"

using std::cout;

const int Player::k_maxHitPoints = 10;

const int Player::k_baseScore = 1000;
const int Player::k_hitPointsWeight = 100;
const int Player::k_goldWeight = 10;
const int Player::k_moveCountWeight = 10;

Player::Player(int x, int y, World* pWorld)
	: m_x(x)
	, m_y(y)
	, m_pWorld(pWorld)
    , m_hitPoints(k_maxHitPoints)
    , m_gold(0)
    , m_moveCount(0)
{ }

void Player::Draw() const
{
    if (!IsDead())
	    cout << "@";
    else
        cout << "~";
}

void Player::DrawUi() const
{
    cout << "HP: " << m_hitPoints << "  Gold: " << m_gold << "  Move Count: " << m_moveCount << "  Score: " << CalculateScore() << "\n\n";
}

bool Player::Update()
{
    if (IsDead())
        return false;

    char input = (char)_getch();

    switch (input)
    {
        case 'q':
            return false;  // quitting

        case 'w':
            Move(0, -1);
            break;

        case 'a':
            Move(-1, 0);
            break;

        case 's':
            Move(0, 1);
            break;

        case 'd':
            Move(1, 0);
            break;

        default:
            cout << "Invalid input";
            break;
    }

    return true;
}

void Player::Move(int deltaX, int deltaY)
{
	m_x += deltaX;
	m_y += deltaY;
    ++m_moveCount;
}

void Player::Damage(int amount)
{
    m_hitPoints -= amount;

    if (m_hitPoints < 0)
        m_hitPoints = 0;
}

void Player::AddGold(int amount)
{
    m_gold += amount;
}

int Player::CalculateScore() const
{
    int score = k_baseScore + (m_hitPoints * k_hitPointsWeight) + (m_gold * k_goldWeight) - (m_moveCount * k_moveCountWeight);
    return score;
}

void Player::EndGame()
{
	m_pWorld->EndGame();
}
