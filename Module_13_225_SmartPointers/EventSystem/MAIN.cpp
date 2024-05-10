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

#include "Event.h"
#include "EventDispatcher.h"
#include <vld.h>

////////////////////////////////////////////////////////////////////////////////////
// Entry point.
////////////////////////////////////////////////////////////////////////////////////
int main()
{
	// Create an event system.
	auto pEventSystem = std::make_shared<EventSystem>();

	// Create an event-powered object (a button) and add a listener that will execute
	// when the button is activated.
	auto pButton = std::make_shared<EventDispatcher>("button", pEventSystem);
	pButton->AddEventListener("activate", [](std::shared_ptr<Event> pEvent)->void
	{
		// All that will happen is it will print this message.
		std::cout << "Clicked on " << pEvent->m_pTarget->GetName() << std::endl;
	});

	// Let's keep track of how many times the event has been dispatched
	// (for debugging).
	int dispatchCount = 0;

	// A loop for testing.
	while (true)
	{
		// Two kinds of input.
		enum Input : char
		{
			kActivate = '1',
			kQuit = '2'
		};

		// Print directions for testing.
		std::cout << "Press " << (char)Input::kActivate << " to activate the button or "
			<< (char)Input::kQuit << " to quit." << std::endl;

		// When this is true, the loop will break.
		bool exit = false;

		// Parse input.
		wint_t choice = _getwch();
		switch (choice)
		{
			// This dispatches an "activate" event on the button.
			case Input::kActivate:
			{
				++dispatchCount;
				auto pEvent = std::make_shared<Event>("activate");
				pButton->DispatchEvent(pEvent);
				break;
			}
			// This ends the program.
			case Input::kQuit:
			{
				exit = true;
				break;
			}
		}

		if (exit)
		{
			break;
		}
	}
	
	// Print the number of dispatched events (for debugging)
	std::cout << "You dispatched a total of " << dispatchCount << " events." << std::endl;
	system("pause");
	return 0;
}