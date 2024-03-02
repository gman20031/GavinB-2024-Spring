#pragma once
#include "cooridnatePair.h"

class Map;
class Player;


//#define DEBUG

#ifdef DEBUG
class DebugMenu
{
private:
	bool displayDebugMenu = false;
	CooridinatePair GetLocationInput();
	
public:
	void RemoveWall(Map& currentMap);
	void PlaceWall(Map& currentMap);
	void ToggleNoClip(Player& player) const;
	bool TeleportPlayer(Player& player);

	void ToggleDisplayDebugMenu();
	void DrawDebugMenu() const;

};

#define DEBUG_MENU_CASES\
		case '0':												\
			debugMenu.ToggleDisplayDebugMenu(); break;			\
		case '9':												\
			debugMenu.ToggleNoClip(playerCharacter); break;		\
		case '8':												\
			debugMenu.TeleportPlayer(playerCharacter); break;   \
		case '7':												\
			debugMenu.RemoveWall(currentMap); break;			\
		case '6':												\
			debugMenu.PlaceWall(currentMap); break;				

#else // NOT DEBUG

#define DEBUG_MENU_CASES

#endif