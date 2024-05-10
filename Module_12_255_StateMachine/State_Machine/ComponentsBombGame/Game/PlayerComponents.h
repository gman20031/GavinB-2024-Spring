#pragma once

#include "../Engine/ComponentFactory.h"
#include "../System/Vector2d.h"

class Actor;
class World;

class PlayerUI : public Component
{
	ID_FROM_NAME("PlayerUI");
private:

public:
	PlayerUI(Actor* pOwner);

	/////////////////////////////////////////////////////////////////////
	// Prints the players information as a single line. then adds a buffer white space to console.
	// Returns the total number of lines printed
	/////////////////////////////////////////////////////////////////////
	int DrawUI();
};

// --------

class PlayerMover : public Component
{
	ID_FROM_NAME("PlayerMover");
private:
	int m_moveCount;

	void Move(int deltaX, int deltaY);
public:
	PlayerMover(Actor* pOwner);

	int GetMoveCount() const { return m_moveCount;}
	void ChangeMoveCount(int amount) { m_moveCount += amount; }
	int* operator&() { return &m_moveCount; }
	int Get() const { return m_moveCount; }

	virtual void Update() override;
};

// --------

class MoneyCounter : public Component
{
	ID_FROM_NAME("MoneyCounter");
private:
	int m_moneyCounter = 0;
public:
	MoneyCounter(Actor* pOwner) : Component(pOwner) {}

	int GetMoney() const { return m_moneyCounter; }
	int* operator&() { return &m_moneyCounter; }
	int Get() const { return m_moneyCounter; }
	
	void ChangeMoney(int moneyChange);
};

// --------

class PlayerScore : public Component
{
	ID_FROM_NAME("PlayerScore");
private:
	static constexpr int kBaseScore = 1000;
	static constexpr int kHitPointsWeight = 100;
	static constexpr int kGoldWeight = 10;
	static constexpr int kMoveCountWeight = 10;

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
	ID_FROM_NAME("MimicFinder");
private:
	static constexpr int kDetectorRange = 1;
	static constexpr int kStartingChrages = 3;
	int m_detectorCharges;

public:
	MimicFinder(Actor* pOwner);

	int GetCharges() const { return m_detectorCharges; }
	int* operator&() { return &m_detectorCharges; }

	void CheckForBombs();
};
