#pragma once

#include <string>

/*
Weapon

	Member variables:
		name (string or char array)
		strength (number)
		dexterity (number)
		magic (number)
	Member function:
		Print (prints the values of all variables in a readable way)

*/

class Weapon
{
private:
	std::string m_Name;
	int m_Strength;
	int m_Dexterity;
	int m_Magic;

public:
	Weapon(std::string name, int strength, int dexterity, int magic);

	void PrintAttributes();

	void SetStrength(int strength);
	int GetStrength();

	void SetDexterity(int dexterity);
	int GetDexterity();

	void SetMagic(int magic);
	int GetMagic();
};