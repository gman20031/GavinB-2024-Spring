// Player.h
#pragma once
//#include "Entity.h"

class World;

class Player : public Entity
{
	static constexpr int kMaxHitPoints = 10;

	static constexpr int kBaseScore = 1000;
	static constexpr int kHitPointsWeight = 100;
	static constexpr int kGoldWeight = 10;
	static constexpr int kMoveCountWeight = 10;
	static constexpr int kDetectorChrages = 3;
	static constexpr int kDetectorRange = 1;

    int m_gold;
    int m_moveCount;
	int m_detectorCharges;

public:
	Player(int x, int y, World* pWorld);

	void Move(int deltaX, int deltaY);
	virtual void Draw() override;
	void DrawSelf() const;  // assumes the cursor is at the right place
    void DrawUi() const;
    virtual void Update() override;
	virtual bool IsPlayer() override { return true; }

	void CheckForBombs();
    void AddGold(int amount);
    int CalculateScore() const;

	void EndGame();
};
