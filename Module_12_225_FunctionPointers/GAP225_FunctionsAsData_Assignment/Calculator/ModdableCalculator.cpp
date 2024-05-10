#include "ModdableCalculator.h"

#include "../SimpleIO.h"

ModdableCalculator::ModdableCalculator()
	: m_supportedOperations{}
{
}

ModdableCalculator::~ModdableCalculator()
{
	
}

/////////////////////////////////////////////////////////////////
// Adds an operation that this calculator can now do.
// That operation's description will be shown in the menu.
/////////////////////////////////////////////////////////////////
void ModdableCalculator::AddOperation(FloatOperation operation,
	const std::string& description)
{
	m_supportedOperations.emplace_back(description, operation);
}

/////////////////////////////////////////////////////////////////
// Runs the calculator.
// It will show a menu of the operations that have been injected,
// then run the associated functions if chosen.
/////////////////////////////////////////////////////////////////
void ModdableCalculator::Run()
{
	while (true)
	{
		system("cls");
		int choice = GetMenuChoice();
		if (choice == kQuit)
			return;

		float left = 0;
		float right = 0;
		GetOperands(left, right);

		float result = PerformOperation(left, right, choice - 1);
		std::cout << "Result: " << result << std::endl;
		system("pause");
	}
}

/////////////////////////////////////////////////////////////////
// Prints the menu of operations based on what has been added.
/////////////////////////////////////////////////////////////////
int ModdableCalculator::GetMenuChoice()
{
	std::cout << "choose one\n";
	std::cout << kQuit << ". Quit" << std::endl;
	for (int i = 0; i < m_supportedOperations.size(); ++i)
	{
		std::cout << (i + 1) << ". " << m_supportedOperations.at(i).first << std::endl;
	}

	int input = CinIntegerInRange(0, (int)m_supportedOperations.size());
	
	return input;
}

/////////////////////////////////////////////////////////////////
// Gets operand values from the user.
/////////////////////////////////////////////////////////////////
void ModdableCalculator::GetOperands(float& left, float& right)
{
	std::cout << "Enter operand values." << std::endl;
	left = GetInput<float>();
	right = GetInput<float>();
}

/////////////////////////////////////////////////////////////////
// Performs one of the operations based on index.
/////////////////////////////////////////////////////////////////
float ModdableCalculator::PerformOperation(float left, float right, int operationIndex) const
{
	const FloatOperation& operation = m_supportedOperations.at(operationIndex).second;
	return operation(left, right);
}
