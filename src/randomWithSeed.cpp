#include <cstdlib>
#include <chrono>
#include <iostream>

int randomWithSeed()
{
	auto start = std::chrono::high_resolution_clock::now();
    auto finish = std::chrono::high_resolution_clock::now();
	int nanosecs = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
	srand (nanosecs);

	return rand();
}