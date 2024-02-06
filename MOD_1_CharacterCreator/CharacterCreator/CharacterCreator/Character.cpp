#include "Character.h"

#include <iostream>

#define Print(str) std::cout << str << std::endl;

void RpgCharacter::PrintName()
{
	Print(m_Name);
}

void RpgCharacter::PrintAttributes()
{
	Print("Strength : " << m_Strength);
	Print("Dexterity: " << m_Dexterity);
	Print("Magic    : " << m_Magic);
}

void RpgCharacter::PrintWeapon()
{
	if (m_EquippedWeapon == nullptr)
		std::cout << "No weapon Equipped\n";
	else
		m_EquippedWeapon->PrintAttributes();
}

void RpgCharacter::PrintAll()
{
	PrintName();
	PrintAttributes();
	PrintWeapon();
}


//////////////////////////////////////////
/// Set and Get
//////////////////////////////////////////

std::string& RpgCharacter::GetName()
{
	return m_Name;
}

void RpgCharacter::SetWeapon(Weapon* newWeapon)
{
	if (m_EquippedWeapon != nullptr)
	{
		m_Strength -= m_EquippedWeapon->GetStrength();
		m_Dexterity -= m_EquippedWeapon->GetDexterity();
		m_Magic -= m_EquippedWeapon->GetMagic();
	}

	m_EquippedWeapon = newWeapon;

	m_Strength += m_EquippedWeapon->GetStrength();
	m_Dexterity += m_EquippedWeapon->GetDexterity();
	m_Magic += m_EquippedWeapon->GetMagic();
}

Weapon* RpgCharacter::GetWeapon()
{
	return m_EquippedWeapon;
}

void RpgCharacter::SetStrength(int strength)
{
	m_Strength = strength;
}

int RpgCharacter::GetStrength()
{
	return m_Strength;
}

void RpgCharacter::SetDexterity(int dexterity)
{
	m_Dexterity = dexterity;
}

int RpgCharacter::GetDexterity()
{
	return m_Dexterity;
}

void RpgCharacter::SetMagic(int magic)
{
	m_Magic = magic;
}

int RpgCharacter::GetMagic()
{
	return m_Magic;
}
