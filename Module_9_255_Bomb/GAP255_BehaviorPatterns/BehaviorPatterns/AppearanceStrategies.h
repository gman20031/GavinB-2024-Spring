#pragma once

#include <iostream>



class AppearanceStrategy
{
private:
	const char m_displayerChar;
public:
	enum class Appearance
	{
		kEmpty = '.',
		kBomb = '*',
		kUsedBomb = '#',
		kExit = 'H',
		kTreasure = '$',
	} static ;

	AppearanceStrategy(char displayer) : m_displayerChar(displayer) {}
	virtual void Draw() const
	{
		std::cout << m_displayerChar;
	}
};


//class EmptyAppearance : public AppearanceStrategy
//{
//public:
//	virtual void Draw() const override
//	{
//		std::cout << '.';
//	}
//};
//
//class UsedBomb : public AppearanceStrategy
//{
//	virtual void Draw() const override
//	{
//		std::cout << '#';
//	}
//};
//class BombAppearance : public AppearanceStrategy
//{
//public:
//	virtual void Draw() const override
//	{
//		std::cout << "*";
//	}
//};
//
//class ExitAppearance : public AppearanceStrategy
//{
//public:
//	virtual void Draw() const override
//	{
//		std::cout << "H";
//	}
//};
//
//class TreasureAppearance : public AppearanceStrategy
//{
//
//public:
//	virtual void Draw() const override
//	{
//		std::cout << '$';
//	}
//};