#include "unit.h"
#include "mapnode.h"
#include <SFML/Graphics.hpp>

Unit::Unit(int x, int y)
  : positioningNode{ x, y }
{

}

sf::Vector2f Unit::getPosition()
{
  return positioningNode.getPosition();
}
