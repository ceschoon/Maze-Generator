#include "../include/randSeed.h"
#include <cstdlib>
#include <chrono>
#include <iostream>

RandSeed::RandSeed()
{	
	int seed = 1;
	
	for (int i=0; i<3; i++)
	{
		auto start = std::chrono::high_resolution_clock::now();
    	auto finish = std::chrono::high_resolution_clock::now();
    	int nanosecs = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
    	if (nanosecs <= 1000)
    	{
			seed = seed * nanosecs;
		}
	}
	
	init(seed);
}


RandSeed::RandSeed(int seed)
{
	init(seed);
}

void RandSeed::init(int seed)
{
	m_seed = seed;
	m_timesUsed = 0;
	
	srand (m_seed);
	
	for (int i=0; i<1024; i++)
	{
		m_randNums[i] = rand();
	}
}

RandSeed::~RandSeed(){};

int RandSeed::randomWithSeed()
{
	m_timesUsed += 1;
	return m_randNums[(m_timesUsed)-1%1024];
}