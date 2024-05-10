#pragma once

#include "State.h"

class Mario;

class MarioState : public State
{
protected:
	Mario* m_pOwner;

public:
	MarioState( Mario* pOwner) : m_pOwner(pOwner) {}

	virtual void EatMushroom(){}
	virtual void EatFireFlower() {}
	virtual void GetHit() {}
	virtual void DoAction() {}
	virtual void PrintDescription() {}
	virtual void OnEnter() {}
	virtual void OnExit() {}
};

class MarioSmall : public MarioState
{
public:
	MarioSmall(Mario* pOwner) : MarioState(pOwner) {}
	virtual void EatMushroom() override;
	virtual void EatFireFlower() override;
	virtual void GetHit() override;
	virtual void DoAction() override;
	virtual void PrintDescription() override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
};


class MarioBig : public MarioState
{
public:
	MarioBig(Mario* pOwner) : MarioState(pOwner) {}
	virtual void EatMushroom() override;
	virtual void EatFireFlower() override;
	virtual void GetHit() override;
	virtual void DoAction() override;
	virtual void PrintDescription() override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
};

class MarioFire : public MarioState
{
public:
	MarioFire(Mario* pOwner) : MarioState(pOwner) {}
	virtual void EatMushroom() override;
	virtual void EatFireFlower() override;
	virtual void GetHit() override;
	virtual void DoAction() override;
	virtual void PrintDescription() override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
};
