#include "GameObject.h"


GameObject::GameObject(Vector2 position, const char displayCharacter)
	: m_displayCharacter{ displayCharacter }
	, m_position{ position }
	, m_pCurrentMap{ nullptr }
{}

/////////////////////////////////////////////////////////////
/// Couts this objects display char with no linebreak
/////////////////////////////////////////////////////////////
void GameObject::draw()
{
	std::cout << m_displayCharacter;
}

Vector2 GameObject::GetPosition() const
{
	return m_position;
}

void GameObject::SetPosition(Vector2 newPosition)
{
	m_position = newPosition;
}

Map* GameObject::GetMapPointer()
{
	return m_pCurrentMap;
}

bool GameObject::SetCurrentMapPointer(Map* newMap)
{
	m_pCurrentMap = newMap;
	return true;
}

char GameObject::GetDisplayChar() const
{
	return m_displayCharacter;
}
