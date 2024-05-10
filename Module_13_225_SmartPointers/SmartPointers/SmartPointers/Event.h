#pragma once

#include <memory>
#include <string>

class EventDispatcher;

////////////////////////////////////////////////////////////////////////////////////
// Represents the activation of an event, such as clicking on a button. Contains
// basic data about the event. Could be subclassed to add more data for more
// specific events.
////////////////////////////////////////////////////////////////////////////////////
struct Event
{
	std::weak_ptr<EventDispatcher> m_pTarget;
	std::string m_eventName;

	Event(const char* pEventName)
		: m_eventName{ pEventName }
	{
	}
};

