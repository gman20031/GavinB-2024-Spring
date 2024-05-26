#include "ActorFileIO.h"

#include <fstream>

#include "../Debug.h"
#include "../System/StringHash.h"

void ActorFileIO::FillActorMap(ActorCacheMap& actorComponentCache)
{
	std::fstream actorInfoFile;
	actorInfoFile.open(kActorInfoPath, std::ios_base::in);
	assert(actorInfoFile.is_open() && "Actor info file did not open");

	std::string actorIdentifier;

	while (!actorInfoFile.eof())
	{
		std::getline(actorInfoFile, actorIdentifier);
		if (actorIdentifier.empty())
			continue;
		if (actorIdentifier.back() != ':')
			continue;
		actorIdentifier.pop_back();

		if (actorComponentCache.try_emplace(actorIdentifier).second == false)
		{
			DEBUG_PRINT("Failed to emplace into actorCache" << actorIdentifier);
			continue;
		}

		std::string componentIdentifier;
		while (actorInfoFile.peek() == '\t')
		{
			actorInfoFile.ignore();
			std::getline(actorInfoFile, componentIdentifier);
			actorComponentCache[actorIdentifier].emplace_back( StringHash( componentIdentifier.c_str() ) );
		}
	}
	actorInfoFile.close();
}

ActorFileIO::ActorCacheMap& ActorFileIO::GetMap()
{
	static ActorCacheMap map;
	static bool mapFilled = false;
	if (!mapFilled)
	{
		FillActorMap(map);
		mapFilled = true;
	}
	return map;
}

std::unique_ptr<Actor> ActorFileIO::Create(const std::string& actorIdentifier)
{
	ActorCacheMap& map = GetMap();

	auto it = map.find(actorIdentifier);
	if (it == map.end())
		return nullptr;
	std::unique_ptr<Actor> pActor = std::make_unique<Actor>();
	
	for (Component::IdType& id : it->second)
	{
		pActor->AddComponent(id);
	}
	
	return pActor;
}