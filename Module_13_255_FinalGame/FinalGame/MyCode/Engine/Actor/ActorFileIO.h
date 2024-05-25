#pragma once
#include <filesystem>

#include "Actor.h"

class ActorFileIO
{
private:
	using ActorCacheMap = std::unordered_map<std::string, std::vector<Component::IdType> >;
	inline static const std::filesystem::path kActorInfoPath = "Game/ActorInformation.txt";
private:
	static void FillActorMap(ActorCacheMap& actorComponentCache);
	static ActorCacheMap& GetMap();
public:
	ActorFileIO() = delete;

	static std::unique_ptr<Actor> Create(const std::string& actorIdentifier);
	//static bool Save(const std::string& actorIdentifier, const std::unique_ptr<Actor>& actor);
	
};