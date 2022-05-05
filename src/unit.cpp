#include "unit.h"
#include "mapnode.h"
#include <SFML/Graphics.hpp>

  #include <iostream>

Unit::Unit(int x, int y, std::string name, int movePoints, std::vector<int> moveCosts)
   : positioningNode{ x, y },
     movePoints{ movePoints },
     maxMovePoints{ movePoints },
     moveCosts{ moveCosts },
     name{ name }
{

}


int hexToID(HexVector vector, int sizeX)
{
  return vector.toCartesian().y * sizeX + vector.toCartesian().x;
}

HexVector neighbours(HexVector pos, int dir)
{
  switch(dir)
  {
    case 0: //NW
      return HexVector(pos.q,
                       pos.r - 1,
                       pos.s + 1); 
    break;  

    case 1: //NE
      return HexVector(pos.q + 1,
                       pos.r - 1,
                       pos.s    ); 
      
    break;  

    case 2: //E
      return HexVector(pos.q + 1,
                       pos.r,
                       pos.s - 1); 
       
    break;  

    case 3: //SE
      return HexVector(pos.q,
                       pos.r + 1,
                       pos.s - 1); 
       
    break;  

    case 4: //SW
      return HexVector(pos.q - 1,
                       pos.r + 1,
                       pos.s    ); 
       
    break;  

    case 5: //W
      return HexVector(pos.q - 1,
                       pos.r,
                       pos.s + 1); 

    break;
  } 

  return HexVector();
}

void Unit::calculatePath(HexVector position, int sizeX, int sizeY)
{
  HexVector move{ position };

  while(!(move == positioningNode.getHexPosition()))
  {
    moveQueue.push_back(move); 

    HexVector hvNW{ neighbours(move, 0) };
    HexVector hvNE{ neighbours(move, 1) };
    HexVector hvE { neighbours(move, 2) };
    HexVector hvSE{ neighbours(move, 3) };
    HexVector hvSW{ neighbours(move, 4) };
    HexVector hvW { neighbours(move, 5) };

    int lowestMC{ 1000000 };
    if(hvNW.toCartesian().x >= 0 && hvNW.toCartesian().x < sizeX
    && hvNW.toCartesian().y >= 0 && hvNW.toCartesian().y < sizeY
    && moveCostMap.at(hexToID(hvNW, sizeX)) < lowestMC)
    {
      lowestMC = moveCostMap.at(hexToID(hvNW, sizeX));
    }
    if(hvNE.toCartesian().x >= 0 && hvNE.toCartesian().x < sizeX
    && hvNE.toCartesian().y >= 0 && hvNE.toCartesian().y < sizeY
    && moveCostMap.at(hexToID(hvNE, sizeX)) < lowestMC)
    {
      lowestMC = moveCostMap.at(hexToID(hvNE, sizeX));
    }
    if(hvE.toCartesian().x >= 0 && hvE.toCartesian().x < sizeX
    && hvE.toCartesian().y >= 0 && hvE.toCartesian().y < sizeY
    && moveCostMap.at(hexToID(hvE, sizeX)) < lowestMC)
    {
      lowestMC = moveCostMap.at(hexToID(hvE, sizeX));
    }
    if(hvSE.toCartesian().x >= 0 && hvSE.toCartesian().x < sizeX
    && hvSE.toCartesian().y >= 0 && hvSE.toCartesian().y < sizeY
    && moveCostMap.at(hexToID(hvSE, sizeX)) < lowestMC)
    {
      lowestMC = moveCostMap.at(hexToID(hvSE, sizeX));
    }
    if(hvSW.toCartesian().x >= 0 && hvSW.toCartesian().x < sizeX
    && hvSW.toCartesian().y >= 0 && hvSW.toCartesian().y < sizeY
    && moveCostMap.at(hexToID(hvSW, sizeX)) < lowestMC)
    {
      lowestMC = moveCostMap.at(hexToID(hvSW, sizeX));
    }
    if(hvW.toCartesian().x >= 0 && hvW.toCartesian().x < sizeX
    && hvW.toCartesian().y >= 0 && hvW.toCartesian().y < sizeY
    && moveCostMap.at(hexToID(hvW, sizeX)) < lowestMC)
    {
      lowestMC = moveCostMap.at(hexToID(hvW, sizeX));
    }

    if(hvNW.toCartesian().x >= 0 && hvNW.toCartesian().x < sizeX
    && hvNW.toCartesian().y >= 0 && hvNW.toCartesian().y < sizeY
    && lowestMC == moveCostMap.at(hexToID(hvNW, sizeX)))
    {
      move = hvNW;
    }
    else if(hvNE.toCartesian().x >= 0 && hvNE.toCartesian().x < sizeX
         && hvNE.toCartesian().y >= 0 && hvNE.toCartesian().y < sizeY
         && lowestMC ==  moveCostMap.at(hexToID(hvNE, sizeX)))
    {
      move = hvNE;
    }
    else if(hvE.toCartesian().x >= 0 && hvE.toCartesian().x < sizeX
         && hvE.toCartesian().y >= 0 && hvE.toCartesian().y < sizeY
         && lowestMC ==  moveCostMap.at(hexToID(hvE, sizeX)))
    {
      move = hvE;
    }
    else if(hvSE.toCartesian().x >= 0 && hvSE.toCartesian().x < sizeX
         && hvSE.toCartesian().y >= 0 && hvSE.toCartesian().y < sizeY
         && lowestMC ==  moveCostMap.at(hexToID(hvSE, sizeX)))
    {
      move = hvSE;
    }
    else if(hvSW.toCartesian().x >= 0 && hvSW.toCartesian().x < sizeX
         && hvSW.toCartesian().y >= 0 && hvSW.toCartesian().y < sizeY
         && lowestMC ==  moveCostMap.at(hexToID(hvSW, sizeX)))
    {
      move = hvSW;
    }
    else if(hvW.toCartesian().x >= 0 && hvW.toCartesian().x < sizeX
         && hvW.toCartesian().y >= 0 && hvW.toCartesian().y < sizeY)
    {
      move = hvW;
    }

  }
  
}
      
