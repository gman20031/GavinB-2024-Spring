/*

//// GAP 225 Smart Pointer Assignment ////

This program works, but has problems due to incorrect uses of smart pointers.
The problems are:

- a bad_weak_ptr exception occurs when you run it in its current form. You might
have to research it.

- there are various memory leaks (as detected by VLD), which proves that the smart
pointers are not doing their jobs.

Fix these problems and victory is yours!
Rules:
- you can only replace smart pointer variables with other kinds of smart pointers,
	e.g. a shared_ptr<Foo> can be replaced with a weak_ptr<Foo> but not with Foo or
	Foo*.
- you cannot use new or delete anywhere.

//////////////////////////////////////////

Here's how this event system basically works:

- An Event is defined as "any named occurrence that happens to an object."
- The term "listener" refers to a function that executes when event X happens to
	object Y. (If event X happens to object Z or event W happens to object Y, the
	listener will not execute; both have to match.)
- The EventSystem manages events and functions that are listening to them.
- An EventDispatcher is any object that can have events happen to it.

To register an event listener:

- Call addEventListener() on the targetted EventDispatcher ("when event X happens
	to you, I want function F to be called")
- This calls EventSystem::RegisterListener, which creates an EventListener object.
- The EventListener has to store a pointer to the EventDispatcher to know which
	object it's listening to.

To make an event happen:

- Call DispatchEvent() on the targetted EventDispatcher ("event X is happening to you
	NOW!")
- This calls EventSystem::DispatchEvent, which checks all listeners for the right
	combination of event X and target object Y.
- If a matching listener is found, the callback executes.

//////////////////////////////////////////////////////////

*/

#include <conio.h>
#include <iostream>
#include <memory>
#include <vld.h>

#include "Event.h"
#include "EventDispatcher.h"

int main()
{
	std::shared_ptr<EventSystem>	 pEventSystem = std::make_shared<EventSystem>();
	std::shared_ptr<EventDispatcher> pButton	  = std::make_shared<EventDispatcher>("button", pEventSystem);

	pButton->AddEventListener("activate", [](std::shared_ptr<Event> pEvent)->void
	{
		auto pTarget = pEvent->m_pTarget.lock();
		std::cout << "Clicked on " << pTarget->GetName() << std::endl;
	});

	int dispatchCount = 0;
	bool exit = false;
	while (!exit)
	{
		enum Input : char
		{
			kActivate = '1',
			kQuit = '2'
		};
	
		std::cout << "Press " << (char)Input::kActivate << " to activate the button or "
			<< (char)Input::kQuit << " to quit." << std::endl;
	
		wint_t choice = _getwch();
		switch (choice)
		{
			case Input::kActivate:
			{
				++dispatchCount;
				auto pEvent = std::make_shared<Event>("activate");
				pButton->DispatchEvent(pEvent);
				break;
			}
			case Input::kQuit:
			{
				exit = true;
				break;
			}
		}
	}

	std::cout << "You dispatched a total of " << dispatchCount << " events." << std::endl;
	system("pause");
	return 0;
}