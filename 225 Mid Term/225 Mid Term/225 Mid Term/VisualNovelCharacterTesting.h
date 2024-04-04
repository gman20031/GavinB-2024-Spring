#pragma once

#include <iostream>
#include <string>

void Test(const char* pTestName, bool test)
{
	std::cout << pTestName << ": " << (test ? "SUCCESS" : "FAILURE") << std::endl;
}

void RunVisualNovelCharacterTests()
{
#if 1
	//In addition, you must be able to set all variables in some way when creating instances of this class. (3)
	//Each character has a unique name and a unique ID number(1)

	VisualNovelCharacter firstCharacter("Joe", 0);
	Test("Character named correctly", firstCharacter.GetName() == "Joe");
	Test("Character ID'd correctly", firstCharacter.GetId() == 0);

	VisualNovelCharacter nonUniqueCharacter("Joe", 1);
	Test("Cannot create non unique Name", nonUniqueCharacter.GetName() == "ERROR");

	VisualNovelCharacter nonUniqueID("nonUniqueID", 1);
	Test("Cannot create non Uniqe ID", nonUniqueID.GetId() == 2);

	firstCharacter.SetName("Geoff");
	Test("Character renamed correctly", firstCharacter.GetName() == "Geoff");

	VisualNovelCharacter secondCharacter("jack black", 3);
	Test("GetName formatted correctly", secondCharacter.GetName() == "Jack Black");

	std::string characterName = "Jonah Jameson";
	VisualNovelCharacter thirdCharacter(characterName, 4);
	Test("Initialized with std::string", thirdCharacter.GetName() == "Jonah Jameson");

#endif // 0


}