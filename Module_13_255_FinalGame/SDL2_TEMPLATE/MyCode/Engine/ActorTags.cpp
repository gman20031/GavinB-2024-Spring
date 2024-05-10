#include "ActorTags.h"

void ActorTags::GiveTag(const std::string& tag)
{
	m_tags.emplace_back(tag);
}

bool ActorTags::RemoveTag(const std::string& checkedTag)
{
	for (auto it = m_tags.begin(); it != m_tags.end(); ++it)
	{
		if (*it == checkedTag)
		{
			m_tags.erase(it);
			return true;
		}
	}
	return false;
}

bool ActorTags::HasTag(const std::string& checkedTag)
{
	for (auto& currentTag : m_tags)
	{
		if (currentTag == checkedTag)
			return true;
	}
	return false;
}