#include <iostream>
#include <chrono>

struct Timer
{
	std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> endTime;

	void start()
	{
		startTime = std::chrono::high_resolution_clock::now();
	}
	auto GetTime()
	{
		endTime = std::chrono::high_resolution_clock::now();
		return endTime - startTime;
	}

};


class cString
{
public:
	const char* memory;

	cString(const char* in)
		: memory(in)
	{
		//
	}
};

class stdString
{
public:
	std::string memory;

	stdString(const std::string& in)
		: memory(in)
	{
		//
	}
};

int main()
{
	cString nullString("hello,World!");
	stdString cppString("hello,Porld!");

	std::cout << nullString.memory << '\n';
	std::cout << cppString.memory << '\n';

	return 0;
}