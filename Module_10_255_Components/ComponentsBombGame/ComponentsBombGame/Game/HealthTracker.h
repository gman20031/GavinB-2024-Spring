#pragma once

#include "../Engine/ComponentFactory.h"

class HealthTracker : public Component
{
	NEW_STATIC_ID;
private:
	size_t m_health = 0;
	bool m_dead = false;
public:
	HealthTracker(Actor* pOwner) : Component(pOwner, s_id){}
	HealthTracker(const HealthTracker& original, Actor* pOwner);


	virtual void Update() override;
	virtual Component* Clone(Actor* pOwner) override { return new HealthTracker(*this, pOwner); }

	void SetHealth(size_t newHealth);
	void ModifyHealth(size_t healthChange);
	size_t Get() const { return m_health; }
	size_t* operator&() { return &m_health; }

	void Kill();
	bool IsDead() const;
};

