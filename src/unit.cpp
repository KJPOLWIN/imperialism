#include "unit.h"
#include "mapnode.h"
#include <SFML/Graphics.hpp>

Unit::Unit(int x, int y, std::string name)
   : positioningNode{ x, y },
     name{ name }
{

}

sf::Vector2f Unit::getPosition()
{
  return positioningNode.getPosition();
}

HexVector Unit::getHexPosition()
{
  return positioningNode.getHexPosition();
}

std::string Unit::getName()
{
  return name;
}
