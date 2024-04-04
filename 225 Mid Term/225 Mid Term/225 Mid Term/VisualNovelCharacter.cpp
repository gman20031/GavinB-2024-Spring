#include "VisualNovelCharacter.h"

#include <iostream>



static void CapitialzeFirstLetters(std::string& string);

VisualNovelCharacter::VisualNovelCharacter(const std::string& name, int id)
	: m_name(name)
	, m_id(id)
{
	EnsureUnique();
	CapitialzeFirstLetters(m_name);
}

void VisualNovelCharacter::EnsureUnique()
{
	static std::vector<int> s_characterIds;
	static std::vector<std::string*> s_allNames;
	static int s_characterCount = 0;
	++s_characterCount;

	if (s_characterCount != 1)
	{
		for (auto& id : s_characterIds)
		{
			if (id == m_id)
			{
				++m_id;
				EnsureUnique();
				return;
			}
		}
		for (auto& name : s_allNames)
		{
			if (*name == m_name)
				m_name = "ERROR";
		}
	}

	s_characterIds.push_back(m_id);
	s_allNames.push_back(&m_name);
}

////////////////////////////////////////////////////////////////////
/// if the character is a lowercase alphabetical letter it 
/// is converted to uppercase and returned
/// else just retrurns input
////////////////////////////////////////////////////////////////////
static char EnsureUpperCase(char character)
{
	constexpr int a_value = 'a';
	constexpr int z_value = 'z';
	constexpr int A_value = 'A';
	constexpr int CapitalDifference = a_value - A_value; // 97 - 65 = 32

	if (character <= z_value and character >= a_value)
		character -= CapitalDifference;

	return character;
}

////////////////////////////////////////////////////////////////////
/// returns the string with every alphabetical character uppercase
////////////////////////////////////////////////////////////////////
static std::string AllUpperCase(const std::string& string)
{
	std::string output = string;
	for (auto& character : output)
		character = EnsureUpperCase(character);
	return output;
}

////////////////////////////////////////////////////////////////////
/// calls EnsureUpperCase() to uppercase
/// Always capitlizes element 0
/// capitlizes first character after any spaces
////////////////////////////////////////////////////////////////////
void CapitialzeFirstLetters(std::string& string)
{
	string[0] = EnsureUpperCase(string[0]);

	bool spaceFound = false;
	for (auto& character : string)
	{
		if (character == ' ')
		{
			spaceFound = true;
			continue;
		}
		if (spaceFound)
		{
			character = EnsureUpperCase(character);
			spaceFound = false;
		}
	}
}

////////////////////////////////////////////////////////////////////
/// Prints out the text in the format of
/// CharacterName(all Uppercase) : dialog
////////////////////////////////////////////////////////////////////
void VisualNovelCharacter::Say(const std::string& dialog) const
{
	std::cout << AllUpperCase(m_name) << " : " << dialog << '\n';
}

////////////////////////////////////////////////////////////////////
/// Prints out the text in the format of
/// CharacterName(all Uppercase) : dialog
////////////////////////////////////////////////////////////////////
void VisualNovelCharacter::Say(const char* dialog) const
{
	std::string strDialog = dialog;
	Say(strDialog);
}