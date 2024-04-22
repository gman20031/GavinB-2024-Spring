#pragma once

#include <assert.h>
#include <unordered_map>
#include "Component.h"

template <class ComponentType, typename ... ArgTypes>
Component* CreateComponent(ArgTypes&& ... args)
{
	return new ComponentType(args...);
}

class ComponentFactory
{
	using ComponentPtr = Component*;
	using KeyType = Component::IdType;
	using CreateComponentFunction = ComponentPtr (*) (Actor*);
	using Contents = CreateComponentFunction;
	using ComponentMap = std::unordered_map<KeyType, Contents>;

private:
	static ComponentMap& GetMap() {
		static ComponentMap s_componentMap;
		return s_componentMap;
	}
public:
	static const ComponentPtr Create (KeyType key, Actor* pOwner) {
		auto entry = GetMap().find(key);
		if (entry == GetMap().end()) return nullptr;
		return entry->second(pOwner);
	}

	template<class ComponentSubClass>
	class Registrar {
	public:
		Registrar() {
			auto test = GetMap().try_emplace(ComponentSubClass::s_id , &ComponentMaker);
			assert(test.second);
		}
	private:
		static ComponentPtr ComponentMaker(Actor* pOwner) { return new ComponentSubClass(pOwner); }
	};
};


