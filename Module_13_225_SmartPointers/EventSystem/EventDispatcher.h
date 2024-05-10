#pragma once

#include <functional>
#include <string>

#include "EventSystem.h"

////////////////////////////////////////////////////////////////////////////////////
// An object that is capable of experiencing events. Functions can be attached to
// this object and execute when a specified event happens. For example, you can
// add a listener function for when this object is clicked on.
////////////////////////////////////////////////////////////////////////////////////
class EventDispatcher : public std::enable_shared_from_this<EventDispatcher>
{
private:
	// The object's name (not a core part of this system)
	std::string m_name;

	// A pointer to the Event System to which all events are relayed.
	std::shared_ptr<EventSystem> m_pEventSystem;

public:
	EventDispatcher(const char* pName, std::shared_ptr<EventSystem> pEventSystem);
	~EventDispatcher() = default;

	// The object's name (not a core part of this system)
	std::string& GetName() { return m_name; }

	void AddEventListener(const char* pEventName, EventSystem::Callback callback);
	void DispatchEvent(std::shared_ptr<Event> pEvent);
};

