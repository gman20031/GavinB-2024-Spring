#pragma once

#include "Unit.h"

class UnitFactory
{
	using UnitMap = std::unordered_map < std::string, Unit >;

	static UnitMap& GetUnitRegistry()
	{
		static constexpr UnitConfig peon("Peon", 5, 1, false);
		static constexpr UnitConfig soldier("Soldier", 1, 1, true);
		static constexpr UnitConfig archer("Archer", 1, 3, true);

		static UnitMap m_UnitTypes
		{
			{"Peon"    , Unit(5  , 1 , peon) },
			{"Soldier" , Unit(15 , 3 , soldier) },
			{"Archer"  , Unit(10 , 2 , archer) },
		};
		return m_UnitTypes;
	}

public:
	static Unit* Create(const std::string& Type)
	{
		auto it = GetUnitRegistry().find(Type);
		if (it != GetUnitRegistry().end())
			return it->second.Clone();
		return nullptr;
	}
};

