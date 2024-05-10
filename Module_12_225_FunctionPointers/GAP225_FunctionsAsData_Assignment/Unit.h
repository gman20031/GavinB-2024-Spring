#pragma once

#include <string>
#include <unordered_map>

class Unit
{
	friend bool operator<(const Unit& lhs, const Unit& rhs);
	friend std::ostream& operator<<(std::ostream& os, const Unit& unit);
private:
    int m_hp;
	int m_attack;
	int m_gatherRate;
	int m_range;
	std::string m_name;

public:
    Unit(int hp, int attack, int range, int gatherRate, const char* name);

	const std::string& GetName() { return m_name; }

    void ModifyHealth(int amount);
	void ModifyAttack(int amount);

    void Gather() const;
    void Attack() const;
};

