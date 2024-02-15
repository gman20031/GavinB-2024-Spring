#pragma once

#include "cooridnatePair.h"
#include "Map.h"

class Map;

class Player
{
	CooridinatePair m_position = { 0,0 };
	char m_displayChar = '@';
	Map* m_pCurrentMap = nullptr;

	bool MoveCharacter(CooridinatePair newPosition);

public:

	bool SetCurrentMap(Map* newMap);
	
	void SetDisplayCharacter(char newChar) { m_displayChar = newChar; }
	char GetDisplayCharacter() { return m_displayChar; }

	CooridinatePair& GetPosition();
	void setPosition(CooridinatePair newPosition);
	bool MoveX(int distance);
	bool MoveY(int distance);

};