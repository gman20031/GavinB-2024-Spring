#include <iostream>

#include <type_traits>
#include <algorithm>
#include <iterator>

template<typename messageType>
unsigned int g_printCount = 0;

template<>
unsigned int g_printCount<bool> = 100;

template<typename messageType>
void Print(const messageType& message)
{
	static_assert( !(std::is_unsigned_v<messageType> and std::is_integral_v<messageType>), "Cannot use unsigned intergal value with templated print");
	std::cout << message << '\n';
	++g_printCount<messageType>;
}

template<typename internalType, int ArrayLength>
class Vector
{
private:
	internalType m_pArray[ArrayLength];
public:
	constexpr Vector(const internalType pNewArray[ArrayLength]) { for (size_t i = 0; i < ArrayLength; ++i) m_pArray[i] = pNewArray[i]; }
	constexpr internalType& Get(size_t index) { return m_pArray[index]; }
};


/* instantiation of Vector<int , 2 >
template<typename int, int 2>
class Vector
{
private:
	int m_array[2];
public:
	constexpr Vector(const int pNewArray[2]) { for (size_t i = 0; i < 2; ++i) m_pArray[i] = pNewArray[i]; }
	int& Get(size_t index) { return m_array[index]; }
};
*/

class intVector2 : public Vector<int, 2>
{

public:
	constexpr int& GetX() { return Get(0); }
	constexpr int& GetY() { return Get(1); }
};


template<typename Ty>
concept NotUnsignedInt = !(std::is_unsigned_v<Ty> and std::is_integral_v<Ty>);

template<typename messageType> requires NotUnsignedInt<messageType>
void ConceptedPrint(const messageType& message)
{
	std::cout << message << '\n';
	++g_printCount<messageType>;
}

template<typename messageType> requires (!std::unsigned_integral<messageType>)
void ConstrainedPrint(const messageType& message)
{
	std::cout << message << '\n';
	++g_printCount<messageType>;
}

#define REQUIREMENTS 1;
int main()
{
#if REQUIREMENTS
	Print(5);

	//unsigned int uInt = 5;
	//Print(uInt);  // cannot use unsigned integral value with templated print
	//Print(false); // cannot use unsigned integral value with templated print
	Print("Bad Day");
	std::cout << g_printCount<bool> << '\n';
	std::cout << g_printCount<const char[]> << '\n';

	int values[4]{ 1,2,3,4 };
	Vector<int, 4 > vector(values);

	std::copy(&vector.Get(0), &vector.Get(3), std::ostream_iterator<int>(std::cout, " "));
#endif
	ConceptedPrint("test");
	uint32_t Uint = 50;
	//ConceptedPrint(Uint); // error no instance of function template ConceptedPrint matches argument list
							// the associated constraints are not satisfied
							// the concept of NotUnsignedInt< uint32_t > evaluated to false
							// the constraint was not satisfied

	//ConstrainedPrint(Uint);   // error no instance of function template ConceptedPrint matches argument list
								// the associated constraints are not satisfied
								// the constraint was not satisifed 
	Uint; // not used


	return 0;
}
