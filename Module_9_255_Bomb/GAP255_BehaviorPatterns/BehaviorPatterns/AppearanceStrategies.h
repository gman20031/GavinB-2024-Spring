#pragma once

#include <iostream>



class AppearanceStrategy
{

public:
	enum class Appearance
	{
		kEmpty = '.',
		kBomb = '*',
		kUsedBomb = '#',
		kExit = 'H',
		kTreasure = '$',
		KTeleporter = '&',
	} static ;
private:
	const Appearance m_displayerChar;
public:
	Appearance GetAppearance() const { return m_displayerChar; }

	AppearanceStrategy(Appearance displayer) : m_displayerChar(displayer) {}
	virtual void Draw() const
	{
		std::cout << (char)m_displayerChar;
	}

};
