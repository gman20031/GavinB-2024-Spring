#include <iostream>

#include "Test/Actor.h"
#include "Test/Component.h"

class TestA : public Component
{
public:
	static CounterId s_id;
	TestA(Actor* pOwner) : Component(pOwner, *s_id) {}
};

class TestB : public Component
{
public:
	static CounterId s_id;
	TestB(Actor* pOwner) : Component(pOwner, *s_id) {}
};

class TestC : public Component
{
public:
	static CounterId s_id;
	TestC(Actor* pOwner) : Component(pOwner, *s_id) {}
};


#define PRINTLN(str) std::cout << str << '\n'

int main()
{
	std::cout << TestA::s_id << '\n';

	PRINTLN(TestA::s_id);
	PRINTLN(TestA::s_id);
	PRINTLN(TestA::s_id);



	return 0;
}