#include "map.h"
#include "mapnode.h"
#include "random.h"
#include "constant.h"
#include <SFML/Graphics.hpp>
#include "json.hpp"
#include <vector>
#include <cmath>
#include <fstream>

  #include <iostream>

Map::Map()
{
  clickmap.loadFromFile("clickmap.png");

  //loading textures and sprites
  selectedNodeTexture.loadFromFile("texture/selectednode.png");
  grassNodeTexture.loadFromFile("texture/nodegrass.png");
  waterNodeTexture.loadFromFile("texture/nodewater.png");
  desertNodeTexture.loadFromFile("texture/nodedesert.png");
  tundraNodeTexture.loadFromFile("texture/nodetundra.png");
  grassHillsNodeTexture.loadFromFile("texture/nodegrasshills.png");
  desertHillsNodeTexture.loadFromFile("texture/nodedeserthills.png");
  tundraHillsNodeTexture.loadFromFile("texture/nodetundrahills.png");
  forestNodeTexture.loadFromFile("texture/nodeforest.png");
  forestHillsNodeTexture.loadFromFile("texture/nodeforesthills.png");
  jungleNodeTexture.loadFromFile("texture/nodejungle.png");
  jungleHillsNodeTexture.loadFromFile("texture/nodejunglehills.png");
  mountainsNodeTexture.loadFromFile("texture/nodemountain.png");
  grasslandRiverNodeTexture.loadFromFile("texture/nodegrasslandriver.png");
  desertRiverNodeTexture.loadFromFile("texture/nodedesertriver.png");
  tundraRiverNodeTexture.loadFromFile("texture/nodetundrariver.png");
  riflemenTexture.loadFromFile("texture/riflemen.png");

  selectedNode.setTexture(selectedNodeTexture);
  grassNode.setTexture(grassNodeTexture);
  waterNode.setTexture(waterNodeTexture);
  desertNode.setTexture(desertNodeTexture);
  tundraNode.setTexture(tundraNodeTexture);
  grassHillsNode.setTexture(grassHillsNodeTexture);
  desertHillsNode.setTexture(desertHillsNodeTexture);
  tundraHillsNode.setTexture(tundraHillsNodeTexture);
  forestNode.setTexture(forestNodeTexture);
  forestHillsNode.setTexture(forestHillsNodeTexture);
  jungleNode.setTexture(jungleNodeTexture);
  jungleHillsNode.setTexture(jungleHillsNodeTexture);
  mountainsNode.setTexture(mountainsNodeTexture);
  grasslandRiverNode.setTexture(grasslandRiverNodeTexture);
  desertRiverNode.setTexture(desertRiverNodeTexture);
  tundraRiverNode.setTexture(tundraRiverNodeTexture);
  riflemenSprite.setTexture(riflemenTexture);
}
      
void Map::nextTurn()
{
  for( auto& unit : units )
  {
    unit.regenerateMovePoints();
  }
}

void Map::moveUnits(HexVector position)
{
  if(position.isInBoundaries(sizeX, sizeY))
  {
    for( auto& unit : units )
    {
      if(unit.isSelected && unit.getFaction() == 0)
      {
        int unitMP{ unit.getMovePoints() };
        int nodeCost{ unit.getMoveCostMap().at(position.toID(sizeX)) };
      
        if(nodeCost != 0
        && nodeCost <= unitMP)
        {
          unit.calculatePath(position, sizeX, sizeY);
        }

        while(unit.getMoveQueueLenght() > 0)
        {
          unit.move(sizeX);
        }

        unit.loadMoveCosts(sizeX, sizeY, nodes, units);
        unit.generateMCM(sizeX, sizeY, nodes);
      }
    }
  }
}

