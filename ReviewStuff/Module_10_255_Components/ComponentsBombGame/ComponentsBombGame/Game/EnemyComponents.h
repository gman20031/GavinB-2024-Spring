#pragma once

#include "../System/Vector2d.h"
#include "../Engine/ComponentFactory.h"


class DirectEnemyLogic : public Component
{
	NEW_STATIC_ID;
private:
	Vector2d<int> m_oldPosition;
	static constexpr size_t kSightRange = 5;
public:
	DirectEnemyLogic(Actor* pOwner) : Component(pOwner, s_id) , m_oldPosition(0,0){}

		//virtual void Render() override;
	virtual void Update() override;
	virtual void OnCollide() override;
};

class ScaredEnemyLogic : public Component
{
	NEW_STATIC_ID;
private:
	Vector2d<int> m_oldPosition;
	static constexpr size_t kSightRange = 5;
public:
	ScaredEnemyLogic(Actor* pOwner) : Component(pOwner, s_id), m_oldPosition(0,0){}

	//virtual void Render() override;
	virtual void Update() override;
	virtual void OnCollide() override;
};


