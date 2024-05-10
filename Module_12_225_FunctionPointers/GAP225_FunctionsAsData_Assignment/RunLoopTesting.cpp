#include "Tasks.h"

#include <concepts>
#include <iostream>

#include "SimpleIO.h"
#include "ConsoleManip.h"

/*
Task 2. RunLoop

Write a function called RunLoop that takes in three parameters:

	an int (n)
	a void() function pointer (iterationCall)
	another void() function pointer (endCall)

*/

//static void RunLoop(int count, void(*IterationCall)(), void(*EndCall)())
//{
//	for (int i = 0; i < count; ++i)
//		IterationCall();
//	EndCall();
//}

template<std::invocable<int> ItFunc, std::invocable<int> EndFunc>
static void Templated_RunLoop(int count, ItFunc&& iterationCall, EndFunc&& endCall )
{
	int i = 0;
	for ( ; i < count; ++i)
		iterationCall(i);
	endCall(i);
}

template<std::predicate<int> Predicate, class EndFunc>
static void RunLoopWithCondition(int count, Predicate&& checker, EndFunc&& endCall)
{
	for (int i = 0; i < count; ++i)
	{
		if (checker(i))
		{
			endCall(i);
			return;
		}
	}
}

void RunLoopTesting()
{
	std::cout << "Iterating 10 times, printing iteration number, then calling endCall. No special end conditions\n";
	ConsoleManip::Pause();

	Templated_RunLoop( 10 ,
		[](int i)
		{
			std::cout << "iteration: " << i << '\n';
		}
	   ,[](int i)
		{
			std::cout << "ended at iteration: " << i << '\n';
		}
	);

	std::cout << "same but ending if iteration is greater than 5\n";
	ConsoleManip::Pause();

	RunLoopWithCondition( 10 ,
		[](int i)->bool
		{
			std::cout << "iteration: " << i << '\n';
			return (i > 5);
		}
	   ,[](int i)
		{
			std::cout << "ended at iteration: " << i << '\n';
		}
	);

	ConsoleManip::Pause();
}
