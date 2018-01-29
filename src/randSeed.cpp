#include "../include/randSeed.h"
#include <cstdlib>
#include <time.h>
#include <chrono>
#include <iostream>

RandSeed::RandSeed()
{
	int seed = time(NULL);
	for (int i=0; i<10; i++)
	{
		auto start = std::chrono::high_resolution_clock::now();
    	auto finish = std::chrono::high_resolution_clock::now();
		seed += std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
	}
	m_seed = seed;
}


RandSeed::RandSeed(int seed)
{
	m_seed = seed;
}

RandSeed::~RandSeed(){};

int RandSeed::randomWithSeed()
{
	srand (this->m_seed);
	return rand();
}