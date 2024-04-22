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

	virtual void Update() override;
	virtual Component* Clone() override { return new HealthTracker(*this); }

	void ChangeHealth(size_t healthChange);
	size_t Get() const { return m_health; }
	size_t* operator&() { return &m_health; }

	bool Kill();
	bool IsDead() const;
};

