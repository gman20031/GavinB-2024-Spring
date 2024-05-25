#include "ActorManager.h"

#include "ActorFileIO.h"

const std::unique_ptr<Actor>& ActorManager::Create(const std::string& actorIdentifier)
{
	auto it = m_allActors.insert(ActorFileIO::Create(actorIdentifier));
	return *it.first;
}

void ActorManager::RenderAll()
{
	for (auto& actor : m_allActors)
		actor->Render();
}

void ActorManager::UpdateAll()
{
	for (auto& actor : m_allActors)
		actor->Update();
}

void ActorManager::StartAll()
{
	for (auto& actor : m_allActors)
		actor->Start();
}

ActorManager& ActorManager::Get()
{
	static ActorManager manager;
	return manager;
}
