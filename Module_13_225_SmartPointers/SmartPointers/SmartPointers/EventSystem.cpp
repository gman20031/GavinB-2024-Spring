#include "EventSystem.h"

////////////////////////////////////////////////////////////////////////////////////
// Registers an event listener. When the specified event happens to the specified
// object, the callback will execute.
////////////////////////////////////////////////////////////////////////////////////
void EventSystem::RegisterListener(const char* pEventName,
	std::weak_ptr<EventDispatcher> pTarget, CallbackFunction callback)
{
	m_listeners.emplace_back(std::make_unique<EventListener>( pEventName, pTarget, callback) );
}

////////////////////////////////////////////////////////////////////////////////////
// All listeners that share an event name and target with the specified event will
// execute.
////////////////////////////////////////////////////////////////////////////////////
void EventSystem::DispatchEvent(std::shared_ptr<Event> pEvent)
{
	for (auto& pListener : m_listeners)
	{
		if ( pListener->m_eventName == pEvent->m_eventName)
		{
			pListener->m_callback(pEvent);
		}
	}
}
