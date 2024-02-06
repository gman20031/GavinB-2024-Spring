#pragma once

#include "Weapon.h"

#include <string>

/*
RpgCharacter

	Member variables:
		name (string or char array)
		strength (number)
		dexterity (number)
		magic (number)
		weapon (Equipment pointer)
	Member functions:
		PrintName (prints the character’s name)
		PrintAttributes (prints all final attributes (including weapon stats))
		PrintWeapon (prints details about weapon)

*/

class RpgCharacter
{
private:
	std::string m_Name;
	int m_Strength = 0;
	int m_Dexterity = 0;
	int m_Magic = 0;
	Weapon* m_EquippedWeapon = nullptr;

public:
	void PrintName();
	void PrintAttributes();
	void PrintWeapon();
	void PrintAll();

	std::string& GetName();

	void SetWeapon(Weapon* newWeapon);
	Weapon* GetWeapon();

	void SetStrength(int strength);
	int GetStrength();

	void SetDexterity(int dexterity);
	int GetDexterity();

	void SetMagic(int magic);
	int GetMagic();
};