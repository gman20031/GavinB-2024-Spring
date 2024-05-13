#include "GameObject.h"

#include "Map.h"

GameObject::GameObject()
	: m_position{ 0,0 }
	, m_pCurrentMap{ nullptr }
{}


/////////////////////////////////////////////////////////////
/// Couts this objects display char with no linebreak
/////////////////////////////////////////////////////////////

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
