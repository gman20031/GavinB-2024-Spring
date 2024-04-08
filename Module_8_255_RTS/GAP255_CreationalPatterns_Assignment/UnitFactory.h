#pragma once

#include "Unit.h"

class UnitFactory
{
	using UnitMap = std::unordered_map < std::string, Unit >;

	static UnitMap& GetUnitRegistry()
	{
		static const UnitType peon("Peon", 5, 1, false);
		static const UnitType soldier("Soldier", 1, 1, true);
		static const UnitType archer("Archer", 1, 3, true);

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
			return new Unit(it->second);
		return nullptr;
	}
};

