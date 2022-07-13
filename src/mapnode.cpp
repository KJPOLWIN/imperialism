#include "mapnode.h"
#include "hexvector.h"
#include "constant.h"
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

  double posX{ x * Constant::nodeSideLength * sqrt(3) };
  double posY{ 3 * y * Constant::nodeSideLength / 2 };
  if(y % 2 == 1)
  {
    posX = x * Constant::nodeSideLength * sqrt(3) + Constant::nodeSideLength * sqrt(3) / 2;
    posY = 3 * y * Constant::nodeSideLength / 2;
  }

  vertices.at(0).position = sf::Vector2f(posX, 
                                         posY + Constant::nodeSideLength / 2);
  vertices.at(1).position = sf::Vector2f(posX + (Constant::nodeSideLength * sqrt(3)) / 2, 
                                         posY);
  vertices.at(2).position = sf::Vector2f(posX + Constant::nodeSideLength * sqrt(3), 
                                         posY + Constant::nodeSideLength / 2);
  vertices.at(3).position = sf::Vector2f(posX + Constant::nodeSideLength * sqrt(3),
                                         posY + 3 * Constant::nodeSideLength / 2);
  vertices.at(4).position = sf::Vector2f(posX + (Constant::nodeSideLength * sqrt(3)) / 2, 
                                         posY + 2 * Constant::nodeSideLength);
  vertices.at(5).position = sf::Vector2f(posX, 
                                         posY + 3 * Constant::nodeSideLength / 2);
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

/*void MapNode::switchTerrainType()
{
  if(terrain == TerrainType::mountains)
  {
    terrain = TerrainType::grassland;
  }
  else
  {
    terrain = static_cast<TerrainType>(static_cast<int>(terrain) + 1);
  }
}*/

void MapNode::switchTerrainType(TerrainType newTerrain)
{
  MapNode::terrain = newTerrain;
}

TerrainType MapNode::getTerrainType()
{
  return terrain;
}
      
void MapNode::switchClimateZone(ClimateZone newClimate)
{
  climate = newClimate;
}

ClimateZone MapNode::getClimateZone()
{
  return climate;
}

sf::Vector2f MapNode::getPosition()
{
  return sf::Vector2f(vertices.at(0).position.x, 
                      vertices.at(1).position.y);
}

void MapNode::setPosition(HexVector newPosition)
{
  hexPosition = newPosition;
  
  const int x{ hexPosition.toCartesian().x };
  const int y{ hexPosition.toCartesian().y };

  double posX{ x * Constant::nodeSideLength * sqrt(3) };
  double posY{ 3 * y * Constant::nodeSideLength / 2 };
  if(y % 2 == 1)
  {
    posX = x * Constant::nodeSideLength * sqrt(3) + Constant::nodeSideLength * sqrt(3) / 2;
    posY = 3 * y * Constant::nodeSideLength / 2;
  }

  vertices.at(0).position = sf::Vector2f(posX, 
                                         posY + Constant::nodeSideLength / 2);
  vertices.at(1).position = sf::Vector2f(posX + (Constant::nodeSideLength * sqrt(3)) / 2, 
                                         posY);
  vertices.at(2).position = sf::Vector2f(posX + Constant::nodeSideLength * sqrt(3), 
                                         posY + Constant::nodeSideLength / 2);
  vertices.at(3).position = sf::Vector2f(posX + Constant::nodeSideLength * sqrt(3),
                                         posY + 3 * Constant::nodeSideLength / 2);
  vertices.at(4).position = sf::Vector2f(posX + (Constant::nodeSideLength * sqrt(3)) / 2, 
                                         posY + 2 * Constant::nodeSideLength);
  vertices.at(5).position = sf::Vector2f(posX, 
                                         posY + 3 * Constant::nodeSideLength / 2);
  vertices.at(6).position = vertices.at(0).position;
}

HexVector MapNode::getHexPosition()
{
  return hexPosition;
}
