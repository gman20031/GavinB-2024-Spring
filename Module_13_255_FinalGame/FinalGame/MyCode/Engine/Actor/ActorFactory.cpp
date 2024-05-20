#include "ActorFactory.h"

#include <fstream>

#include "../Debug.h"
#include "../System/StringHash.h"

void ActorFactory::FillActorMap(ActorCacheMap& actorComponentCache)
{
	std::fstream actorInfoFile;
	actorInfoFile.open(kActorInfoPath, std::ios_base::in);
	assert(actorInfoFile.is_open() && "Actor info file did not open");

	std::string actorIdentifier;

	while (!actorInfoFile.eof())
	{
		std::getline(actorInfoFile, actorIdentifier);
		if (actorIdentifier.back() != ':')
			continue;
		actorIdentifier.pop_back();

		if (actorComponentCache.try_emplace(actorIdentifier).second == false)
		{
			DEBUG_PRINT("Failed to emplace into actorCache" << actorIdentifier);
			continue;
		}

		while (actorInfoFile.peek() == '\t')
		{
			actorInfoFile.ignore();
			std::string componentIdentifier;
			actorInfoFile >> componentIdentifier;
			actorComponentCache[actorIdentifier].emplace_back(StringHash(componentIdentifier.c_str()));
		}
	}

	actorInfoFile.close();

}

std::unique_ptr<Actor> ActorFactory::Create(const std::string& actorIdentifier)
{
	static bool mapFilled = false;
	static ActorCacheMap actorComponentCache;

	if (!mapFilled)
	{
		FillActorMap(actorComponentCache);
		mapFilled = true;
	}

	auto it = actorComponentCache.find(actorIdentifier);
	if (it == actorComponentCache.end())
		return nullptr;
	std::unique_ptr<Actor> pActor = std::make_unique<Actor>();
	
	for (Component::IdType& id : it->second)
	{
		pActor->AddComponent(id);
	}
	
	return pActor;
}
