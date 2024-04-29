#include "PlayerComponents.h"

#include <conio.h>

#include "Appearances.h"
#include "../Engine/Actor.h"
#include "HealthTracker.h"
#include "TileComponents.h"
#include "World.h"

// Player Ui

PlayerUI::PlayerUI(Actor* pOwner)
	: Component(pOwner , s_id)
	, m_pHitPoints		(&*m_pOwner->GetComponent<HealthTracker>())
	, m_pMoneyCount		(&*m_pOwner->GetComponent<MoneyCounter>())
	, m_pDetectCharges	(&*m_pOwner->GetComponent<MimicFinder>() )
	, m_pMoveCount		(&*m_pOwner->GetComponent<PlayerMover>() )
{
}

void PlayerUI::DrawUI()
{
	int score = m_pOwner->GetComponent<PlayerScore>()->CalculateScore();
	std::cout << "HP: " << *m_pHitPoints << "  Gold: " << *m_pMoneyCount <<
		"  Move Count: " << *m_pMoveCount << "  Score: " << score <<
		"  Detector Charges: " << *m_pDetectCharges << "\n\n";
}

// player Mover
PlayerMover::PlayerMover(Actor* pOwner)
	: Component(pOwner, s_id)
	, m_PlayerPostion(pOwner->GetPosition())
	, m_moveCount(0)
{
}

void PlayerMover::Move(int deltaX, int deltaY)
{
	m_PlayerPostion.x += deltaX;
	m_PlayerPostion.y += deltaY;
	m_pOwner->SetPosition(m_PlayerPostion);
}

void PlayerMover::Update()
{
	if (m_pOwner->GetComponent<HealthTracker>()->IsDead())
		return;

	char input = (char)_getch();
	switch (input)
	{
	case 'w': Move(0, -1); break;
	case 'a': Move(-1, 0); break;
	case 's': Move(0, 1); break;
	case 'd': Move(1, 0); break;
	case 'e': m_pOwner->GetComponent<MimicFinder>()->CheckForBombs(); break;
	case 'q': m_pOwner->GetComponent<HealthTracker>()->Kill();  break;  // quitting
	default: std::cout << "Invalid input"; break;
	}

	//update the tile I am now standing on.
	m_pOwner->GetWorldPtr()->GetTileAt(m_pOwner->GetPosition())->Update();
}

// Money Counter

void MoneyCounter::ChangeMoney(int moneyChange)
{
	m_moneyCounter += moneyChange;
}

// Player Score

PlayerScore::PlayerScore(Actor* pOwner)
	: Component(pOwner, s_id)
	, m_pHitPoints(&*m_pOwner->GetComponent<HealthTracker>())
	, m_pMoveCount(&*m_pOwner->GetComponent<PlayerMover>())
	, m_pGoldCount(&*m_pOwner->GetComponent<MoneyCounter>())
	, m_score(kBaseScore)
{
}

//Recalculates and sets score
void PlayerScore::Update()
{
	m_score = CalculateScore();
}

int PlayerScore::CalculateScore()
{
	int score = kBaseScore
		+ ( (int)(*m_pHitPoints) * kHitPointsWeight)
		+ ( (int)(*m_pGoldCount) * kGoldWeight)
		- ( (int)(*m_pMoveCount) * kMoveCountWeight);
	return score;
}


// Mimic Finder
MimicFinder::MimicFinder(Actor* pOwner)
	: Component(pOwner, s_id)
	, m_pWorld(pOwner->GetWorldPtr())
	, m_detectorCharges(kStartingChrages)
{

}

void MimicFinder::CheckForBombs()
{
	if (m_detectorCharges > 0)
	{
		m_pOwner->GetComponent<PlayerMover>()->ChangeMoveCount(1);
		--m_detectorCharges;

		constexpr int detectionWidth = (kDetectorRange * 2) + 1;
		constexpr int detectedSquares = detectionWidth * detectionWidth;
		int relativeX = -kDetectorRange;
		int relativeY = -kDetectorRange;

		int targetX = m_pOwner->GetPosition().x + relativeX;
		int targetY = m_pOwner->GetPosition().y + relativeY;

		for (size_t i = 0; i < detectedSquares; ++i)
		{
			Actor* pTile = m_pWorld->GetTileAt(targetX, targetY);
			if (pTile->GetComponent<ExplodeOnCollide>())
				pTile->GetComponent<BasicRenderer>()->ChangeSprite((char)TileAppearance::kEmpty);
			++targetX;
			if (targetX > kDetectorRange)
			{
				targetX = -kDetectorRange;
				++targetY;
			}
		}
	}
}

