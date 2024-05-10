#pragma once

#include "MarioStates.h"
#include "StateMachine.h"

class Mario : public StateMachine<MarioState>
{
	bool m_dead = false;

public:
	Mario();

	virtual void EatMushroom()		{ m_pState->EatMushroom(); }
	virtual void EatFireFlower()	{ m_pState->EatFireFlower(); }
	virtual void GetHit()			{ m_pState->GetHit(); }
	virtual void DoAction()			{ m_pState->DoAction(); }
	virtual void PrintDescription() { m_pState->PrintDescription(); }
	bool Dead() const { return m_dead; }
	void Damage();
};