
#include <tuple>
#include <iostream>

#include "ComponentFactory.h"

//ComponentFactory<int>::Registrar<MoveComponent> a;
//ComponentFactory<int>::Registrar<ConcreteComponentTest> b;
//ComponentFactory<int,int>::Registrar<Teleporter> c;
//ComponentFactory<>::Registrar<CheckForBombs> d;

ExampleInstationIntBool::Registrar<IntBoolTest> e;

ExampleVariaticInt::Registrar< VariaticIntTest> f;

template <typename T>
static void Print(std::initializer_list<T> iList)
{
	for (const auto& object : iList)
		std::cout << object << " ,";
	std::cout << '\n';
}



template <typename... T>
static void VariablePrint(T&&... args)
{
	(std::cout << ... << args) << '\n';
}

template<class T , class ... argTypes>
static void TemplateIlist(T e1, argTypes... args)
{
	std::cout << e1 << '\n';
	//VariablePrint(args...);
}

int main()
{
	Component* pTest;

	pTest = ExampleInstationIntBool::Create(IntBoolTest::s_Id, 3, false);
	static_cast<IntBoolTest*>(pTest)->Print();

	delete pTest;

	pTest = ExampleVariaticInt::Create(VariaticIntTest::s_Id, { 3, 5, 6, 30 } );
	static_cast<VariaticIntTest*>(pTest)->Print();


	VariablePrint(1, 2 , 3 , "bool" , false);

	return 0;
}