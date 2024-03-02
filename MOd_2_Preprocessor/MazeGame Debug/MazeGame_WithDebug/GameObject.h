#pragma once

#include "Debugging.h"
#include "cooridnatePair.h"
#include "Map.h"

class GameObject
{
protected:
	CooridinatePair m_position = { 0,0 };
	Map* m_pCurrentMap = nullptr;
	
public:
	void MoveTo(CooridinatePair newPosition);

	Map* GetMapPointer() { return m_pCurrentMap; }
	virtual bool SetCurrentMapPointer(Map* newMap) = 0;
	
};