#pragma once

#include <string>
#include <unordered_map>

#include "Potions.h"

struct UnitConfig
{
	const char* m_name;
	const int m_gatherRate;
	const int m_range;
	const bool m_canUse;
};


class Unit
{
private:
#if TEST_MODE
	friend void RunConsumablesTest();
	friend void AddUnit(Unit** pUnit, const char* type);
#endif
	bool m_guaranteePotion = false;

	const UnitConfig& m_type;
    int m_hp;
	int m_attack;

	Consumable* m_healthPotion = nullptr;
	Consumable* m_attackBuff = nullptr;

public:
    Unit(int hp, int attack, const UnitConfig& type);
	Unit(const Unit& original);

	const std::string& GetName() { return m_type.m_name; }

    void ModifyHealth(int amount);
	void ModifyAttack(int amount);

    void Gather() const;
    void Attack() const;

	Unit* Clone() const;
	void Use();
};