sf::Vector2i Map::getClickedNode(sf::Vector2f clickPosition, sf::Vector2f viewOffset, double zoom)
{
  sf::Vector2f point{ static_cast<float>(clickPosition.x + viewOffset.x / zoom),
                      static_cast<float>(clickPosition.y + viewOffset.y / zoom) };
  double hexSize{ Constant::nodeSideLength / zoom };
  int tileX{ static_cast<int>(point.x / (hexSize * sqrt(3))) };
  int tileY{ static_cast<int>(point.y / (3 * hexSize)) };

  if(point.x < 0)
  {
    --tileX;
  }
  if(point.y < 0)
  {
    --tileY;
  }

  double xmod{ (point.x - tileX * hexSize * sqrt(3)) * zoom };
  double ymod{ (point.y - tileY * 3 * hexSize) * zoom };

  int x{ tileX };
  int y{ tileY * 2 };

  if(xmod >= 0 && ymod >= 0)
  {
    sf::Color area{ clickmap.getPixel(static_cast<unsigned int>(xmod), 
                                      static_cast<unsigned int>(ymod)) };
    if(area == sf::Color::Red)
    {
      --x;
      --y;
    }
    else if(area == sf::Color::Yellow)
    {
      --y;
    }
    else if(area == sf::Color::Green)
    {
      --x;
      ++y;
    }
    else if(area == sf::Color::Blue)
    {
      ++y;
    }
  }

  return sf::Vector2i(x, y);
}

void Map::selectNodesAndUnits(sf::Vector2f clickPosition, sf::Vector2f viewOffset, double zoom)
{
  for( auto& node : nodes )
  {
    node.disselect();
  }

  for( auto& unit : units )
  {
    unit.isSelected = false;
  }
  
  sf::Vector2i selectedNodeCartesian{ getClickedNode(clickPosition, viewOffset, zoom) };

  if(selectedNodeCartesian.x >= 0 && selectedNodeCartesian.x < sizeX 
  && selectedNodeCartesian.y >= 0 && selectedNodeCartesian.y < sizeY)
  {
    getNode(selectedNodeCartesian).select();

    for( auto& unit : units )
    {
      if(unit.getHexPosition() == HexVector(selectedNodeCartesian))
      {
        unit.isSelected = true;
        unit.loadMoveCosts(sizeX, sizeY, nodes, units);
        unit.generateMCM(sizeX, sizeY, nodes);
        break;
      }
    }
  }
}

bool isVisible(sf::Vector2f nodePosition, sf::Vector2f viewOffset, double zoom)
{
  return (nodePosition.x > viewOffset.x - Constant::nodeSideLength * sqrt(3)
       && nodePosition.y > viewOffset.y - Constant::nodeSideLength * 2
       && nodePosition.x < viewOffset.x + Constant::windowWidth  * zoom
       && nodePosition.y < viewOffset.y + Constant::windowHeight * zoom);
}

