#pragma once


void AddUnit(Unit** pUnit, const char* type)
{
	*pUnit = UnitFactory::Create(type);
	if (*pUnit == nullptr)
		std::cout << type << " creation failed\n";
	else
	{
		std::cout << type << " has been created\n";
		if ((*pUnit)->m_healthPotion or (*pUnit)->m_attackBuff)
			std::cout << "has consumable\n";
	}
}

static void Gather(Unit* pUnit)
{
	if (!pUnit)
	{
		std::cout << "Unit has not been created\n";
		return;
	}
	pUnit->Gather();
}

static void Attack(Unit* pUnit)
{
	if (!pUnit)
	{
		std::cout << "Unit has not been created\n";
		return;
	}
	pUnit->Attack();
}

static void Use(Unit* pUnit)
{
	if (!pUnit)
	{
		std::cout << "Unit has not been created\n";
		return;
	}
	pUnit->Use();
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

	int oneCharge = 0;
	int twoCharges = 0;
	int threeCharges = 0;
	int incorrectCharges = 0;

	int consumeCount = 0;
	for (const Unit* const soldier : testSoldiers)
	{
		consumeCount = 0;
		if (soldier->m_healthPotion)
		{
			++consumeCount;
			switch (soldier->m_healthPotion->GetCharges())
			{
			case 1: ++oneCharge; break;
			case 2: ++twoCharges; break;
			case 3: ++threeCharges; break;
			default: ++incorrectCharges; break;
			}
		}
		if (soldier->m_attackBuff)
		{
			++consumeCount;
			switch (soldier->m_attackBuff->GetCharges())
			{
			case 1: ++oneCharge; break;
			case 2: ++twoCharges; break;
			case 3: ++threeCharges; break;
			default: ++incorrectCharges; break;
			}
		}
		switch (consumeCount)
		{
		case 0:++ZeroConsumables; break;
		case 1:++OneConsumable; break;
		case 2:++TwoConsumables; break;
		}
	}
	std::cout << ZeroConsumables + OneConsumable + TwoConsumables << " total units, " << kTestAmount << " expected\n";
	std::cout << ZeroConsumables << " units with zero consumables\n";
	std::cout << OneConsumable << " units with one consumables\n";
	std::cout << TwoConsumables << " units with two consumables\n\n";

	std::cout << incorrectCharges << " consumables with incorrect number of charges\n";
	std::cout << oneCharge << " consumables with one charge\n";
	std::cout << twoCharges << " consumables with two charge\n";
	std::cout << threeCharges << " consumables with three charge\n";

	// idk math

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
			<< "9: Attack w/ Archer\n"

			<< "-: Use w/ Soldier\n"
			<< "=: Use w/ Archer\n";

		char choice = (char)std::getchar();
		std::cin.ignore(std::numeric_limits<int>::max(), '\n');

		switch (choice)
		{
		case '0': keepTesting = false; break;
			// Creating
		case '1': AddUnit(&pPeon, "Peon");       break;
		case '2': AddUnit(&pSoldier, "Soldier"); break;
		case '3': AddUnit(&pArcher, "Archer");   break;
			// Gathering
		case '4':Gather(pPeon);    break;
		case '5':Gather(pSoldier); break;
		case '6':Gather(pArcher);  break;
			// Attacking
		case '7':Attack(pPeon);    break;
		case '8':Attack(pSoldier); break;
		case '9':Attack(pArcher);  break;
			// using
		case '-':Use(pSoldier); break;
		case '=':Use(pArcher); break;
		}
		system("pause");
	}
}