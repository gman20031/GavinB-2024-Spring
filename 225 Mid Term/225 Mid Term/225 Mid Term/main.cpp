#include <iostream>

#define TEST_MODE 1
#include "VisualNovelCharacter.h"

#if TEST_MODE
#include "VisualNovelCharacterTesting.h"
#endif // TEST_MODE



int main()
{
#if TEST_MODE
	RunVisualNovelCharacterTests();
#endif // TEST_MODE

std::cout << "\n\ndialog test \n";
	VisualNovelCharacter Aiden("aiden calvin", 0);
	VisualNovelCharacter Nick("nick vercillo", 1);

	std::string AidenLineOne = "hey " + Nick.GetName() + ", what have you been doing.";
	Aiden.Say(AidenLineOne);

	std::string NickLineOne = "Oh hey " + Aiden.GetName() + "just being cool, you know how it is.";
	Nick.Say(NickLineOne);

	Aiden.Say("You ever get the feeling that your written by some terrible author.");
	Nick.Say("Never.");
	Aiden.Say("yeah me neither.");
	Nick.Say("Then why'd you ask?");
	Aiden.Say("I DONT KNOW.");
	Nick.Say("WELL I DONT KNOW EITHER!");
	Aiden.Say("*shoots Nick with a gun*");

	return 0;
}



//Write a class to represent a character in a dialog - based visual novel.
//Each character has a unique name and a unique ID number(1)
//The character’s name should appear in ALL CAPS when they are speaking. (1)
//Their name should appear with only the initial letters capitalized when other people say their name. (1)
//Have at least the following public functions :
//	Say(3)
//	Takes in a dialog string to say.The dialog should print to the console in the format NAME : dialog
//	replace NAME with the character’s name in all caps
//	replace dialog with the passed - in string
//	end the line after dialog is printed
//	GetName(3)
//	Returns the character’s name in basic English style, i.e.with the initial letter of each word capitalized.Example : John Doe
// 
//	In addition, you must be able to set all variables in some way when creating instances of this class. (3)
//	Apply all best practices to the creation of this class. (points for this are included in other items)
//	Demonstrate the use of the class in main by creating two characters and have them each speak to other, using the other’s name. (3)
