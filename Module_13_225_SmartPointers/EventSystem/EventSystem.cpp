#include "EventSystem.h"

////////////////////////////////////////////////////////////////////////////////////
// Registers an event listener. When the specified event happens to the specified
// object, the callback will execute.
////////////////////////////////////////////////////////////////////////////////////
void EventSystem::RegisterListener(const char* pEventName,
	std::shared_ptr<EventDispatcher> pTarget, Callback callback)
{
	m_listeners.emplace_back(new EventListener{ pEventName, pTarget, callback });
}

////////////////////////////////////////////////////////////////////////////////////
// All listeners that share an event name and target with the specified event will
// execute.
////////////////////////////////////////////////////////////////////////////////////
void EventSystem::DispatchEvent(std::shared_ptr<Event> pEvent)
{
	for (std::shared_ptr<EventListener> pListener : m_listeners)
	{
		if (pListener->m_pTarget == pEvent->m_pTarget
			&& pListener->m_eventName == pEvent->m_eventName)
		{
			pListener->m_callback(pEvent);
		}
	}
}
