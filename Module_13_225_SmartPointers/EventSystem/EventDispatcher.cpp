#include "EventDispatcher.h"

////////////////////////////////////////////////////////////////////////////////////
// Constructor.
////////////////////////////////////////////////////////////////////////////////////
EventDispatcher::EventDispatcher(const char* pName, std::shared_ptr<EventSystem> pEventSystem)
	: m_name{ pName }
	, m_pEventSystem{ pEventSystem }
{
}

////////////////////////////////////////////////////////////////////////////////////
// Begins listening for the specified event to happen to this object. Once the event
// happens, the callback will execute and receive basic info about the event.
////////////////////////////////////////////////////////////////////////////////////
void EventDispatcher::AddEventListener(const char* pEventName,
	EventSystem::Callback callback)
{
	m_pEventSystem->RegisterListener(pEventName, shared_from_this(), callback);
}

////////////////////////////////////////////////////////////////////////////////////
// Notifies this object that the event has happened. This event will assign itself
// as the target of the event.
////////////////////////////////////////////////////////////////////////////////////
void EventDispatcher::DispatchEvent(std::shared_ptr<Event> pEvent)
{
	pEvent->m_pTarget = shared_from_this();
	m_pEventSystem->DispatchEvent(pEvent);
}
