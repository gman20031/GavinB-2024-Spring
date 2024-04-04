#pragma once

#include <string>
#include <vector>

class VisualNovelCharacter
{
private:
	std::string m_name;
	int m_id;

	void EnsureUnique();
public:

	VisualNovelCharacter(const std::string& name, int id);

	void SetName(const std::string& newName) { m_name = newName; }
	std::string GetName() const { return m_name; }

	int GetId() const { return m_id; }

	void Say(const std::string& dialog) const;
	void Say(const char* dialog) const;

};



