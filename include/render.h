#ifndef RENDER_H
#define RENDER_H

#include "map.h"
#include "parameters.h"
#include <SFML/Graphics.hpp>

void renderGrid(sf::Image &image, Map &map);
void drawSquare(sf::Image &image, int x, int y, sf::Color color);

#endif // RENDER_H
