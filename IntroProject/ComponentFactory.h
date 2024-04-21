#pragma once

#include <unordered_map>
#include <iostream>

#include "Component.h"
#include "ComponentImplementations.h"

class ComponentFactory
{
	using ComponentPtr = Component*;
	using Contents = Component;
	using KeyType = Component::IdType;
	using ComponentMap = std::unordered_map<KeyType, Contents>;

private:
	static ComponentMap& GetMap() {
		static ComponentMap s_componentMap;
		return s_componentMap;
	}
public:
	static const ComponentPtr Get(KeyType key) {
		auto entry = GetMap().find(key);
		if (entry == GetMap().end()) return nullptr;
		return &(entry->second);
	}

	template<class ComponentSubClass>
	class Registrar {
	public:
		Registrar() {
			GetMap().emplace(ComponentSubClass::s_Id, ComponentSubClass());
		}
	};
};

