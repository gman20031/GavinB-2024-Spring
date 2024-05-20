#pragma once

#include <SDL.h>
#include <memory>

#include "Actor.h"

class ActorManager
{
private:
	ActorManager() = default;

	std::vector < std::unique_ptr<Actor> > m_AllActors;

public:
	ActorManager(const ActorManager&) = delete;
	ActorManager& operator=(const ActorManager&) = delete;

	std::vector<std::unique_ptr<Actor>>& GetActors() { return m_AllActors; }
	void RenderAll();

	static ActorManager& Get();
};
