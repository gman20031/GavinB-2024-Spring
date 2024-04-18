
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
static void IlistPrint(std::initializer_list<T> iList)
{
	for (const auto& object : iList)
		std::cout << object << " ,";
	std::cout << '\n';
}

template <typename... T>
static void UnfoldedPrint(T&&... args)
{
	std::cout << "Unfolded Print\n";
	// std::cout << ... << stuff between << args
	(std::cout << ... << args) << '\n'; // unfolded Print requires "... Operator paramPack"

}

template<typename ... argTypes>
void ParamPackTest([[maybe_unused]] argTypes... argugments)
{
	std::cout << "ParamPackTest : Entered without specilization\n";
}

template<> // specialized for int, bool
void ParamPackTest(int A, bool B)
{
	std::cout << "ParamPackTest : int , bool\n";
	std::cout << A << " , " << B << '\n';
}

void ReccursivePrint()
{
	// Reccursive Print requires a overloaded function that has zero arguments
	// Else it will reccursively call itself with void args forever
	// or not compile in this case.
}

template<class T , class ... argTypes>
static void ReccursivePrint(const T& first, const argTypes&... other)
{
	std::cout << first << " , ";
	ReccursivePrint(other...);
}

template <class ComponentType , typename ... ArgTypes>
Component* CreateComponent(ArgTypes&& ... args)
{
	return new ComponentType(args...);
}

int main()
{
	Component* pTest;

	pTest = ExampleInstationIntBool::Create(IntBoolTest::s_Id, 3, false);
	static_cast<IntBoolTest*>(pTest)->Print();

	delete pTest;

	pTest = ExampleVariaticInt::Create(VariaticIntTest::s_Id, { 3, 5, 6, 30 } );
	static_cast<VariaticIntTest*>(pTest)->Print();

	UnfoldedPrint(1, 2 , 3 , "bool" , false);

	std::cout << "Reccursive print: unable to print info in function as it is reccursive \n";
	ReccursivePrint("gooday", false, 4, 5.f, 6.02);

	ParamPackTest();
	ParamPackTest(5, false);
	ParamPackTest(100.003);

	delete pTest;

	pTest = TestCreateComponent<IntIntTest>(4, 3.5);
	static_cast<IntIntTest*>(pTest)->Print();

	delete pTest;

	ComponentFactory<int,int>::Registrar<IntIntTest> IntIntregistrar;
	pTest = ComponentFactory<int , int >::Create(IntIntTest::s_Id, 4, 2.5);
	static_cast<IntIntTest*>(pTest)->Print();

	delete pTest;
	return 0;
}