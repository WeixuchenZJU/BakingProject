#pragma once
#include <chrono>



double GetCPUTime()
{
	static auto begin = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - begin).count() / 1000.0;
}
