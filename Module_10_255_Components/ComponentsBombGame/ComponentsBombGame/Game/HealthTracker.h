#pragma once

#include "../Engine/ComponentFactory.h"

class HealthTracker : public Component
{
	NEW_STATIC_ID;
private:
	int m_health = 0;
	bool m_dead = false;
public:
	HealthTracker(Actor* pOwner) : Component(pOwner, s_id){}
	HealthTracker(const HealthTracker& original, Actor* pOwner);
	
	void SetHealth(int newHealth);
	void ModifyHealth(int healthChange);
	int Get() const { return m_health; }
	int* operator&() { return &m_health; }

	void Kill();
	bool IsDead() const;
	virtual void Update() override;
};

