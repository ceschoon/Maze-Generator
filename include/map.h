#ifndef MAP_H
#define MAP_H

#include "randSeed.h"
#include <vector>
#include <iostream>

class Map
{
    public:
        Map(int mapHeight, int mapWidth, RandSeed seed);	// odd numbers 
        ~Map();

		const RandSeed Getseed() const {return m_seed;}
        const int GetmapWidth() const {return m_mapWidth;}
		const int GetmapHeight() const {return m_mapHeight;}
		const int GetgridAt(int i, int j) const {return m_grid[i][j];}
		const std::vector<std::vector<int>> GetupdateList() 
			const {return m_updateList;}
		//const std::vector<int> GetNthPixelToUpdate(int n) const {return m_grid[n];}
		
		void recursiveDivision2(int recursionLevel=0);
        void recursiveDivision4(int recursionLevel=0);
		friend std::ostream& operator<<(std::ostream& stream, const Map& map);
		void addToUpdateList(int i, int j);
		void addEntireGridToUpdateList();
		void clearUpdateList();

    protected:

    private:
        int m_mapWidth;
		int m_mapHeight;
		std::vector<std::vector<int>> m_grid;
		std::vector<std::vector<int>> m_updateList;
		RandSeed m_seed;
};

#endif // MAP_H
