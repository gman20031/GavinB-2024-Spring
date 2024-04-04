#pragma once
/////////////////////////////////////////////////////////////////////
// All the characters used for the game
/////////////////////////////////////////////////////////////////////
enum class ObjectChar
{
	kBase = '\0',
	kEmpty = '.',
	kWall = '#',
	kExit = 'X',
	kPlayer = '@',
	kTrap = '0',

	kHorizontalEnemy = '-',
	kVerticalEnemy = '|',
	kRandomEnemy = '&',
	kDirectEnemy = '$',

	kClearDoor = '~',
	kHiddenDoor = 'D',

	kTogglePlate = '*',
	kSwordItem = '+',

	kCount = 12,
};