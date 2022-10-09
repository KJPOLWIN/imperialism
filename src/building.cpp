#include "building.h"
#include "mapnode.h"
#include <SFML/Graphics.hpp>
#include <string>

Building::Building(int x, int y, std::string name, int faction,
                   int turnsToBuild, 
                   int upkeep, int population,
                   int moneyProduction, int foodProduction,
                   int woodProduction, int stoneProduction,
                   int weaponsProduction)
  : positioningNode{ x, y },
    turnsToBuild{ turnsToBuild },
    name{ name },
    faction{ faction },
    upkeep{ upkeep },
    population{ population },
    moneyProduction{ moneyProduction },
    foodProduction{ foodProduction },
    woodProduction{ woodProduction },
    stoneProduction{ stoneProduction },
    weaponsProduction{ weaponsProduction }
{
  if(turnsToBuild < 1)
  {
    completed = true;
  }
}

void Building::update()
{
  if(!completed)
  {
    --turnsToBuild;
    if(turnsToBuild == 0) completed = true;
  }
}

sf::Vector2f Building::getPosition()
{
  return positioningNode.getPosition();
}
HexVector Building::getHexPosition()
{
  return positioningNode.getHexPosition();
}
      
void Building::setPosition(HexVector newPosition)
{
  positioningNode.setPosition(newPosition);
}
      
std::string Building::getName()
{
  return name;
}

int Building::getFaction()
{
  return faction;
}

int Building::getUpkeep()
{
  return upkeep;
}

int Building::getFoodCost()
{
  return population;
}

int Building::getMoneyProduction()
{
  return moneyProduction;
}

int Building::getFoodProduction()
{
  return foodProduction;
}

int Building::getWoodProduction()
{
  return woodProduction;
}

int Building::getStoneProduction()
{
  return stoneProduction;
}

int Building::getWeaponsProduction()
{
  return weaponsProduction;
}
      
int Building::getTurnsToBuild()
{
  return turnsToBuild;
}
