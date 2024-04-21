
#include <tuple>
#include <iostream>

#include "ComponentFactory.h"

//ComponentFactory<int>::Registrar<MoveComponent> a;
//ComponentFactory<int>::Registrar<ConcreteComponentTest> b;
//ComponentFactory<int,int>::Registrar<Teleporter> c;
//ComponentFactory<>::Registrar<CheckForBombs> d;

template <class ComponentType , typename ... ArgTypes>
Component* CreateComponent(ArgTypes&& ... args)
{
	return new ComponentType(std::forward<ArgTypes>(args)...);
}

class IntIntTest : public Component
{
	int m_i;
	int m_b;

public:
	IntIntTest(int i, int b) : m_i(i), m_b(b) {}
	IntIntTest() : IntIntTest(0,0) {}
	static constexpr size_t s_Id = 6;

	Component* Clone(int i, int b) const
	{
		return new IntIntTest(i, b);
	}
	void Print() const { std::cout << "int : " << m_i << " , Int : " << m_b << '\n'; }\
};

ComponentFactory::Registrar<IntIntTest> rax;

int main()
{
	Component* pTest = ComponentFactory::Create(IntIntTest::s_Id);
	Component* static_cast<IntIntTest*>(pTest);
	
	delete pTest;
	return 0;
}