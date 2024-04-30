#pragma once
#include <iostream>
#include <time.h>
#include <chrono> 
#include <ratio>

class HigRezTimer
{
	std::chrono::high_resolution_clock::time_point m_start;
public:
	HigRezTimer()
		: m_start(std::chrono::high_resolution_clock::now())
	{
	}

	void PrintTimeSinceStart()
	{
		using namespace std::literals;
		std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
		auto time_span = (end - m_start) / 1ms;
		std::cout << time_span << " miliseconds\n";
	}
};
