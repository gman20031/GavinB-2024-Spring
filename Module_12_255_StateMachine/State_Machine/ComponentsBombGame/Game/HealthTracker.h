#pragma once

#include "../Engine/ComponentFactory.h"

class HealthTracker : public Component
{
	ID_FROM_NAME("HealthTracker");
private:
	int m_health = 0;
	bool m_dead = false;
public:
	HealthTracker(Actor* pOwner) : Component(pOwner){}
	HealthTracker(const HealthTracker& original, Actor* pOwner);
	
	void SetHealth(int newHealth);
	void ModifyHealth(int healthChange);
	int Get() const { return m_health; }
	int* operator&() { return &m_health; }

	void Kill();
	bool IsDead() const;
	virtual void Update() override;
};

