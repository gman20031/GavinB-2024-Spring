#include "SDL_EventListener.h"

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
