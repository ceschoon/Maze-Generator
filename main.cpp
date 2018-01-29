#include "include/map.h"
#include "include/render.h"
#include "include/parameters.h"
#include "include/initParameters.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>

int main(int argc, char *argv[])
{
	// extract parameters

	int mapSizeX = 29;
	int mapSizeY = 29;        // maze's size
	int seed = RandSeed().getSeed();

	bool interrupt = initParameters(argc, argv, mapSizeX, mapSizeY, seed);
    if (interrupt){return 0;}	

	// create the window
	
	sf::RenderWindow window(sf::VideoMode(620, 620), "The Amazeing Maze-Generator");
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	//sf::View view = window.getView();
	sf::View view(sf::FloatRect(0, 0, (mapSizeX+2)*squareSize, (mapSizeY+2)*squareSize));

	image.create((mapSizeX+2)*squareSize, (mapSizeY+2)*squareSize, sf::Color::Black);
	texture.create((mapSizeX+2)*squareSize, (mapSizeY+2)*squareSize);
	
	// create the map
	
	RandSeed randSeed(seed);
	Map map(mapSizeY,mapSizeX,randSeed);
	map.recursiveDivision2();

	// main loop

    while (window.isOpen())
    {			
		// event handling

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::Resized)
			{
				
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				// move view
				
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && 						sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
				{
    				view.move(-viewVelocity, 0);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
						 sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
				{
    				view.move(viewVelocity, 0);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && 
						 sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
				{
    				view.move(0, viewVelocity);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
						 sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
				{
    				view.move(0, -viewVelocity);
				}
				
				// zoom view

				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add) &&
						 sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
				{
    				view.zoom(0.8f);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract) &&
						 sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
				{
    				view.zoom(1.25f);
				}
		
				// get seed

				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
    				std::cout << map.Getseed().getSeed() << std::endl;
				}
			}
        }

		// processing objects
		
		// render the map
		
		window.clear();

		renderGrid(image, map);
		texture.update(image);
		sprite.setTexture(texture);
		window.draw(sprite);

		window.setView(view);

		window.display();

		// pause
		
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	
	return 0;
}