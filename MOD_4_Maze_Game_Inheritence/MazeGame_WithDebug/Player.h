#pragma once

#include "Debugging.h"
#include "cooridnatePair.h"
#include "Map.h"
#include "GameObject.h"

class Player : public GameObject
{
public:
	static constexpr size_t kMoveSpeed = 1;
private:

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
	virtual bool SetCurrentMapPointer(Map* newMap) override;

	CooridinatePair& GetPosition();
	void setPosition(CooridinatePair newPosition);

	bool Move(GameObject::Direction);
	bool MoveX(int distance);
	bool MoveY(int distance);

};