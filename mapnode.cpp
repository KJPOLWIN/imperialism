#include "mapnode.h"
#include <SFML/Graphics.hpp>
#include <array>
#include <cmath>

MapNode::MapNode(int x, int y)
{
  for( auto& vertex : vertices )
  {
    vertex.color = sf::Color::White;
  }

  constexpr double sideLength{ 50.0 };

  vertices.at(0).position = sf::Vector2f(x * sideLength, 
                                         y * sideLength + sideLength / 2);
  vertices.at(1).position = sf::Vector2f(x * sideLength + (sideLength * sqrt(3)) / 2, 
                                         y * sideLength);
  vertices.at(2).position = sf::Vector2f(x * sideLength + sideLength * sqrt(3), 
                                         y * sideLength + sideLength / 2);
  vertices.at(3).position = sf::Vector2f(x * sideLength + sideLength * sqrt(3),
                                         y * sideLength + 3 * sideLength / 2);
  vertices.at(4).position = sf::Vector2f(x * sideLength + (sideLength * sqrt(3)) / 2, 
                                         y * sideLength + 2 * sideLength);
  vertices.at(5).position = sf::Vector2f(x * sideLength, 
                                         y * sideLength + 3 * sideLength / 2);
  vertices.at(6).position = vertices.at(0).position; 
}

void MapNode::draw(sf::RenderWindow& targetWindow)
{
  targetWindow.draw(&vertices.at(0), vertices.size(), sf::LineStrip);
}
