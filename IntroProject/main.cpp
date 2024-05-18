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
		return std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
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


static void Test() 
{

	Timer timer;
	std::chrono::nanoseconds cStringTotalTime(0);
	std::chrono::nanoseconds stdStringTotalTime(0);

	for (int i = 0; i < 1'00; ++i)
	{
		timer.start();
		cString nullString("hello,World!");
		cStringTotalTime += timer.GetTime();
	}
	for (int i = 0; i < 1'00; ++i)
	{
		timer.start();
		stdString cppString("Pello,Porld!");
		stdStringTotalTime += timer.GetTime();
	}

	std::cout << "Total C String time   : " << cStringTotalTime << '\n';
	std::cout << "Total std String Time : " << stdStringTotalTime << '\n';
}

struct Result
{
	cString c;
	stdString std;
};

Result testResult()
{
	cString nullString("hello,World! is there any case that this is a small string problem?");
	stdString cppString("Pello,Porld! is there any case that this is a small string problem?");

	return {nullString, cppString};

}

int main()
{
	const char* name = "hello, World!";

	cString nullString("hello,World!");
	stdString cppString("Pello,Porld!");


	//std::cout << "Test One: \n";
	//Test();
	//std::cout << "Test Two: \n";
	//Test();
	//std::cout << "Test Three: \n";
	//Test();

	auto result = testResult();
	std::cout << result.c.memory << "  - cString memory\n";
	std::cout << result.std.memory << "  - stdString memory\n";


	return 0;
}