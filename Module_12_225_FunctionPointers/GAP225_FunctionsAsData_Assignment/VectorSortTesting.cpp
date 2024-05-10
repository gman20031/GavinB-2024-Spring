#include "Tasks.h"

#include <algorithm>

#include "Vector3.h"
#include "ConsoleManip.h"
#include "Unit.h"

void VectorSortTesting()
{
	Vector3 vectorArray[]{ {2,3,4} ,{1,2,2} ,{1,0,0} ,{0,1,1} , { 0, 0 ,0} , {2,0,0} };
	constexpr size_t size = std::size(vectorArray);

	//////////////

	std::cout << "Vector Array Pre sort:\n";
	std::cout << "Vector values     - Vector Length\n";
	for (Vector3& vector : vectorArray)
	{
		std::cout << vector << " - " << vector.GetLength() << '\n';
	}
	std::cout << '\n';


	ConsoleManip::Pause();
	std::cout << '\n';

	std::cout << "Vector Array normal std::stable_sort'ed:\n";
	std::cout << "Vector values     - Vector Length\n";
	std::stable_sort(vectorArray, vectorArray + (size));
	for (Vector3& vector : vectorArray)
	{
		std::cout << vector << " - " << vector.GetLength() << '\n';
	}
	std::cout << '\n';

	ConsoleManip::Pause();
	std::cout << '\n';

	std::cout << "Testing Unit Comparison\n\n";
	Unit unitArray[]
	{ {5,2,1,1,"soldier"}
	, {3,2,1,1, "wounded Soldier"}
	, {0,2,1,1, "dead soldier"}
	, {2,1,0,4, "peon"}
	, {2,1,0,4, "peon"}
	};
	size_t unitCount = std::size(unitArray);

	std::cout << "Starting Array\n";
	for (Unit& unit : unitArray)
	{
		std::cout << unit << '\n';
	}

	ConsoleManip::Pause();
	std::cout << '\n';

	std::cout << "Standard sorted array - health based\n";
	std::stable_sort(unitArray, unitArray + unitCount);
	for (Unit& unit : unitArray)
	{
		std::cout << unit << '\n';
	}

	ConsoleManip::Pause();

}