void Map::draw(sf::RenderWindow& targetWindow, sf::Vector2f viewOffset, double zoom)
{
  for( auto& node : nodes )
  {
    if(isVisible(node.getPosition(), viewOffset, zoom))
    {
      switch(node.getTerrainType())
      {
        case TerrainType::water:
          waterNode.setPosition(node.getPosition());
          targetWindow.draw(waterNode);
        break;

        case TerrainType::plains:
          switch(node.getClimateZone())
          {
            case ClimateZone::polar:
              tundraNode.setPosition(node.getPosition());
              targetWindow.draw(tundraNode);
            break;

            case ClimateZone::dry:
              desertNode.setPosition(node.getPosition());
              targetWindow.draw(desertNode);
            break;

            case ClimateZone::temperate:
            case ClimateZone::tropical:
              grassNode.setPosition(node.getPosition());
              targetWindow.draw(grassNode);
            break;
          }
        break;

        case TerrainType::hills:
          switch(node.getClimateZone())
          {
            case ClimateZone::polar:
              tundraHillsNode.setPosition(node.getPosition());
              targetWindow.draw(tundraHillsNode);
            break;

            case ClimateZone::dry:
              desertHillsNode.setPosition(node.getPosition());
              targetWindow.draw(desertHillsNode);
            break;
            
            case ClimateZone::temperate:
            case ClimateZone::tropical:
              grassHillsNode.setPosition(node.getPosition());
              targetWindow.draw(grassHillsNode);
            break;
          }
        break;

        case TerrainType::mountains:
          mountainsNode.setPosition(node.getPosition());
          targetWindow.draw(mountainsNode);
        break;

        case TerrainType::forest:
          switch(node.getClimateZone())
          {
            case ClimateZone::temperate:
              forestNode.setPosition(node.getPosition());
              targetWindow.draw(forestNode);
            break;

            case ClimateZone::tropical:
              jungleNode.setPosition(node.getPosition());
              targetWindow.draw(jungleNode);
            break;

            case ClimateZone::polar:
            case ClimateZone::dry:
            break;
          }
        break;

        case TerrainType::forestHills:
          switch(node.getClimateZone())
          {
            case ClimateZone::temperate:
              forestHillsNode.setPosition(node.getPosition());
              targetWindow.draw(forestHillsNode);
            break;

            case ClimateZone::tropical:
              jungleHillsNode.setPosition(node.getPosition());
              targetWindow.draw(jungleHillsNode);
            break;
            
            case ClimateZone::polar:
            case ClimateZone::dry:
            break;
          }
        break;

        case TerrainType::river:
          switch(node.getClimateZone())
          {
            case ClimateZone::polar:
              tundraRiverNode.setPosition(node.getPosition());
              targetWindow.draw(tundraRiverNode);
            break;

            case ClimateZone::dry:
              desertRiverNode.setPosition(node.getPosition());
              targetWindow.draw(desertRiverNode);
            break;
            
            case ClimateZone::temperate:
            case ClimateZone::tropical:
              grasslandRiverNode.setPosition(node.getPosition());
              targetWindow.draw(grasslandRiverNode);
            break;
          }
        break;

        case TerrainType::blank:
        break;
      }
    }
  }

  //Drawing unselected nodes first, so full selected node's border will be visible
  for( auto& node : nodes )
  {
    if(!node.isSelected
    && isVisible(node.getPosition(), viewOffset, zoom))
    {
      node.draw(targetWindow);
    }
  }
 
  //Drawing selected nodes
  for( auto& node : nodes )
  {
    if(node.isSelected
    && isVisible(node.getPosition(), viewOffset, zoom))
    {
      node.draw(targetWindow);
    }
  }

  for( auto& unit : units )
  {
    //Drawing possible moves
    for( auto& node : nodes )
    {
      if(unit.isSelected
      && isVisible(node.getPosition(), viewOffset, zoom))
      {
        HexVector nodePos{ node.getHexPosition() };
        int unitMP{ unit.getMovePoints() };
        int nodeCost{ unit.getMoveCostMap().at(nodePos.toID(sizeX)) };
        
        if(nodeCost != 0
        && nodeCost <= unitMP)
        {
          selectedNode.setPosition(node.getPosition());
          targetWindow.draw(selectedNode);
        }
      } 
    }

    //Drawing units
    if(isVisible(unit.getPosition(), viewOffset, zoom))
    {
      riflemenSprite.setPosition(unit.getPosition());
      targetWindow.draw(riflemenSprite);
    }
  }
}
 
