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
	std::string m_name;
	std::shared_ptr<EventSystem> m_pEventSystem;
public:
	EventDispatcher(const char* pName, std::shared_ptr<EventSystem> pEventSystem);
	~EventDispatcher() = default;

	void AddEventListener(const char* pEventName, EventSystem::CallbackFunction callback);
	void DispatchEvent(std::shared_ptr<Event> pEvent);

	// The object's name (not a core part of this system)
	std::string& GetName() { return m_name; }
};

