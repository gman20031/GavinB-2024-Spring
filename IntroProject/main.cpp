#include "ConsoleManip.h"

int main()
{
	ConsoleManip::ChangeConsoleTitle("Test Title");
	ConsoleManip::ChangeConsoleFormat(TEXT_RGB(255, 0, 255));
	std::cout << "help\n";
	std::cout << "gooday\n";
	ConsoleManip::Printf("Printed with formatting\n", TEXT_RGB(0, 255, 0));
	std::cout << "gooday";

	printf("good day sir");
	return 0;
}