void Map::regenerate(int sizeX, int sizeY, 
                     int landmassCountP, int landmassMaxSize,
                     double landToWaterChance, double waterToLandChance,
                     int mountainRangeMaxLenght, int mountainRangeCountP,
                     double firstPassHillChance, double secondPassHillChance,
                     double forestChance,
                     double riverChance)
{
  this->sizeX = sizeX;
  this->sizeY = sizeY;

  nodes.clear();
  
  for(int y{ 0 }; y < sizeY; ++y)
  {
    for(int x{ 0 }; x < sizeX; ++x)
    {
      nodes.emplace_back(x, y);
    }
  }
   
  //Creating climate zones 
  for(auto& node : nodes)
  {
    int y{ node.getHexPosition().toCartesian().y };
    //Polar: 1st, 7th
    if(y < sizeY / 7 || y > 6 * sizeY / 7)
    { 
      node.switchClimateZone(ClimateZone::polar);
    }
    //Temperate: 2nd, 6th
    //Dry: 3rd, 5th
    if((y >= 2 * sizeY / 7 && y <= 3 * sizeY / 7)
    || (y >= 4 * sizeY / 7 && y <= 5 * sizeY / 7))
    {
      node.switchClimateZone(ClimateZone::dry);
    }
    //Tropical: 4th
    if(y >= 3 * sizeY / 7 && y <= 4 * sizeY / 7)
    {
      node.switchClimateZone(ClimateZone::tropical);
      
    }
  }

  //Landmass generation
  int landmassCount{ landmassCountP * static_cast<int>(nodes.size()) / 100 };

  int landmassSize{  };
  int landmassX{  };
  int landmassY{  };  

  for(int iii{ 0 }; iii < landmassCount; ++iii)
  {
    landmassSize = Random::getRandomInt(1, landmassMaxSize);
    landmassX = Random::getRandomInt(0, sizeX - 1);
    landmassY = Random::getRandomInt(0, sizeY - 1);  
  
    createLandmass(landmassX, landmassY, landmassSize);
  }

  //Smudging landmasses
  for( auto& node : nodes )
  {
    if(node.getTerrainType() == TerrainType::plains
    && neighboursTerrain(node.getHexPosition(), 
                         TerrainType::water)
    && Random::testForProbability(landToWaterChance))
    {
      node.switchTerrainType(TerrainType::water);
    }
    else if(node.getTerrainType() == TerrainType::water
    && neighboursTerrain(node.getHexPosition(), 
                         TerrainType::plains)
    && Random::testForProbability(waterToLandChance))
    {
      node.switchTerrainType(TerrainType::plains);
    }
  }

  //Mountains generation
  int mountainRangeCount{ mountainRangeCountP * static_cast<int>(nodes.size()) / 100 };

  int rangeX{ 0 };
  int rangeY{ 0 };

  for(int iii{ 0 }; iii < mountainRangeCount; ++iii)
  {
    rangeX = Random::getRandomInt(0, sizeX - 1);
    rangeY = Random::getRandomInt(0, sizeY - 1);
    HexVector rangeHexPosition{ rangeX, rangeY };
  
    for(int jjj{ 0 }; jjj < mountainRangeMaxLenght; ++jjj)
    {
      if(getNode(sf::Vector2i(rangeX, rangeY)).getTerrainType() != TerrainType::blank)
      {
        getNode(sf::Vector2i(rangeX, rangeY)).switchTerrainType(TerrainType::mountains);
        rangeHexPosition.q += Random::getRandomInt(-1, 1);
        rangeHexPosition.r += Random::getRandomInt(-1, 1);
        rangeHexPosition.s += Random::getRandomInt(-1, 1);
      }

      rangeX = rangeHexPosition.toCartesian().x;
      rangeY = rangeHexPosition.toCartesian().y;
    }
  }

  //Hills generation
  for(auto& node : nodes)
  {
    if(neighboursTerrain(node.getHexPosition(), TerrainType::mountains)
    && Random::testForProbability(firstPassHillChance))
    {
      node.switchTerrainType(TerrainType::hills);
    }
  }
  
  for(auto& node : nodes)
  {
    if(node.getTerrainType() == TerrainType::plains
    && neighboursTerrain(node.getHexPosition(), TerrainType::hills)
    && Random::testForProbability(secondPassHillChance))
    {
      node.switchTerrainType(TerrainType::hills);
    }
  }

  //Forest generation
  for(auto& node : nodes)
  {
    if((node.getClimateZone() == ClimateZone::temperate
     || node.getClimateZone() == ClimateZone::tropical)
    && Random::testForProbability(forestChance))
    {
      if(node.getTerrainType() == TerrainType::plains)
      {
        node.switchTerrainType(TerrainType::forest);
      }
      else if(node.getTerrainType() == TerrainType::hills)
      {
        node.switchTerrainType(TerrainType::forestHills);
      }

    }
  }

  //River generation
  for(auto& node : nodes)
  {
    if(node.getTerrainType() != TerrainType::water 
    && node.getTerrainType() != TerrainType::river
    && node.getTerrainType() != TerrainType::mountains
    && !neighboursTerrain(node.getHexPosition(), TerrainType::river)
    && (neighboursTerrain(node.getHexPosition(), TerrainType::mountains)
     || neighboursTerrain(node.getHexPosition(), TerrainType::hills)
     || neighboursTerrain(node.getHexPosition(), TerrainType::forestHills))
    && Random::testForProbability(riverChance))
    {
      node.switchTerrainType(TerrainType::river);

      double shortestDistanceToWater{ 200.0 * static_cast<double>(sizeX) };
      MapNode* closestWaterNode{ nullptr };
      for(auto& waterNode : nodes)
      {
        if(waterNode.getTerrainType() == TerrainType::water)
        {
          sf::Vector2f nPos{ node.getPosition() };
          sf::Vector2f wnPos{ waterNode.getPosition() }; 
          double distance{ sqrt(pow(nPos.x - wnPos.x, 2) + pow(nPos.y - wnPos.y, 2)) };
          if(distance < shortestDistanceToWater && distance < 2000)
          {
            shortestDistanceToWater = distance;
            closestWaterNode = &waterNode;
          }
        }
      }

      int directionToWater{ Random::getRandomInt(0, 5) };
      if(closestWaterNode != nullptr)
      {
        sf::Vector2f cwtPos{ closestWaterNode->getPosition() };
        double angle{ atan2(cwtPos.y - node.getPosition().y, 
                            cwtPos.x - node.getPosition().x) * 180 / M_PI };
        if(angle < 0) angle += 360;
        directionToWater = static_cast<int>(angle / 60);
      }

      HexVector position{ node.getHexPosition() };
      int direction{ 0 };
      while(true)
      {
        if(position.toCartesian().x < 0 
        || position.toCartesian().y < 0
        || position.toCartesian().x > sizeX
        || position.toCartesian().y > sizeY
        || getNode(position).getTerrainType() == TerrainType::water)
        { 
          break;
        }
        else if(neighboursTerrain(position, TerrainType::water))
        {
          getNode(position).switchTerrainType(TerrainType::river);
          break;
        }
        else
        {
          getNode(position).switchTerrainType(TerrainType::river);
        }

        direction = Random::getRandomInt(directionToWater - 1, directionToWater + 1);
        if(direction == -1) direction = 5;
        else if(direction == 6) direction = 0;

        position = position.getNeighbour(direction);
      }
    }
  }

  units.clear();
  units.emplace_back(5, 5,  //Debug riflemen 
                     "Riflemen", 
                     3, std::vector<int>{ 10, 1, 2, 3, 2, 2, 3 },
                     0);
  units.emplace_back(5, 6,  //Another debug riflemen
                     "Riflemen", 
                     3, std::vector<int>{ 10, 1, 2, 3, 2, 2, 3 },
                     0);
  units.emplace_back(7, 7,  //Debug enemy riflemen
                     "Riflemen", 
                     3, std::vector<int>{ 10, 1, 2, 3, 2, 2, 3 },
                     1);

  for(auto& unit : units)
  {
    unit.loadMoveCosts(sizeX, sizeY, nodes, units);
    unit.generateMCM(sizeX, sizeY, nodes);
  }
}
      
