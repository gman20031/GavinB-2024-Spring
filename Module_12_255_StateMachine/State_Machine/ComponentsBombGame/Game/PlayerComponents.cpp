#include "PlayerComponents.h"

#include <conio.h>

#include "Appearances.h"
#include "../Engine/Actor.h"
#include "HealthTracker.h"
#include "TileComponents.h"
#include "World.h"

// Player Ui

PlayerUI::PlayerUI(Actor* pOwner)
	: Component(pOwner)
{
}


/////////////////////////////////////////////////////////////////////
// Prints the players information as a single line. then adds a buffer white space to console.
// Returns the total number of lines printed
/////////////////////////////////////////////////////////////////////
int PlayerUI::DrawUI()
{
	static constexpr int kBuffer = 2;

	int hitPoints = m_pOwner->GetComponent<HealthTracker>()->Get();
	int gold = m_pOwner->GetComponent<MoneyCounter>()->Get();
	int detectCharges = m_pOwner->GetComponent<MimicFinder>()->GetCharges();
	int moveCount = m_pOwner->GetComponent<PlayerMover>()->Get();
	int score = m_pOwner->GetComponent<PlayerScore>()->CalculateScore();

	std::cout << "HP: " << hitPoints << "  Gold: " << gold <<
		"  Move Count: " << moveCount << "  Score: " << score <<
		"  Detector Charges: " << detectCharges << "\n\n";
	return kBuffer;
}

// player Mover
PlayerMover::PlayerMover(Actor* pOwner)
	: Component(pOwner)
	, m_moveCount(0)
{
}

void PlayerMover::Move(int deltaX, int deltaY)
{
	auto playerPos = m_pOwner->GetPosition();
	playerPos.x += deltaX;
	playerPos.y += deltaY;
	m_pOwner->SetPosition(playerPos);
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
	m_pOwner->GetWorldPtr()->UpdateTile(m_pOwner->GetPosition());
}

// Money Counter

void MoneyCounter::ChangeMoney(int moneyChange)
{
	m_moneyCounter += moneyChange;
}

// Player Score

PlayerScore::PlayerScore(Actor* pOwner)
	: Component(pOwner)
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
	int hitPoints = m_pOwner->GetComponent<HealthTracker>()->Get();
	int gold = m_pOwner->GetComponent<MoneyCounter>()->Get();
	int moveCount= m_pOwner->GetComponent<PlayerMover>()->Get();

	int score = kBaseScore
		+ ((hitPoints) * kHitPointsWeight)
		+ ((gold) * kGoldWeight)
		- ((moveCount) * kMoveCountWeight);
	return score;
}


// Mimic Finder
MimicFinder::MimicFinder(Actor* pOwner)
	: Component(pOwner)
	, m_detectorCharges(kStartingChrages)
{

}

static void CheckTileForBomb(Actor* pTile)
{
	ExplodeOnCollide* pExplodeCollider = pTile->GetComponent<ExplodeOnCollide>();
	if (pExplodeCollider)
	{
		if (!pExplodeCollider->Exploded())
			pTile->GetComponent<BasicRenderer>()->ChangeSprite((char)TileAppearance::kBomb);
	}
}

void MimicFinder::CheckForBombs()
{
	if (m_detectorCharges <= 0)
		return

	m_pOwner->GetComponent<PlayerMover>()->ChangeMoveCount(1);
	--m_detectorCharges;

	int playerX = m_pOwner->GetPosition().x;
	int playery = m_pOwner->GetPosition().y;
	Actor* pTile = nullptr;
	World* pWorld = m_pOwner->GetWorldPtr();

	constexpr int detectionWidth = (kDetectorRange * 2) + 1;
	constexpr int detectedSquares = detectionWidth * detectionWidth;
	int relativeX = -kDetectorRange;
	int relativeY = -kDetectorRange;

	for (size_t i = 0; i < detectedSquares; ++i)
	{
		pTile = pWorld->GetTileAt(playerX + relativeX, playery + relativeY);

		if(pTile)
			CheckTileForBomb(pTile);

		++relativeX;
		if (relativeX > kDetectorRange)
		{
			relativeX = -kDetectorRange;
			++relativeY;
		}
	}
	
}


