#pragma once
#include <iostream>
#include <vector>
#include <cstdarg>
#include "Component.h"

class ConcreteComponentTest : public Component
{
	int value;

public:
	static constexpr size_t s_Id = 0;
	ConcreteComponentTest(int val) : value(val) {}

	void PrintValue() const { std::cout << value; }
};

class MoveComponent : public Component
{
	int m_speed;

public:
	static constexpr size_t s_Id = 1;
	MoveComponent(int speed) : m_speed(speed) {}
	void MoveTowards([[maybe_unused]] Actor*  otherActor) { std::cout << "moving towards other Actor\n"; }
};


class Teleporter : public Component
{
	int m_x, m_y;

public:
	static constexpr size_t s_Id = 2;
	Teleporter(int x, int y) : m_x(x), m_y(y) {}

	void TeleportActor(Actor* teleportedActor) const {
		std::cout << teleportedActor << " teleported to "
			<< m_x << " , " << m_y << '\n';
	}
};

class CheckForBombs : public Component
{
	const int checkRange;
	static constexpr size_t bombId = 0;

public:
	static constexpr size_t s_Id = 3;

};

class IntBoolTest : public Component
{
	int m_i;
	bool m_b;

public:
	IntBoolTest(int i, bool b) : m_i(i), m_b(b) {}
	static constexpr size_t s_Id = 4;

	void Print() const { std::cout << "int : " << m_i << " , Bool : " << m_b << '\n'; }

};

class VariaticIntTest : public Component
{
	std::vector<int> allInts;

public:
	static constexpr size_t s_Id = 5;
	VariaticIntTest(std::initializer_list<int> iList) :allInts(iList) {}

	void Print() const { 
		for (int number : allInts) std::cout << number << " , ";
		std::cout << '\n';
	}
};

class IntIntTest : public Component
{
	int m_i;
	int m_b;

public:
	IntIntTest(int i, int b) : m_i(i), m_b(b) {}
	static constexpr size_t s_Id = 6;

	void Print() const { std::cout << "int : " << m_i << " , Int : " << m_b << '\n'; }

};
