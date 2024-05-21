#pragma once

#include <SDL.h>
#include <concepts>
#include <unordered_map>
#include <memory>
#include <vector>
#include <functional>

//template<typename T>
//concept SDLEventObserverCallable = std::predicate<SDL_Event>;

class SDLEventObserver
{
public:
	//using CallbackFunction = bool(*)(SDL_Event);
private:
	//class EventListener
	//{
	//	CallbackFunction m_callback;
	//public:
	//	EventListener(CallbackFunction callback) : m_callback(callback) {};
	//	bool operator()(SDL_Event event) { return m_callback(event); }
	//};

	//std::unordered_map<SDL_EventType, std::vector<std::unique_ptr<EventListener> > > m_listenerMap;
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
