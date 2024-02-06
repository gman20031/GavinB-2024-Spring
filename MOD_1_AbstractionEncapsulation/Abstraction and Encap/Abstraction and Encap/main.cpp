/*
Write a function that abstracts this process:
	asking the user a question, then getting a string response that may have spaces in it.
	example: what is your favorite food? cheese pizza
	Your function can ask any question; it’s not hard-coded to ask a specific question
	The user’s answer to your question can be accessed outside of the function, without using a global variable.



Write a struct called FixedArray that encapsulates:
	the creation and manipulation of a dynamic array of integers. It should have these functions:
	Init: takes an integer, and allocates an array of that size
	Set: takes an index and value, sets the element at that index to that value
	Set: takes an index, returns a reference to the element at that index

	Your struct doesn’t take any user input (e.g. std::cin)
	Your struct doesn’t print anything (e.g. std::cout)
	Add a Print function, which prints every element in the array (this can be an exception to the previous item)

*/

#include <iostream>
#include <string>

//asking the user a question, then getting a string response that may have spaces in it.
static void AskAndGetResponse(std::string& question, std::string& response)
{
	std::cout << question << '\n';
	std::getline(std::cin, response);
}

//struct called FixedArray

struct FixedArray
{
public:
	int* m_pList;
	int m_size = 0;

	FixedArray(int size) : m_size(size)
	{ 
		m_pList = new int[size];
		for (int i = 0; i < size; ++i)
		{
			m_pList[i] = 0;
		}
	}

	void Set(int index, int newValue)
	{
		m_pList[index] = newValue; 
	}

	int& At(int index)
	{
		return m_pList[index]; 
	}

	void Print()
	{
		for (int i = 0; i < m_size; ++i)
		{
			std::cout << m_pList[i] << ",";
		}
		std::cout << '\n';
	}
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There was no specified use, so I quickly made something to test if what I did actually works, its not made well, but can be used to test whats happening.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PrintOptions()
{
	std::cout << "0 - set\n";
	std::cout << "1 - Get\n";
	std::cout << "2 - Print\n";
}

static void TestSet(FixedArray& fixedArray)
{
	int index, newValue;

	std::cout << "Index: ";
	std::cin >> index;
	std::cout << "\nnew Value: ";
	std::cin >> newValue;
	std::cout << '\n';

	fixedArray.Set(index, newValue);
}

static void TestGet(FixedArray& fixedArray)
{
	int index;

	std::cout << "Index: ";
	std::cin >> index;
	std::cout << '\n';

	std::cout << "at index" << index << " is :"  << fixedArray.At(index) << '\n';
	system("pause");
}

static void TestPrint(FixedArray& fixedArray)
{
	fixedArray.Print();
	system("pause");
}

int main(int argv, char* argc[])
{
	FixedArray myArray(4);

	int input = 0;

	for (;;)
	{
		PrintOptions();
		std::cin >> input;

		switch (input)
		{
		case 0: TestSet(myArray); break;
		case 1: TestGet(myArray); break;
		case 2: TestPrint(myArray); break;
		}
		system("cls");
	}

}