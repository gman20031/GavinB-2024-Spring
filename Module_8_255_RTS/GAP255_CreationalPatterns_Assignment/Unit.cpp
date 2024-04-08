#include "Unit.h"

#include <iostream>

#include "Random.h"

///////////////////// UnitType /////////////////////



///////////////////// Unit /////////////////////

Unit::Unit(int hp, int attack, const UnitType& type)
    : m_hp( hp )
	, m_attack( attack )
    , m_type(type)
{}

Unit::Unit(const Unit& original)
	: m_type(original.m_type)
	, m_hp(original.m_hp)
	, m_attack(original.m_attack)
{

	if(m_type.m_canUse)
	{
		//attack
		if(Random::GetRandomInRange(0, 3) == 0)
			m_attackBuff  = CreateConsumable(this, ConsumableType::kAttackBuff);
		//health
		if(Random::GetRandomInRange(0, 3) == 0)
			m_healthPotion = CreateConsumable(this, ConsumableType::kHealthPotion);
	}
}

void Unit::ModifyHealth(int amount)
{
    m_hp += amount;
	std::cout << m_type.m_name << " has " << m_hp << " HP\n";

	if (m_hp <= 0)
	{
		std::cout << m_type.m_name << " is dead\n";
    }
}

void Unit::Gather() const
{
	std::cout << m_type.m_name << " gathers " << m_type.m_gatherRate << " resources\n";
}

void Unit::Attack() const
{
	std::cout << m_type.m_name << " attacks from " << m_type.m_range << " range, dealing "
		<< m_attack << " damage\n";
}

void Unit::Use() const
{
	if (!m_healthPotion and !m_attackBuff)
	{
		std::cout << "no consumables\n";
		system("pause");
		return;
	}
	if (m_healthPotion)
		std::cout << "1 : use Health Potion\n";
	if (m_attackBuff)
		std::cout << "2 : use Attack Buff\n";
	std::cout << "any other : back\n";

	int input = std::getchar();
	std::cin.ignore(std::numeric_limits<int>::max(), '\n');

	switch (input)
	{
	case '1':
		if(m_healthPotion)
			m_healthPotion->Use(); 
		break;
	case '2':
		if (m_attackBuff)
			m_attackBuff->Use();
		break;
	}

}