void Map::saveToFile(std::string filename)
{
  nlohmann::json mapData{  };

  //Map size
  mapData["sizeX"] = sizeX;
  mapData["sizeY"] = sizeY;

  //Node data
  std::vector<std::array<int, 2>> nodeData{  };
  for(auto& node : nodes)
  {
    nodeData.push_back(std::array<int, 2>{ static_cast<int>(node.getTerrainType()), static_cast<int>(node.getClimateZone()) });
  }
  mapData["nodes"] = nodeData;

  //Unit data
  mapData["unitCount"] = units.size();
  for(std::size_t iii{ 0 }; iii < units.size(); ++iii)
  {
    mapData["units"][iii]["x"] = units.at(iii).getHexPosition().toCartesian().x;
    mapData["units"][iii]["y"] = units.at(iii).getHexPosition().toCartesian().y;
    mapData["units"][iii]["name"] = units.at(iii).getName();
    mapData["units"][iii]["mp"] = units.at(iii).getMaxMovePoints();
    mapData["units"][iii]["mc"] = units.at(iii).getMoveCosts();
    mapData["units"][iii]["faction"] = units.at(iii).getFaction();
  }

  //Saving to file
  std::fstream saveFile{  };
  saveFile.open("saves/" + filename, std::ios::out | std::ios::trunc);

  if(saveFile.is_open())
  {
    saveFile << std::setw(4) << mapData << std::endl;
    saveFile.close();
  }
}

void Map::loadFromFile(std::string filename)
{
  nodes.clear();
  units.clear();

  nlohmann::json savedMap{  };
  std::fstream saveFile{  };
  saveFile.open(filename, std::ios::in);

  saveFile >> savedMap;

  sizeX = savedMap["sizeX"];
  sizeY = savedMap["sizeY"];

  for(int y{ 0 }; y < sizeY; ++y)
  {
    for(int x{ 0 }; x < sizeX; ++x)
    {
      nodes.emplace_back(x, y);
      nodes.at(static_cast<std::size_t>(y * sizeX + x))
        .switchTerrainType(static_cast<TerrainType>(
          savedMap["nodes"][static_cast<std::size_t>(y * sizeX + x)][0]));
      nodes.at(static_cast<std::size_t>(y * sizeX + x))
        .switchClimateZone(static_cast<ClimateZone>(
          savedMap["nodes"][static_cast<std::size_t>(y * sizeX + x)][1]));
    }
  }

  for(std::size_t iii{ 0 }; iii < savedMap["unitCount"]; ++iii)
  {
    units.emplace_back(savedMap["units"][iii]["x"], savedMap["units"][iii]["y"],
                       savedMap["units"][iii]["name"],
                       savedMap["units"][iii]["mp"], savedMap["units"][iii]["mc"],
                       savedMap["units"][iii]["faction"]);
  }
}

