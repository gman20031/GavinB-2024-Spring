#pragma once

#include "../Engine/ComponentFactory.h"
#include "../System/Vector2d.h"

class Actor;
class World;

class PlayerUI : public Component
{
	NEW_STATIC_ID;
private:
	size_t* m_pHitPoints;
	int* m_pMoneyCount;
	int* m_pDetectCharges;
	int* m_pMoveCount;
public:
	PlayerUI(Actor* pOwner);
	void DrawUI();
};

// --------

class PlayerMover : public Component
{
	NEW_STATIC_ID;
private:
	Vector2d<int> m_PlayerPostion;
	int m_moveCount;

	void Move(int deltaX, int deltaY);
public:
	PlayerMover(Actor* pOwner);

	int GetMoveCount() const { return m_moveCount;}
	void ChangeMoveCount(int amount) { m_moveCount += amount; }
	int* operator&() { return &m_moveCount; }

	virtual void Update() override;
};

// --------

class MoneyCounter : public Component
{
	NEW_STATIC_ID;
private:
	int m_moneyCounter = 0;
public:
	MoneyCounter(Actor* pOwner) : Component(pOwner, s_id) {}

	int GetMoney() const { return m_moneyCounter; }
	int* operator&() { return &m_moneyCounter; }

	void ChangeMoney(int moneyChange);
};

// --------

class PlayerScore : public Component
{
	NEW_STATIC_ID;
private:
	static constexpr int kBaseScore = 1000;
	static constexpr int kHitPointsWeight = 100;
	static constexpr int kGoldWeight = 10;
	static constexpr int kMoveCountWeight = 10;

	size_t* m_pHitPoints;
	int* m_pMoveCount;
	int* m_pGoldCount;
	int m_score;
public:
	PlayerScore(Actor* pOwner);
	
	int GetScore() { return CalculateScore(); }
	int* operator&() { return &m_score; }

	int CalculateScore();
	virtual void Update() override;
};

// --------

class MimicFinder : public  Component
{
	NEW_STATIC_ID;
private:
	static constexpr int kDetectorRange = 1;
	static constexpr int kStartingChrages = 3;
	int m_detectorCharges;
	World* m_pWorld;

public:
	MimicFinder(Actor* pOwner);

	int GetCharges() const { return m_detectorCharges; }
	int* operator&() { return &m_detectorCharges; }

	void CheckForBombs();
};
