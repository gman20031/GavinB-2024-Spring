#include "Unit.h"

#include <iostream>


///////////////////// Unit /////////////////////

Unit::Unit(int hp, int attack, int range, int gatherRate, const char* name)
	: m_hp(hp)
	, m_attack(attack)
	, m_name(name)
	, m_range(range)
	, m_gatherRate(gatherRate)
{

}

void Unit::ModifyHealth(int amount)
{
    m_hp += amount;
	std::cout << m_name << " has " << m_hp << " HP\n";

	if (m_hp <= 0)
	{
		std::cout << m_name << " is dead\n";
    }
}

void Unit::ModifyAttack(int amount)
{
	m_attack += amount;
	std::cout << m_name << " has " << m_attack << " Attack\n";

}

void Unit::Gather() const
{
	std::cout << m_name << " gathers " << m_gatherRate << " resources\n";
}

void Unit::Attack() const
{
	std::cout << m_name << " attacks from " << m_range << " range, dealing "
		<< m_attack << " damage\n";
}

bool operator<(const Unit& lhs, const Unit& rhs)
{
	return(lhs.m_hp < rhs.m_hp);
}

std::ostream& operator<<(std::ostream& os, const Unit& unit)
{
	os << unit.m_name << "{";
	os << unit.m_hp << ',' << unit.m_attack << ',' << unit.m_gatherRate << ',' << unit.m_range << "}";
	return os;
}