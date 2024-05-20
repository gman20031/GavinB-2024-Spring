#include "ActorManager.h"

void ActorManager::RenderAll()
{
	for (auto& actor : m_AllActors)
		actor->Render();
}

ActorManager& ActorManager::Get()
{
	static ActorManager manager;
	return manager;
}
