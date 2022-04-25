#include "unit.h"
#include "mapnode.h"
#include <SFML/Graphics.hpp>

Unit::Unit(int x, int y, std::string name, int movePoints)
   : positioningNode{ x, y },
     movePoints{ movePoints },
     maxMovePoints{ movePoints },
     name{ name }
{

}

sf::Vector2f Unit::getPosition()
{
  return positioningNode.getPosition();
}
      
void Unit::setPosition(HexVector newPosition)
{
  positioningNode.setPosition(newPosition);
}

HexVector Unit::getHexPosition()
{
  return positioningNode.getHexPosition();
}

std::string Unit::getName()
{
  return name;
}
      
int Unit::getHealth()
{
  return health;
}

int Unit::getMaxHealth()
{
  return maxHealth;
}
      
void Unit::regenerateMovePoints()
{
  movePoints = maxMovePoints;
}

void Unit::decreaseMovePoints(int pointsToDecrease)
{
  movePoints -= pointsToDecrease;
}

int Unit::getMovePoints()
{
  return movePoints;
}

int Unit::getMaxMovePoints()
{
  return maxMovePoints;
}
