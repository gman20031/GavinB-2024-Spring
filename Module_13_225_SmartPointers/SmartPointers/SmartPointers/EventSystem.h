#pragma once

#include <functional>
#include <string>
#include <vector>

#include "Event.h"

class EventDispatcher;

////////////////////////////////////////////////////////////////////////////////////
// Manages event listeners and dispatches events to them.
////////////////////////////////////////////////////////////////////////////////////
class EventSystem
{
public:
	using CallbackFunction = std::function<void(std::shared_ptr<Event>)>;

private:
	struct EventListener
	{
		std::string m_eventName;
		std::weak_ptr<EventDispatcher> m_pTarget;
		CallbackFunction m_callback;
	};

private:
	std::vector<std::unique_ptr<EventListener>> m_listeners;

public:
	EventSystem() = default;
	~EventSystem() = default;

	void RegisterListener(const char* pEventName, std::weak_ptr<EventDispatcher> pTarget, CallbackFunction callback);
	void DispatchEvent(std::shared_ptr<Event> pEvent);
};

