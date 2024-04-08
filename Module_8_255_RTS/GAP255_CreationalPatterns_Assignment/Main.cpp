#include <iostream>
#include <vector>

#include "Unit.h"
#include "UnitFactory.h"
#include "Random.h"

static void AddUnit(Unit* pUnit, const char* type)
{
	pUnit = UnitFactory::Create(type);
	if(pUnit == nullptr)
		std::cout << type << " creation failed\n";
	else
		std::cout << type << " has been created\n";
}

static void Gather(Unit* pUnit)
{
	if (pUnit == nullptr)
	{
		std::cout << "Unit has not been created\n";
		return;
	}
	pUnit->Gather();
}

static void Attack(Unit* pUnit)
{
	if (pUnit == nullptr)
	{
		std::cout << "Unit has not been created\n";
		return;
	}
	pUnit->Attack();
}


void RunConsumablesTest()
{
	constexpr int kTestAmount = 1'000;
	Unit* testSoldiers[kTestAmount](nullptr);
	for (size_t i = 0; i < kTestAmount; ++i)
		testSoldiers[i] = UnitFactory::Create("Soldier");
	

	int ZeroConsumables = 0;
	int OneConsumable = 0;
	int TwoConsumables = 0;

	int consumeCount = 0;
	for (const Unit* const soldier : testSoldiers)
	{		
		consumeCount = 0;
		if (soldier->m_healthPotion)
			++consumeCount;
		if (soldier->m_attackBuff)
			++consumeCount;
		switch (consumeCount)
		{
		case 0:++ZeroConsumables; break;
		case 1:++OneConsumable; break;
		case 2:++TwoConsumables; break;
		}
	}
	std::cout << ZeroConsumables + OneConsumable + TwoConsumables << " total\n";
	std::cout << ZeroConsumables << " units with zero consumables\n";
	std::cout << OneConsumable   << " units with one consumables\n";
	std::cout << TwoConsumables  << " units with two consumables\n";

	// 750 none
	// 188 One
	// 62 two
	system("pause");
}

static void RunCreationTestSandbox()
{
	Unit* pPeon = nullptr;
	Unit* pSoldier = nullptr;
	Unit* pArcher = nullptr;

	bool keepTesting = true;
	while (keepTesting)
	{
		system("cls");


		std::cout << "0: Quit\n"

			<< "1: Create Peon\n"
			<< "2: Create Soldier\n"
			<< "3: Create Archer\n"

			<< "4: Gather w/ Peon\n"
			<< "5: Gather w/ Soldier\n"
			<< "6: Gather w/ Archer\n"

			<< "7: Attack w/ Peon\n"
			<< "8: Attack w/ Soldier\n"
			<< "9: Attack w/ Archer\n";

		char choice = (char)std::getchar();
		std::cin.ignore();

		switch (choice)
		{
		case '0': keepTesting = false; break;
			// Creating
		case '1': AddUnit(pPeon, "Peon");       break;
		case '2': AddUnit(pSoldier, "Soldier"); break;
		case '3': AddUnit(pArcher, "Archer");   break;
			// Gathering
		case '4':Gather(pPeon);    break;
		case '5':Gather(pSoldier); break;
		case '6':Gather(pArcher);  break;
			// Attacking
		case '7':Attack(pPeon);    break;
		case '8':Attack(pSoldier); break;
		case '9':Attack(pArcher);  break;
		}
		system("pause");
	}
}

int main()
{
	//Random::SeedWithTime();

	RunConsumablesTest();
	RunCreationTestSandbox();

    return 0;
}