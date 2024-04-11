#pragma once

#include "Enemy.h"

class EnemyFactory
{
	using Type = EnemyMover::MoveType;

	inline static EnemyMover s_chaseType = (Type::kChase);
	inline static EnemyMover s_runAwayType = (Type::kRunAway);

	inline static Enemy s_chasingPrototype = { '!', &s_chaseType, 0, 0, nullptr };
	inline static Enemy s_runningPrototype = { '?', &s_runAwayType, 0, 0, nullptr };

public:
	static Enemy* Create(Type moveType)
	{
		using enum Type;
		switch (moveType)
		{
		case kChase:	return s_chasingPrototype.Clone();
		case kRunAway:	return s_chasingPrototype.Clone();
		}
		
	}
};

