#include <iostream>
#include <string>
#include <vector>
#include "Vectors.h"

#include "Toggle.h"


void Test(std::string test, bool pass)
{
	std::cout << test << " : ";
	pass ? std::cout << "PASS" : std::cout << "FAIL";
	std::cout << '\n';
}

/*
TASK 1: (5)
- Create a file called Toggle.h, and implement this class.
NAME: Toggle
PURPOSE: To store two values, then alternate which one gets returned by the Get function.
DETAILS:
- Store two values of any data type (both are the same type)
- Must have these public members:
	- Constructor(val1, val2) - assigns val1 and val2 as the toggle values.
	- Get() - returns the currently selected toggle value
	- Toggle() - switches over to the other value. Returns nothing.

EXAMPLE: Toggle<int> could have 5 and 10. Get() will return 5, but after calling Toggle(); Get() will return 10.
THIS TASK IS DONE WHEN: I can generate toggles of any data types I choose, such as int, bool or Foo.
*/

void TestTaskOne()
{
	std::cout << "Testing Toggle.h\n\n";

	Toggle<int> toggle(5, 10);
	Test("gets first val", toggle.Get() == 5);
	toggle.ToggleValue();
	Test("toggled gets second val", toggle.Get() == 10);

	Toggle<double> toggle2(10.523, 266.44);
	Test("gets first val", toggle2.Get() == 10.523);
	toggle2.ToggleValue();
	Test("toggled gets second val", toggle2.Get() == 266.44);
	std::cout << '\n';
}



/*
TASK 2: (15)
- In Game.h, implement the functions Game::Save and Game::Load.
- The Save function should write the player's state to a file, and the Load function should restore the player's state from that file.
- Program the 'p' button to call the Save function.
- Program the 'o' button to call the Load function.
THIS TASK IS DONE WHEN: When I start the game, move a few times, change color, save, quit, and load the game, the game will be in the same state as when I saved it.
*/



/*
TASK 3: (10)
- Create a file called Trigger.h and implement this class.
NAME: Trigger
PURPOSE: This class implements a game trigger that can have any effect injected into it.
DETAILS:
- Implement this as a class.
- Store a position, e.g. a Vector2<size_t>.
- Is dependent on the Player class from Game.h (you will need to #include Game.h)
- We will use the word 'effect' to describe a function with this signature: void(Player*)
- Functions:
	- ctor(x, y, appearance, effect)
		- effect: a function that will execute when the trigger is stepped on by a Player
	- void SetEffect(newEffect)
		- newEffect: a new function that will replace the existing effect function.
	- void OnStep(Player* pPlayer)
		- SIDE EFFECT: This calls ExecuteEffect, passing in pPlayer.
	- void Draw()
		- SIDE EFFECT: Draws the trigger's appearance (as a char).
*/

/*
TASK 4: (5)
- Must have completed TASK 3.
- Add a std::array of trigger objects to the Game class. Place 2 trigger objects in this array.
- Set up one trigger to change the direction of the player. It should appear as '?'.
- Set up the other trigger to change the color of the player. It should appear as '%'.
- Test both triggers!
THIS TASK IS DONE WHEN: I can play the game and both triggers work as described.
*/


/*
TASK 5: (5)
- Create a file named Vectors.h and write this function:
PURPOSE: To remove all even numbers from a std::vector
PARAMETERS: a std::vector<int>
SIDE EFFECTS: all even numbers are removed from the vector
RETURNS: the number of removed values

*/
#if 1


void TestTaskFive()
{
	std::cout << "Testing RemoveEvens()\n\n";


	std::vector<int> vectorOne{1, 2, 3, 4};
	size_t removedElements = RemoveEvens(vectorOne);
	Test("removed even Numbers", vectorOne == std::vector<int>{1, 3});
	Test("result is correct", removedElements == 2);

	std::vector<int> vectorAllEven{ 20, 2, 8, 4 };
	removedElements = RemoveEvens(vectorAllEven);
	Test("removed all numbers for all even", vectorAllEven == std::vector<int>{});
	Test("result is correct", removedElements == 4);

	std::vector<int> vectorAllOdd{ 35, 15, 17, 1 };
	removedElements = RemoveEvens(vectorAllOdd);
	Test("removed no Numbers for all odd", vectorAllOdd == std::vector<int>{ 35, 15, 17, 1 });
	Test("result is correct", removedElements == 0);

	std::cout << '\n';
}

#endif
/*
TASK 6: (5)
- Create a file named Vectors.h (or reuse the one from task 5) and write this function:
PURPOSE: To add a zero before all odd numbers in a std::vector
PARAMETERS: a std::vector<int>
SIDE EFFECTS: all odd numbers receive a 0 before them
RETURNS: the number of added zeroes
*/
#if 1

void TestTaskSix()
{
	std::cout << "Testing AddZeroBeforOdd()\n\n";


	std::vector<int> vectorOne{ 1, 2, 3, 4 };
	size_t removedElements = AddZeroBeforOdd(vectorOne);
	Test("Added Zeros before odds", vectorOne == std::vector<int>{0, 1, 2, 0 , 3 , 4});
	Test("result is correct", removedElements == 2);

	std::vector<int> vectorAllEven{ 20, 2, 8, 4 };
	removedElements = AddZeroBeforOdd(vectorAllEven);
	Test("Added no zeros in all even vector ", vectorAllEven == std::vector<int>{ 20, 2, 8, 4} );
	Test("result is correct", removedElements == 0);

	std::vector<int> vectorAllOdd{ 35, 15, 17, 1 };
	removedElements = AddZeroBeforOdd(vectorAllOdd);
	Test("Added zeros to all odd vector", vectorAllOdd == std::vector<int>{ 0,35, 0, 15, 0, 17, 0, 1 });
	Test("result is correct", removedElements == 4);
	
	std::cout << '\n';
}

#endif
