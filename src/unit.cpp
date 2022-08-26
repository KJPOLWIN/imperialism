#include "unit.h"
#include "mapnode.h"
#include <SFML/Graphics.hpp>

  #include <iostream>

Unit::Unit(int x, int y, 
           std::string name, 
           int movePoints, std::vector<int> moveCosts, 
           int faction)
   : positioningNode{ x, y },
     movePoints{ movePoints },
     maxMovePoints{ movePoints },
     moveCosts{ moveCosts },
     name{ name },
     faction{ faction }
{

}

void Unit::calculatePath(HexVector position, int sizeX, int sizeY)
{
  while(!(position == positioningNode.getHexPosition()))
  {
    moveQueue.push_back(position); 

    int lowestMC{ 1000000 };

    for(int iii{ 0 }; iii <= 5; ++iii)
    {
      if(position.getNeighbour(iii).isInBoundaries(sizeX, sizeY)
      && moveCostMap.at(position.getNeighbour(iii).toID(sizeX)) < lowestMC)
      {
        lowestMC = moveCostMap.at(position.getNeighbour(iii).toID(sizeX));
      }
    }

    if(position.getNW().isInBoundaries(sizeX, sizeY)
    && lowestMC == moveCostMap.at(position.getNW().toID(sizeX)))
    {
      position = position.getNW();
    }
    else if(position.getNE().isInBoundaries(sizeX, sizeY)
    && lowestMC == moveCostMap.at(position.getNE().toID(sizeX)))
    {
      position = position.getNE();
    }
    else if(position.getE().isInBoundaries(sizeX, sizeY)
    && lowestMC == moveCostMap.at(position.getE().toID(sizeX)))
    {
      position = position.getE();
    }
    else if(position.getSE().isInBoundaries(sizeX, sizeY)
    && lowestMC == moveCostMap.at(position.getSE().toID(sizeX)))
    {
      position = position.getSE();
    }
    else if(position.getSW().isInBoundaries(sizeX, sizeY)
    && lowestMC == moveCostMap.at(position.getSW().toID(sizeX)))
    {
      position = position.getSW();
    }
    else if(position.getW().isInBoundaries(sizeX, sizeY))
    {
      position = position.getW();
    }
  }
}
      
void Unit::move(int sizeX)
{
  if(moveQueue.size() > 0)
  {
    int moveCost{ priority.at(moveQueue.back().toID(sizeX)) };
    
    if(moveCost <= movePoints)
    {
      setPosition(moveQueue.back());
      moveQueue.pop_back();
      movePoints -= moveCost;
    }
    else
    {
      moveQueue.clear();
    }
  }
}

void Unit::loadMoveCosts(int sizeX, int sizeY, 
                         std::vector<MapNode>& nodes, std::vector<Unit>& units)
{
  priority.clear();
  
  for(int y{ 0 }; y < sizeY; ++y)
  {
    for(int x{ 0 }; x < sizeX; ++x)
    {
      priority.push_back(
        moveCosts.at(
          static_cast<std::size_t>(
            nodes.at(
              static_cast<std::size_t>(y * sizeX + x)).getTerrainType())));
    }
  }

  for(auto& unit : units)
  {
    if(!(unit.getHexPosition() == getHexPosition()))
    {
      priority.at(unit.getHexPosition().toID(sizeX)) = 1000;
    }
  }
}
      
void Unit::generateMCM(int sizeX, int sizeY, std::vector<MapNode>& nodes)
{
  moveCostMap.clear();
  frontier.clear();
  //priority.clear();
  
  for(int y{ 0 }; y < sizeY; ++y)
  {
    for(int x{ 0 }; x < sizeX; ++x)
    {
      moveCostMap.push_back(0);
    }
  }

  frontier.push_back(&nodes.at(positioningNode.getHexPosition().toID(sizeX)));

  while(frontier.size() != 0)
  {
    HexVector currentNodeHexPos{ frontier.at(0)->getHexPosition() };

    for(int dir{ 0 }; dir <= 5; ++dir)
    {
      if(currentNodeHexPos.getNeighbour(dir).isInBoundaries(sizeX, sizeY)
      && moveCostMap.at(currentNodeHexPos.getNeighbour(dir).toID(sizeX)) == 0
      && !(currentNodeHexPos.getNeighbour(dir) == positioningNode.getHexPosition()))
      {
        int minimalMC{ 0 };
        //take the lowest non-zero MC from neighbours as base, or unit node MC (which is zero)
        if(!(currentNodeHexPos.getNeighbour(dir)
                              .isNextToNode(positioningNode.getHexPosition())))
        {
          minimalMC = 1000000;  //I assume nodes will have smaller MC

          for(int iii{ 0 }; iii <= 5; ++iii)
          {
            if(currentNodeHexPos.getNeighbour(dir)
                                .getNeighbour(iii)
                                .toID(sizeX) < nodes.size()
            && moveCostMap.at(currentNodeHexPos.getNeighbour(dir)
                                               .getNeighbour(iii)
                                               .toID(sizeX)) != 0
            && moveCostMap.at(currentNodeHexPos.getNeighbour(dir)
                                               .getNeighbour(iii)
                                               .toID(sizeX)) < minimalMC)
            {
              minimalMC = moveCostMap.at(currentNodeHexPos.getNeighbour(dir)
                                                          .getNeighbour(iii)
                                                          .toID(sizeX));
            }
          }
        }

        moveCostMap.at(
          currentNodeHexPos.getNeighbour(dir)
                           .toID(sizeX)) = minimalMC 
                                         + priority.at(
                                             currentNodeHexPos.getNeighbour(dir)
                                                              .toID(sizeX));
      
        if(moveCostMap.at(currentNodeHexPos.getNeighbour(dir)
                                           .toID(sizeX)) <= maxMovePoints)
        {
          frontier.push_back(&nodes.at(currentNodeHexPos.getNeighbour(dir)
                                                        .toID(sizeX)));
        }
      }
    }

    frontier.erase(frontier.begin());
  }
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

std::vector<int>& Unit::getMoveCosts()
{
  return moveCosts;
}
      
std::vector<int>& Unit::getMoveCostMap()
{
  return moveCostMap;
} 

int Unit::getMoveQueueLenght()
{
  return moveQueue.size();
}
      
int Unit::getFaction()
{
  return faction;
}
