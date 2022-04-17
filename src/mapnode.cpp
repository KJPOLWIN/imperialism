#include "mapnode.h"
#include "hexvector.h"
#include <SFML/Graphics.hpp>
#include <array>
#include <cmath>

MapNode::MapNode(int x, int y)
  : hexPosition{ x, y }
{
  for( auto& vertex : vertices )
  {
    vertex.color = sf::Color::White;
  }

  constexpr double sideLength{ 50.0 };

  double posX{ x * sideLength * sqrt(3) };
  double posY{ 3 * y * sideLength / 2 };
  if(y % 2 == 1)
  {
    posX = x * sideLength * sqrt(3) + sideLength * sqrt(3) / 2;
    posY = 3 * y * sideLength / 2;
  }

  vertices.at(0).position = sf::Vector2f(posX, 
                                         posY + sideLength / 2);
  vertices.at(1).position = sf::Vector2f(posX + (sideLength * sqrt(3)) / 2, 
                                         posY);
  vertices.at(2).position = sf::Vector2f(posX + sideLength * sqrt(3), 
                                         posY + sideLength / 2);
  vertices.at(3).position = sf::Vector2f(posX + sideLength * sqrt(3),
                                         posY + 3 * sideLength / 2);
  vertices.at(4).position = sf::Vector2f(posX + (sideLength * sqrt(3)) / 2, 
                                         posY + 2 * sideLength);
  vertices.at(5).position = sf::Vector2f(posX, 
                                         posY + 3 * sideLength / 2);
  vertices.at(6).position = vertices.at(0).position; 
}

void MapNode::select()
{
  isSelected = true;
  for( auto& vertex : vertices )
  {
    vertex.color = sf::Color::Yellow;
  }
}

void MapNode::disselect()
{
  isSelected = false;
  for( auto& vertex : vertices )
  {
    vertex.color = sf::Color::White;
  }
}

void MapNode::draw(sf::RenderWindow& targetWindow)
{
  targetWindow.draw(&vertices.at(0), vertices.size(), sf::LineStrip);
}

void MapNode::switchTerrainType()
{
  if(terrain == TerrainType::tundra)
  {
    terrain = TerrainType::grassland;
  }
  else
  {
    terrain = static_cast<TerrainType>(static_cast<int>(terrain) + 1);
  }
}

void MapNode::switchTerrainType(TerrainType newTerrain)
{
  MapNode::terrain = newTerrain;
}

TerrainType MapNode::getTerrainType()
{
  return terrain;
}

sf::Vector2f MapNode::getPosition()
{
  return sf::Vector2f(vertices.at(0).position.x, 
                      vertices.at(1).position.y);
}

HexVector MapNode::getHexPosition()
{
  return hexPosition;
}
