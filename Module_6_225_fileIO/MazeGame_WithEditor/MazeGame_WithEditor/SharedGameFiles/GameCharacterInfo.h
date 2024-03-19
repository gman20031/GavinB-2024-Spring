#pragma once
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
	kCount = 9,
};