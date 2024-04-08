#pragma once

#include <string>
#include <unordered_map>

#include "Potions.h"

struct UnitType
{
	std::string m_name;
	const int m_gatherRate;
	const int m_range;
	const bool m_canUse;
};


class Unit
{
private:
	friend void RunConsumablesTest();
	bool m_guaranteePotion = false;

	const UnitType& m_type;
    int m_hp;
	int m_attack;

	Consumable* m_healthPotion = nullptr;
	Consumable* m_attackBuff = nullptr;

public:
    Unit(int hp, int attack, const UnitType& type);
	Unit(const Unit& original);

	const std::string& GetName() { return m_type.m_name; }

    void ModifyHealth(int amount);
	void ModifyAttack(int amount) { m_attack += amount; }

    void Gather() const;
    void Attack() const;

	void Use() const;
};

