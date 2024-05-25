#pragma once

#include <SDL.h>
#include <concepts>
#include <unordered_map>
#include <memory>
#include <vector>
#include <functional>

class SDLEventObserver
{
private:
	std::unordered_map< SDL_EventType, std::vector< std::function<bool(SDL_Event)> > > m_listenerMap;
public:
	template<std::predicate<SDL_Event> Function>
	void RegisterListener(Function&& listenFunction, SDL_EventType eventType);

	void PushEvent(SDL_Event event);
};

template<std::predicate<SDL_Event> Function>
inline void SDLEventObserver::RegisterListener(Function&& listenFunction, SDL_EventType eventType)
{
	m_listenerMap[eventType].emplace_back( listenFunction );
}
