#include "../include/render.h"
#include "../include/map.h"
#include <iostream>


void renderGrid(sf::Image &image, Map &map)
{
	// render the squares to update	
	
	for (std::vector<int> square : map.GetupdateList())
	{
		int squareType = map.GetgridAt(square[0], square[1]);
		
		if (squareType==0)
		{
			drawSquare(image, 1+square[1], 1+square[0], sf::Color(191,191,191,255));
		}
		else if (squareType==1)
		{
			drawSquare(image, 1+square[1], 1+square[0], sf::Color::Black);
		}
		else {}
	}

	map.clearUpdateList();
}

void drawSquare(sf::Image &image, int x, int y, sf::Color color)
{
	for (int i=0; i<squareSize; i++)
	{
		for (int j=0; j<squareSize; j++)
		{
			image.setPixel(x*squareSize+i, y*squareSize+j, color);
		}
	}	
}