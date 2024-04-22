#pragma once

#include "../Engine/Component.h"


class DirectEnemyLogic : Component
{
	NEW_STATIC_ID;
private:
	static constexpr size_t kSightRange = 5;
public:
	DirectEnemyLogic(Actor* pOwner) : Component(pOwner, s_id) {}

	//virtual void Render() override;
	virtual void Update() override;
	virtual void OnCollide() override;
};

class ScaredEnemyLogic : Component
{
	NEW_STATIC_ID;
private:
	static constexpr size_t kSightRange = 5;
public:
	ScaredEnemyLogic(Actor* pOwner) : Component(pOwner, s_id) {}

	//virtual void Render() override;
	virtual void Update() override;
	virtual void OnCollide() override;
};


