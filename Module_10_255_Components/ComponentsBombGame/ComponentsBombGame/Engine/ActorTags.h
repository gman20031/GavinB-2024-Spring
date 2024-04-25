#pragma once
#include "Component.h"

#include <vector>
#include <string>

class ActorTags : public Component
{
private:
	NEW_STATIC_ID;
	std::vector<std::string> m_tags; 
public:
	ActorTags(Actor* pOwner) : Component(pOwner , s_id) { /*EMPTY*/ }
	virtual ~ActorTags() = default;

	void GiveTag(const std::string& tag) { m_tags.emplace_back(tag); }
	bool RemoveTag(const std::string& tag);
	bool HasTag(const std::string& tag);
	std::vector<std::string>& data() { return m_tags; }
	virtual void Update() { /*EMPTY*/ }
};
