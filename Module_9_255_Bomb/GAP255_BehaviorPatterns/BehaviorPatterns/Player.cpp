// Player.cpp
#include "Player.h"
#include <iostream>
#include <conio.h>

#include "World.h"

Player::Player(int x, int y, World* pWorld)
	: Entity(x, y , pWorld)
	, m_detectorCharges(kDetectorChrages)
    , m_gold(0)
    , m_moveCount(0)
{
	m_x = x;
	m_y = y;
	m_pWorld = pWorld;
	m_hitPoints = kMaxHitPoints;
}

void Player::Draw()
{
	DrawSelf();
	DrawUi();
}

void Player::DrawSelf() const
{
    if (IsDead())
        std::cout << "~";
    else
	    std::cout << "@";
}

void Player::DrawUi() const
{
    std::cout << "HP: " << m_hitPoints << "  Gold: " << m_gold <<
		"  Move Count: " << m_moveCount << "  Score: " << CalculateScore()<<
		"  Detector Charges: " << m_detectorCharges << "\n\n";
}

void Player::Update()
{
	if (IsDead())
		return;

    char input = (char)_getch();
    switch (input)
    {
        case 'w': Move(0, -1);break;
        case 'a': Move(-1, 0);break;
        case 's': Move(0, 1); break;
        case 'd': Move(1, 0); break;
		case 'e': CheckForBombs(); break;
		case 'q': Kill();  return;  // quitting
		default : std::cout << "Invalid input"; break;
    }
}

void Player::Move(int deltaX, int deltaY)
{
	m_x += deltaX;
	m_y += deltaY;
    ++m_moveCount;
}

void Player::CheckForBombs()
{
	if(m_detectorCharges > 0)
	{
		++m_moveCount;
		--m_detectorCharges;

		constexpr int detectionWidth = (kDetectorRange * 2) + 1;
		constexpr int detectedSquares = detectionWidth * detectionWidth;
		int xPos = -kDetectorRange;
		int yPos = -kDetectorRange;

		for (size_t i = 0; i < detectedSquares; ++i)
		{
			Tile* tile = m_pWorld->GetTileAt(m_x + xPos, m_y + yPos);
			if (tile->GetBehaviorType() == BehaviorStrategy::Behavior::kExplosion)
				tile->SetAppearance(AppearanceStrategy::Appearance::kBomb);
			++xPos;
			if (xPos > kDetectorRange)
			{
				xPos = -kDetectorRange;
				++yPos;
			}
		}

	}
}

void Player::AddGold(int amount)
{
    m_gold += amount;
}

int Player::CalculateScore() const
{
    int score = kBaseScore + (m_hitPoints * kHitPointsWeight) + (m_gold * kGoldWeight) - (m_moveCount * kMoveCountWeight);
    return score;
}

void Player::EndGame()
{
	m_pWorld->EndGame();
}
