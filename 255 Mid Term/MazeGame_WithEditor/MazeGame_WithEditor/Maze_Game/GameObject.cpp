#include "GameObject.h"
#include "../SharedGameFiles/ConsoleManip.h"

#include "Map.h"

GameObject::GameObject(GameObjectType newType = GameObjectType::kBase)
	: m_position{ 0,0 }
	, m_pCurrentMap{ nullptr }
	, m_displayCharacter(newType)
{

}


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

void GameObject::Draw()
{
	ConsoleManip::DrawToConsole((char)m_displayCharacter);
}
