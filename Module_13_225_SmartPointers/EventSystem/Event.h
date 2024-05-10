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
	// The object that the event "happened to"
	std::shared_ptr<EventDispatcher> m_pTarget;

	// The kind of event.
	std::string m_eventName;

	// Constructor
	Event(const char* pEventName)
		: m_eventName{ pEventName }
	{
	}
};

