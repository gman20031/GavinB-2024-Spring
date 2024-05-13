#include <iostream>
#include <string>
#include <vector>
#include <conio.h>

#include "Weapon.h"
#include "Character.h"

/*
	“Sword”: strength: 5, dexterity: 2
	“Longbow”: strength: 3, dexterity: 5
	“Staff”: strength: 1, magic: 5
*/

static void PrintIntro()
{
	std::cout << "Hello welcome to the character creator\n";
	system("pause");
	system("cls");
}

static int GetMeInteger()
{
	int userIntInput;

	std::cin >> userIntInput;

	while (!std::cin.good()) // if input is not good for any reason loop
	{
		std::cout << "Please enter an integer only \n";
		std::cin.clear();													// Resets all error flags from cin
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // effectivelly clears the cin stream buffer
		std::cin >> userIntInput;
	}

	return userIntInput;
}

static void GetString(std::string& string)
{
	

}

void CreateCharacter(RpgCharacter& playerCharacter)
{
	std::cout << "What is your characters name?\n";
	std::getline(std::cin, playerCharacter.GetName() );

	std::cout << "what is your characters Strength?\n";
	playerCharacter.SetStrength(GetMeInteger());

	std::cout << "what is your characters Dexterity?\n";
	playerCharacter.SetDexterity(GetMeInteger());

	std::cout << "what is your characters Magic?\n";
	playerCharacter.SetMagic(GetMeInteger());

	system("cls");
}

static int GetIntegerInRange(int min, int max)
{
	int newMin = min + int('0');//I need to add '0'(48) because getch is a character getter
	int newMax = max + int('0');//BUT i preffer not pressing enter so I like this better.

	int input = _getch();

	while (input > newMax or input < newMin)
	{
		std::cout << "please input integer between " << min << " and " << max << '\n';
		int input = _getch();
	}
	input -= int('0');
	return input;
}

static void PickWeapon(RpgCharacter& playerCharacter, std::vector<Weapon>& weaponList)
{
	int totalWeapons = (int)weaponList.size();

	for (int i = 0; i < totalWeapons; ++i)
	{
		std::cout << i << " : ";
		weaponList.at(i).PrintAttributes();
	}
	std::cout << totalWeapons << " : No weapon\n";

	std::cout << "Which Weapon would you like to use?";
	int input = GetIntegerInRange(0,totalWeapons);

	if (input < weaponList.size())
		playerCharacter.SetWeapon(&weaponList.at(input));

	system("cls");
	return;
}

static void InitWeaponList(std::vector<Weapon>& weaponList)
{
	weaponList.emplace_back("staff", 1, 0, 5);
	weaponList.emplace_back("Long Bow", 3, 5, 0);
	weaponList.emplace_back("Sword", 5, 2, 0);
}

int main(int argv, char* argc[])
{
	RpgCharacter playerCharacter;
	std::vector<Weapon> weaponList;
	InitWeaponList(weaponList);

	PrintIntro();
	CreateCharacter(playerCharacter);
	PickWeapon(playerCharacter,weaponList);
	playerCharacter.PrintAll();
	
	system("Pause");
}

