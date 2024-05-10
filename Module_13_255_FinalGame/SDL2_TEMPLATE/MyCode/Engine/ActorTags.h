#pragma once
#include "Component.h"

#include <vector>
#include <string>

class ActorTags : public Component
{
private:
	ID_FROM_NAME("ActorTags");
	std::vector<std::string> m_tags; 
public:
	ActorTags(Actor* pOwner) : Component(pOwner) { /*EMPTY*/ }
	virtual ~ActorTags() = default;

	void GiveTag(const std::string& tag);
	bool RemoveTag(const std::string& tag);
	bool HasTag(const std::string& tag);
	std::vector<std::string>& data() { return m_tags; }
	virtual void Update() { /*EMPTY*/ }
};
