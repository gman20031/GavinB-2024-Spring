#pragma once
#include <filesystem>

#include "Actor.h"

class ActorFactory
{
private:
	using ActorCacheMap = std::unordered_map<std::string, std::vector<Component::IdType> >;
	inline static const std::filesystem::path kActorInfoPath = "Game/ActorInformation.txt";

private:
	static void FillActorMap(ActorCacheMap& actorComponentCache);
public:
	ActorFactory() = delete;

	static std::unique_ptr<Actor> Create(const std::string& actorIdentifier);

};