#include "SDL_EventListener.h"

//void SDLEventObserver::RegisterListener(CallbackFunction listenFunction, SDL_EventType eventType)
//{
//	m_listenerMap[eventType].emplace_back( std::make_unique<EventListener>(listenFunction) );
//}

void SDLEventObserver::PushEvent(SDL_Event event)
{
	SDL_EventType type = (SDL_EventType)event.type;
	auto it = m_listenerMap.find(type);
	if (it == m_listenerMap.end())
		return;

	for (auto& listener : it->second)
	{
		listener(event);
	}

}
