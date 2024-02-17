#pragma once

#include "Debugging.h"
#include "cooridnatePair.h"
#include "Map.h"


class Player
{

	CooridinatePair m_position = { 0,0 };
	Map* m_pCurrentMap = nullptr;
	bool MoveCharacter(CooridinatePair newPosition);

#ifdef DEBUG
	char m_standingOnCharacter = Map::k_emptyCharacter;
	bool m_noClip = false;
public:
	void ToggleNoClip();
	bool GetNoClipValue() const { return m_noClip; }
	bool TeleportToLocation (CooridinatePair newLocation);
private:
#endif

public:

	bool SetCurrentMapPointer(Map* newMap);
	Map* GetMapPointer() { return m_pCurrentMap; }

	CooridinatePair& GetPosition();
	void setPosition(CooridinatePair newPosition);

	bool MoveX(int distance);
	bool MoveY(int distance);

};