void Unit::move(int sizeX)
{
  if(moveQueue.size() > 0)
  {
    int moveCost{ moveCostMap.at(moveQueue.back().toCartesian().y * sizeX + moveQueue.back().toCartesian().x) };
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
      
void Unit::generateMCM(int sizeX, int sizeY, std::vector<MapNode>& nodes)
{
  moveCostMap.clear();
  frontier.clear();
  priority.clear();
  
  for(int y{ 0 }; y < sizeY; ++y)
  {
    for(int x{ 0 }; x < sizeX; ++x)
    {
      priority.push_back(moveCosts.at(static_cast<int>(nodes.at(y * sizeX + x).getTerrainType())));
      moveCostMap.push_back(0);

    }
  }

  frontier.push_back(&nodes.at(positioningNode.getHexPosition().toCartesian().y * sizeX 
                             + positioningNode.getHexPosition().toCartesian().x));

  int counter{ 0 };
  while(frontier.size() != 0)
  {
    ++counter;
    if(counter > 10000)
    {
      break;
    }
    
    HexVector currentNodeHexPos{ frontier.at(0)->getHexPosition() };

    //NW
    HexVector hvNW{ currentNodeHexPos.q,
                    currentNodeHexPos.r - 1,
                    currentNodeHexPos.s + 1 };

    if(hvNW.toCartesian().x >= 0 && hvNW.toCartesian().y >= 0
    && hvNW.toCartesian().x < sizeX && hvNW.toCartesian().y < sizeY)
    {
      if(moveCostMap.at(hexToID(hvNW, sizeX)) == 0
      && !(hvNW == positioningNode.getHexPosition()))
      {

        int minimalMC{ 0 };
        //take the lowest non-zero MC from neighbours as base, or unit node MC (which is zero)
        if(!(neighbours(hvNW, 0) == positioningNode.getHexPosition()
          || neighbours(hvNW, 1) == positioningNode.getHexPosition()
          || neighbours(hvNW, 2) == positioningNode.getHexPosition()
          || neighbours(hvNW, 3) == positioningNode.getHexPosition()
          || neighbours(hvNW, 4) == positioningNode.getHexPosition()
          || neighbours(hvNW, 5) == positioningNode.getHexPosition()))
        {

          minimalMC = 1000000;  //I assume nodes will have smaller MC


          if(hexToID(neighbours(hvNW, 0), sizeX) >= 0
          && hexToID(neighbours(hvNW, 0), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvNW, 0), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvNW, 0), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvNW, 0), sizeX));
          }
          if(hexToID(neighbours(hvNW, 1), sizeX) >= 0
          && hexToID(neighbours(hvNW, 1), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvNW, 1), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvNW, 1), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvNW, 1), sizeX));
          }
          if(hexToID(neighbours(hvNW, 2), sizeX) >= 0
          && hexToID(neighbours(hvNW, 2), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvNW, 2), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvNW, 2), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvNW, 2), sizeX));
          }
          if(hexToID(neighbours(hvNW, 3), sizeX) >= 0
          && hexToID(neighbours(hvNW, 3), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvNW, 3), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvNW, 3), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvNW, 3), sizeX));
          }
          if(hexToID(neighbours(hvNW, 4), sizeX) >= 0
          && hexToID(neighbours(hvNW, 4), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvNW, 4), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvNW, 4), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvNW, 4), sizeX));
          }
          if(hexToID(neighbours(hvNW, 5), sizeX) >= 0
          && hexToID(neighbours(hvNW, 5), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvNW, 5), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvNW, 5), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvNW, 5), sizeX));
          }

        }

        moveCostMap.at(hexToID(hvNW, sizeX)) = minimalMC 
                                               + priority.at(hexToID(hvNW, sizeX));
      }

      frontier.push_back(&nodes.at(hexToID(hvNW, sizeX)));
    }

    //NE
    HexVector hvNE{ currentNodeHexPos.q + 1,
                    currentNodeHexPos.r - 1,
                    currentNodeHexPos.s     };

    if(hvNE.toCartesian().x >= 0 && hvNE.toCartesian().y >= 0
    && hvNE.toCartesian().x < sizeX && hvNE.toCartesian().y < sizeY)
    {

      if(moveCostMap.at(hexToID(hvNE, sizeX)) == 0
      && !(hvNE == positioningNode.getHexPosition()))
      {

        int minimalMC{ 0 };
        //take the lowest non-zero MC from neighbours as base, or unit node MC (which is zero)
        if(!(neighbours(hvNE, 0) == positioningNode.getHexPosition()
          || neighbours(hvNE, 1) == positioningNode.getHexPosition()
          || neighbours(hvNE, 2) == positioningNode.getHexPosition()
          || neighbours(hvNE, 3) == positioningNode.getHexPosition()
          || neighbours(hvNE, 4) == positioningNode.getHexPosition()
          || neighbours(hvNE, 5) == positioningNode.getHexPosition()))
        {

          minimalMC = 1000000;  //I assume nodes will have smaller MC


          if(hexToID(neighbours(hvNE, 0), sizeX) >= 0
          && hexToID(neighbours(hvNE, 0), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvNE, 0), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvNE, 0), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvNE, 0), sizeX));
          }
          if(hexToID(neighbours(hvNE, 1), sizeX) >= 0
          && hexToID(neighbours(hvNE, 1), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvNE, 1), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvNE, 1), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvNE, 1), sizeX));
          }
          if(hexToID(neighbours(hvNE, 2), sizeX) >= 0
          && hexToID(neighbours(hvNE, 2), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvNE, 2), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvNE, 2), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvNE, 2), sizeX));
          }
          if(hexToID(neighbours(hvNE, 3), sizeX) >= 0
          && hexToID(neighbours(hvNE, 3), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvNE, 3), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvNE, 3), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvNE, 3), sizeX));
          }
          if(hexToID(neighbours(hvNE, 4), sizeX) >= 0
          && hexToID(neighbours(hvNE, 4), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvNE, 4), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvNE, 4), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvNE, 4), sizeX));
          }
          if(hexToID(neighbours(hvNE, 5), sizeX) >= 0
          && hexToID(neighbours(hvNE, 5), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvNE, 5), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvNE, 5), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvNE, 5), sizeX));
          }

        }

        moveCostMap.at(hexToID(hvNE, sizeX)) = minimalMC 
                                               + priority.at(hexToID(hvNE, sizeX));
      }

      frontier.push_back(&nodes.at(hexToID(hvNE, sizeX)));
    }
    

    //E
    HexVector hvE{ currentNodeHexPos.q + 1,
                   currentNodeHexPos.r,
                   currentNodeHexPos.s - 1 };
    
    if(hvE.toCartesian().x >= 0 && hvE.toCartesian().y >= 0
    && hvE.toCartesian().x < sizeX && hvE.toCartesian().y < sizeY)
    {

      if(moveCostMap.at(hexToID(hvE, sizeX)) == 0
      && !(hvE == positioningNode.getHexPosition()))
      {

        int minimalMC{ 0 };
        //take the lowest non-zero MC from neighbours as base, or unit node MC (which is zero)
        if(!(neighbours(hvE, 0) == positioningNode.getHexPosition()
          || neighbours(hvE, 1) == positioningNode.getHexPosition()
          || neighbours(hvE, 2) == positioningNode.getHexPosition()
          || neighbours(hvE, 3) == positioningNode.getHexPosition()
          || neighbours(hvE, 4) == positioningNode.getHexPosition()
          || neighbours(hvE, 5) == positioningNode.getHexPosition()))
        {

          minimalMC = 1000000;  //I assume nodes will have smaller MC


          if(hexToID(neighbours(hvE, 0), sizeX) >= 0
          && hexToID(neighbours(hvE, 0), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvE, 0), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvE, 0), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvE, 0), sizeX));
          }
          if(hexToID(neighbours(hvE, 1), sizeX) >= 0
          && hexToID(neighbours(hvE, 1), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvE, 1), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvE, 1), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvE, 1), sizeX));
          }
          if(hexToID(neighbours(hvE, 2), sizeX) >= 0
          && hexToID(neighbours(hvE, 2), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvE, 2), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvE, 2), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvE, 2), sizeX));
          }
          if(hexToID(neighbours(hvE, 3), sizeX) >= 0
          && hexToID(neighbours(hvE, 3), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvE, 3), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvE, 3), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvE, 3), sizeX));
          }
          if(hexToID(neighbours(hvE, 4), sizeX) >= 0
          && hexToID(neighbours(hvE, 4), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvE, 4), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvE, 4), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvE, 4), sizeX));
          }
          if(hexToID(neighbours(hvE, 5), sizeX) >= 0
          && hexToID(neighbours(hvE, 5), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvE, 5), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvE, 5), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvE, 5), sizeX));
          }

        }

        moveCostMap.at(hexToID(hvE, sizeX)) = minimalMC 
                                               + priority.at(hexToID(hvE, sizeX));
      }

      frontier.push_back(&nodes.at(hexToID(hvE, sizeX)));
    }

    //SE
    HexVector hvSE{ currentNodeHexPos.q,
                    currentNodeHexPos.r + 1,
                    currentNodeHexPos.s - 1 };

    if(hvSE.toCartesian().x >= 0 && hvSE.toCartesian().y >= 0
    && hvSE.toCartesian().x < sizeX && hvSE.toCartesian().y < sizeY)
    {
      if(moveCostMap.at(hexToID(hvSE, sizeX)) == 0
      && !(hvSE == positioningNode.getHexPosition()))
      {

        int minimalMC{ 0 };
        //take the lowest non-zero MC from neighbours as base, or unit node MC (which is zero)
        if(!(neighbours(hvSE, 0) == positioningNode.getHexPosition()
          || neighbours(hvSE, 1) == positioningNode.getHexPosition()
          || neighbours(hvSE, 2) == positioningNode.getHexPosition()
          || neighbours(hvSE, 3) == positioningNode.getHexPosition()
          || neighbours(hvSE, 4) == positioningNode.getHexPosition()
          || neighbours(hvSE, 5) == positioningNode.getHexPosition()))
        {

          minimalMC = 1000000;  //I assume nodes will have smaller MC


          if(hexToID(neighbours(hvSE, 0), sizeX) >= 0
          && hexToID(neighbours(hvSE, 0), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvSE, 0), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvSE, 0), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvSE, 0), sizeX));
          }
          if(hexToID(neighbours(hvSE, 1), sizeX) >= 0
          && hexToID(neighbours(hvSE, 1), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvSE, 1), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvSE, 1), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvSE, 1), sizeX));
          }
          if(hexToID(neighbours(hvSE, 2), sizeX) >= 0
          && hexToID(neighbours(hvSE, 2), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvSE, 2), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvSE, 2), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvSE, 2), sizeX));
          }
          if(hexToID(neighbours(hvSE, 3), sizeX) >= 0
          && hexToID(neighbours(hvSE, 3), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvSE, 3), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvSE, 3), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvSE, 3), sizeX));
          }
          if(hexToID(neighbours(hvSE, 4), sizeX) >= 0
          && hexToID(neighbours(hvSE, 4), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvSE, 4), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvSE, 4), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvSE, 4), sizeX));
          }
          if(hexToID(neighbours(hvSE, 5), sizeX) >= 0
          && hexToID(neighbours(hvSE, 5), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvSE, 5), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvSE, 5), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvSE, 5), sizeX));
          }

        }

        moveCostMap.at(hexToID(hvSE, sizeX)) = minimalMC 
                                               + priority.at(hexToID(hvSE, sizeX));
      }

      frontier.push_back(&nodes.at(hexToID(hvSE, sizeX)));
    }

    //SW
    HexVector hvSW{ currentNodeHexPos.q - 1,
                    currentNodeHexPos.r + 1,
                    currentNodeHexPos.s     };
    
    if(hvSW.toCartesian().x >= 0 && hvSW.toCartesian().y >= 0
    && hvSW.toCartesian().x < sizeX && hvSW.toCartesian().y < sizeY)
    {
      if(moveCostMap.at(hexToID(hvSW, sizeX)) == 0
      && !(hvSW == positioningNode.getHexPosition()))
      {

        int minimalMC{ 0 };
        //take the lowest non-zero MC from neighbours as base, or unit node MC (which is zero)
        if(!(neighbours(hvSW, 0) == positioningNode.getHexPosition()
          || neighbours(hvSW, 1) == positioningNode.getHexPosition()
          || neighbours(hvSW, 2) == positioningNode.getHexPosition()
          || neighbours(hvSW, 3) == positioningNode.getHexPosition()
          || neighbours(hvSW, 4) == positioningNode.getHexPosition()
          || neighbours(hvSW, 5) == positioningNode.getHexPosition()))
        {

          minimalMC = 1000000;  //I assume nodes will have smaller MC


          if(hexToID(neighbours(hvSW, 0), sizeX) >= 0
          && hexToID(neighbours(hvSW, 0), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvSW, 0), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvSW, 0), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvSW, 0), sizeX));
          }
          if(hexToID(neighbours(hvSW, 1), sizeX) >= 0
          && hexToID(neighbours(hvSW, 1), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvSW, 1), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvSW, 1), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvSW, 1), sizeX));
          }
          if(hexToID(neighbours(hvSW, 2), sizeX) >= 0
          && hexToID(neighbours(hvSW, 2), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvSW, 2), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvSW, 2), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvSW, 2), sizeX));
          }
          if(hexToID(neighbours(hvSW, 3), sizeX) >= 0
          && hexToID(neighbours(hvSW, 3), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvSW, 3), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvSW, 3), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvSW, 3), sizeX));
          }
          if(hexToID(neighbours(hvSW, 4), sizeX) >= 0
          && hexToID(neighbours(hvSW, 4), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvSW, 4), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvSW, 4), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvSW, 4), sizeX));
          }
          if(hexToID(neighbours(hvSW, 5), sizeX) >= 0
          && hexToID(neighbours(hvSW, 5), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvSW, 5), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvSW, 5), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvSW, 5), sizeX));
          }

        }

        moveCostMap.at(hexToID(hvSW, sizeX)) = minimalMC 
                                               + priority.at(hexToID(hvSW, sizeX));
      }

      frontier.push_back(&nodes.at(hexToID(hvSW, sizeX)));
    }

    //W
    HexVector hvW{ currentNodeHexPos.q - 1,
                   currentNodeHexPos.r,
                   currentNodeHexPos.s + 1 };
    
    if(hvW.toCartesian().x >= 0 && hvW.toCartesian().y >= 0
    && hvW.toCartesian().x < sizeX && hvW.toCartesian().y < sizeY)
    {
      if(moveCostMap.at(hexToID(hvW, sizeX)) == 0
      && !(hvW == positioningNode.getHexPosition()))
      {

        int minimalMC{ 0 };
        //take the lowest non-zero MC from neighbours as base, or unit node MC (which is zero)
        if(!(neighbours(hvW, 0) == positioningNode.getHexPosition()
          || neighbours(hvW, 1) == positioningNode.getHexPosition()
          || neighbours(hvW, 2) == positioningNode.getHexPosition()
          || neighbours(hvW, 3) == positioningNode.getHexPosition()
          || neighbours(hvW, 4) == positioningNode.getHexPosition()
          || neighbours(hvW, 5) == positioningNode.getHexPosition()))
        {

          minimalMC = 1000000;  //I assume nodes will have smaller MC


          if(hexToID(neighbours(hvW, 0), sizeX) >= 0
          && hexToID(neighbours(hvW, 0), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvW, 0), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvW, 0), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvW, 0), sizeX));
          }
          if(hexToID(neighbours(hvW, 1), sizeX) >= 0
          && hexToID(neighbours(hvW, 1), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvW, 1), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvW, 1), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvW, 1), sizeX));
          }
          if(hexToID(neighbours(hvW, 2), sizeX) >= 0
          && hexToID(neighbours(hvW, 2), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvW, 2), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvW, 2), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvW, 2), sizeX));
          }
          if(hexToID(neighbours(hvW, 3), sizeX) >= 0
          && hexToID(neighbours(hvW, 3), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvW, 3), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvW, 3), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvW, 3), sizeX));
          }
          if(hexToID(neighbours(hvW, 4), sizeX) >= 0
          && hexToID(neighbours(hvW, 4), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvW, 4), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvW, 4), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvW, 4), sizeX));
          }
          if(hexToID(neighbours(hvW, 5), sizeX) >= 0
          && hexToID(neighbours(hvW, 5), sizeX) < nodes.size()
          && moveCostMap.at(hexToID(neighbours(hvW, 5), sizeX)) != 0
          && moveCostMap.at(hexToID(neighbours(hvW, 5), sizeX)) < minimalMC)
          {
            minimalMC = moveCostMap.at(hexToID(neighbours(hvW, 5), sizeX));
          }

        }

        moveCostMap.at(hexToID(hvW, sizeX)) = minimalMC 
                                               + priority.at(hexToID(hvW, sizeX));
      }

      frontier.push_back(&nodes.at(hexToID(hvW, sizeX)));
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