MapNode& Map::getNode(int q, int r, int s)
{
  return getNode(HexVector(q, r, s)); 
}
      
MapNode& Map::getNode(HexVector position)
{
  if(position.isInBoundaries(sizeX, sizeY))
  {
    return nodes.at(position.toID(sizeX));
  }

  return nothingness;
}

MapNode& Map::getNode(sf::Vector2i position)
{
  return getNode(HexVector(position));
}
      
MapNode& Map::getNeighbour(int mainQ, int mainR, int mainS, int directionID)
{
  return getNeighbour(HexVector(mainQ, mainR, mainS), directionID);
}

MapNode& Map::getNeighbour(HexVector mainNodePosition, int directionID)
{
  return getNode(mainNodePosition.getNeighbour(directionID));
}

bool Map::neighboursTerrain(int q, int r, int s, TerrainType terrain)
{
  return neighboursTerrain(HexVector(q, r, s), terrain);
}

bool Map::neighboursTerrain(HexVector position, TerrainType terrain)
{
  for(int dir{ 0 }; dir <= 5; ++dir)
  {
    if(getNode(position.getNeighbour(dir)).getTerrainType() == terrain)
    {
      return true;
    }
  }

  return false;
}

bool Map::neighboursTerrain(int x, int y, TerrainType terrain)
{
  return neighboursTerrain(HexVector(x, y), terrain);
}

void Map::createLandmass(int q, int r, int s, int size)
{
  for( auto& node : nodes)
  {
    HexVector delta{ node.getHexPosition().q - q, 
                     node.getHexPosition().r - r, 
                     node.getHexPosition().s - s };

    if(abs(delta.q) <= size && abs(delta.r) <= size && abs(delta.s) <= size)
    {
      node.switchTerrainType(TerrainType::plains);
    }
  }
}

void Map::createLandmass(HexVector position, int size)
{
  createLandmass(position.q, position.r, position.s, size);
}

void Map::createLandmass(int x, int y, int size)
{
  createLandmass(HexVector(x, y), size);
}

std::string Map::getSelectedNodeName()
{
  for( auto& node : nodes )
  {
    if(node.isSelected)
    {
      switch(node.getTerrainType())
      {
        case TerrainType::water:
          return "Sea";
        break;

        case TerrainType::plains:
          switch(node.getClimateZone())
          {
            case ClimateZone::polar:
              return "Tundra";
            break;

            case ClimateZone::dry:
              return "Desert";
            break;

            case ClimateZone::temperate:
            case ClimateZone::tropical:
              return "Grassland";
            break;
          }
        break;

        case TerrainType::hills:
          switch(node.getClimateZone())
          {
            case ClimateZone::polar:
              return "Tundra hills";
            break;

            case ClimateZone::dry:
              return "Desert hills";
            break;
            
            case ClimateZone::temperate:
            case ClimateZone::tropical:
              return "Grassland hills";
            break;
          }
        break;

        case TerrainType::mountains:
          return "Mountains";
        break;

        case TerrainType::forest:
          switch(node.getClimateZone())
          {
            case ClimateZone::temperate:
              return "Forest";
            break;

            case ClimateZone::tropical:
              return "Rainforest";
            break;

            case ClimateZone::dry:
            case ClimateZone::polar:
            break;
          }
        break;

        case TerrainType::forestHills:
          switch(node.getClimateZone())
          {
            case ClimateZone::temperate:
              return "Forest hills";
            break;

            case ClimateZone::tropical:
              return "Rainforest hills";
            break;

            case ClimateZone::dry:
            case ClimateZone::polar:
            break;
          }
        break;

        case TerrainType::river:
          switch(node.getClimateZone())
          {
            case ClimateZone::polar:
              return "Tundra river";
            break;

            case ClimateZone::dry:
              return "Desert river";
            break;
            
            case ClimateZone::temperate:
            case ClimateZone::tropical:
              return "Grassland river";
            break;
          }
        break;

        case TerrainType::blank:
        break;
      }
    }
  }

  return "";
}

Unit& Map::getSelectedUnit()
{
  for( auto& unit : units )
  {
    if(unit.isSelected)
    {
      return unit;
    }
  }

  return nobody;
}
