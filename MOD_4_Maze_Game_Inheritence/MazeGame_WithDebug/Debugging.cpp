#include <iostream>

#include "Debugging.h"
#include "Map.h"
#include "Player.h"


//#define DEBUG

#ifdef DEBUG

CooridinatePair DebugMenu::GetLocationInput()
{	
	CooridinatePair input;

	std::cin >> input.x >> input.y;
	while (!std::cin.good()) 
	{
		std::cout << "one or more of those were not proper numbers \n";
		std::cin.clear();													// Resets all error flags from cin
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // effectivelly clears the cin stream buffer
		std::cin >> input.x >> input.y;
	}//test for floats
	return input;
}



void DebugMenu::RemoveWall(Map& currentMap)
{
	if (!displayDebugMenu)
		return;

	std::cout << "enter X,Y of the wall you would like to replace with a '.' \n";
	CooridinatePair userInput = GetLocationInput();
	if (currentMap.at(userInput) == Map::k_wallCharacter)
		currentMap.at(userInput) = Map::k_emptyCharacter;
	else
	{
		std::cout << "that is not a wall\n";
		system("Pause");
	}

}

void DebugMenu::PlaceWall(Map& currentMap)
{
	if (!displayDebugMenu)
		return;

	std::cout << "enter X,Y of the empty square you would like to place a wall\n";
	CooridinatePair userInput = GetLocationInput();
	if (currentMap.at(userInput) == Map::k_emptyCharacter)
		currentMap.at(userInput) = Map::k_wallCharacter;
	else
	{
		std::cout << "that is not empty\n";
		system("Pause");
	}
}

void DebugMenu::ToggleNoClip(Player& player) const
{
	if (!displayDebugMenu)
		return;

	player.ToggleNoClip();
}

bool DebugMenu::TeleportPlayer(Player& player)
{	
	if (!displayDebugMenu)
		return false;

	std::cout << "enter X,Y of the square you would like to goto\n";
	CooridinatePair userInput = GetLocationInput();
	Map* currentMap = player.GetMapPointer();
	switch(currentMap->at(userInput))
	{
	case Map::k_exitCharacter:
		return true;
	case Map::k_emptyCharacter:
	case Map::k_wallCharacter:
		return player.TeleportToLocation(userInput); break;
	default:
		return false;
	}
}


void DebugMenu::ToggleDisplayDebugMenu()
{
	if (displayDebugMenu)
		displayDebugMenu = false;
	else
		displayDebugMenu = true;
}

void DebugMenu::DrawDebugMenu() const
{
	if (displayDebugMenu)
	{
		std::cout << "0: toggle debug\n"
			<< "9: toggle noclip\n" 
			<< "8: Teleport\n"
			<< "7: Remove Wall\n"
			<< "6: Place Wall\n";
	}
	else
		std::cout << "debug enabled, 0 for menu\n";

}


#endif