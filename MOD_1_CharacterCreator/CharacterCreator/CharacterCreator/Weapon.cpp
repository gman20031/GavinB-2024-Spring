#include "Weapon.h"

#include <iostream>

Weapon::Weapon(std::string name, int strength, int dexterity, int magic)
	:m_Name(name), m_Strength(strength), m_Dexterity(dexterity), m_Magic(magic)
{
}

void Weapon::PrintAttributes()
{
	std::cout << m_Name;
	std::cout << " - Strength " << m_Strength;
	std::cout << " ,Dexterity " << m_Dexterity;
	std::cout << " ,Magic " << m_Magic;
	std::cout << '\n';

}

void Weapon::SetStrength(int strength)
{
	m_Strength = strength;
}

int Weapon::GetStrength()
{
	return m_Strength;
}

void Weapon::SetDexterity(int dexterity)
{
	m_Dexterity = dexterity;
}

int Weapon::GetDexterity()
{
	return m_Dexterity;
}

void Weapon::SetMagic(int magic)
{
	m_Magic = magic;
}

int Weapon::GetMagic()
{
	return m_Magic;
}

