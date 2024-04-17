#pragma once

#include <iostream>

class AppearanceStrategy
{

public:
	const char m_displayerChar;
public:
	char GetAppearanceType() const { return m_displayerChar; }

	AppearanceStrategy(char displayer) : m_displayerChar(displayer) {}
	virtual void Draw() const
	{
		std::cout << m_displayerChar;
	}

};
