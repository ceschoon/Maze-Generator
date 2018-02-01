#include "../include/map.h"
#include "../include/randSeed.h"
#include <cstdlib>

/*
 * Convention:  0 = empty space
 *				1 = wall
 */


Map::Map(int mapHeight, int mapWidth, RandSeed seed)
{
	if (mapWidth%2==1)
	{
		m_mapWidth = mapWidth;
	}
	else
	{
		m_mapWidth = mapWidth+1;
		std::cout << "Width of labyrinth must be an odd number";
		// GENERER UNE ERREUR
	}
	if (mapHeight%2==1)
	{
		m_mapHeight = mapHeight;
	}
	else
	{
		m_mapHeight = mapHeight+1;
		std::cout << "Height of labyrinth must be an odd number";
		// GENERER UNE ERREUR
	}

	std::vector<int> tempVector(mapWidth, 0);
	std::vector<std::vector<int>> tempGrid(mapHeight, tempVector);
	m_grid = tempGrid;
	m_seed = seed;
}

Map::~Map(){};

std::ostream& operator<<(std::ostream& stream, const Map& map) 
{
	for (int i=0; i<map.GetmapHeight(); i++)
	{
		for (int j=0; j<map.GetmapWidth(); j++)
		{
			std::cout << map.GetgridAt(i,j);
		}
		if (i<map.GetmapHeight()-1){std::cout << std::endl;}
	}  
	
    return stream;
}

void Map::addToUpdateList(int i, int j)
{
	m_updateList.push_back({i,j});
}
void Map::clearUpdateList()
{
	m_updateList.clear();
}
void Map::addEntireGridToUpdateList()
{
	for (int i=0; i<GetmapHeight(); i++)
	{
		for (int j=0; j<GetmapWidth(); j++)
		{
			addToUpdateList(i,j);
		}
	}
}

void Map::recursiveDivision(int recursionLevel)
{
	int N = (m_mapHeight)/2;
	int M = (m_mapWidth)/2;
	
	if (N==0 || M==0)
	{
		// do nothing
	}
	else
	{
		// create a wall
		
		int randIndex = 0;
		
		if (recursionLevel%2==0)
		{
			randIndex = m_seed.randomWithSeed()%M;
			for (int i=0; i<2*N+1; i++)
			{
				m_grid[i][2*randIndex+1]=1;
			}		
		}
		else
		{
			randIndex = m_seed.randomWithSeed()%N;
			for (int i=0; i<2*M+1; i++)
			{
				m_grid[2*randIndex+1][i]=1;
			}
		}

		// make a hole in the wall
		
		int randIndex2 = 0;

		if (recursionLevel%2==0)
		{
			randIndex2 = m_seed.randomWithSeed()%(N+1);
			m_grid[2*randIndex2][2*randIndex+1] = 0;
		}
		else
		{
			randIndex2 = m_seed.randomWithSeed()%(M+1);
			m_grid[2*randIndex+1][2*randIndex2] = 0;
		}

		// recursion

		if (recursionLevel%2==0) 
		{
			Map map1(2*N+1,2*randIndex+1,m_seed.randomWithSeed());
			Map map2(2*N+1,2*(M-randIndex-1)+1,m_seed.randomWithSeed());

			map1.recursiveDivision(recursionLevel+1);
			map2.recursiveDivision(recursionLevel+1);

			for (int i=0; i<2*N+1; i++)
			{
				for (int j=0; j<2*randIndex+1; j++)
				{
					m_grid[i][j] = map1.GetgridAt(i,j);
				}
			}
			for (int i=0; i<2*N+1; i++)
			{
				for (int j=2*randIndex+2; j<2*M+1; j++)
				{
					m_grid[i][j] = map2.GetgridAt(i,j-2*randIndex-2);
				}
			}
		}
		else
		{
			Map map1(2*randIndex+1,2*M+1,m_seed.randomWithSeed());
			Map map2(2*(N-randIndex-1)+1,2*M+1,m_seed.randomWithSeed());

			map1.recursiveDivision(recursionLevel+1);
			map2.recursiveDivision(recursionLevel+1);

			for (int i=0; i<2*randIndex+1; i++)
			{
				for (int j=0; j<2*M+1; j++)
				{
					m_grid[i][j] = map1.GetgridAt(i,j);
				}
			}
			for (int i=2*randIndex+2; i<2*N+1; i++)
			{
				for (int j=0; j<2*M+1; j++)
				{
					m_grid[i][j] = map2.GetgridAt(i-2*randIndex-2,j);
				}
			}
		}
	}

	if (recursionLevel==0)
	{
		clearUpdateList();
		addEntireGridToUpdateList();
	}
}
