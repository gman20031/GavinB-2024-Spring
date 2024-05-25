#pragma once

#include <SDL.h>
#include <memory>
#include <string>
#include <unordered_set>

#include "Actor.h"

class ActorManager
{
private:
	ActorManager() = default;

	//std::vector < std::unique_ptr<Actor> > m_AllActors;
	using Container = std::unordered_set< std::unique_ptr<Actor> >;
	Container m_allActors;

public:
	ActorManager(const ActorManager&) = delete;
	ActorManager& operator=(const ActorManager&) = delete;

	const std::unique_ptr<Actor>& Create(const std::string& actorIdentifier);
	Container& GetActors() { return m_allActors; }

	void RenderAll();
	void UpdateAll();
	void StartAll();

	static ActorManager& Get();
};
