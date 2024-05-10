#pragma once

#include <string>
#include "../Engine/ActorTags.h"


struct GameTag
{
	inline static std::string kEmpty  = "empty";
	inline static std::string kPlayer = "player";
	inline static std::string kEnemy  = "enemy";
	inline static std::string kTreasure = "treasure";
};

