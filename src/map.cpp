#include "map.h"
#include "mapnode.h"
#include "random.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

  #include <iostream>

Map::Map(   sf::Font& font    )
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
    
  units.push_back(Unit(5, 5, "Riflemen", 
                       3, { 10, 1, 2, 3, 2, 2, 3 }
        ));

  debugMoveCostText = sf::Text("", font, 16);
  debugMoveCostText.setOutlineThickness(2);
  debugMoveCostText.setOutlineColor(sf::Color::Black);
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
  for( auto& unit : units )
  {
    if(unit.isSelected)
    {
      int unitMP{ unit.getMovePoints() };
      int nodeCost{ unit.getMoveCostMap().at(position.toCartesian().y * sizeX + position.toCartesian().x) };
      
      if(nodeCost != 0
      && nodeCost <= unitMP)
      {
        unit.calculatePath(position, sizeX, sizeY);
      }

      while(unit.getMoveQueueLenght() > 0)
      {
        unit.move(sizeX);
      }

      unit.generateMCM(sizeX, sizeY, nodes);
    }
  }
}

sf::Vector2i Map::getClickedNode(sf::Vector2f clickPosition, sf::Vector2f viewOffset, double zoom)
{
  int x{ static_cast<int>(clickPosition.x * zoom + viewOffset.x) / 88 };  //Node width in px
  int y{ 2 * (static_cast<int>(clickPosition.y * zoom + viewOffset.y) / 151) }; //Node height in px + 50 px below
  
  sf::Color area{ sf::Color::White }; 
  if(clickPosition.x >= 0 && clickPosition.y >= 0)
  {
    area = clickmap.getPixel(static_cast<unsigned int>(clickPosition.x * zoom + viewOffset.x) % 88, 
                             static_cast<unsigned int>(clickPosition.y * zoom + viewOffset.y) % 151);
  }
  
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
        break;
      }
    }
  }
}

void Map::draw(sf::RenderWindow& targetWindow, sf::Vector2f viewOffset, double zoom)
{
  for( auto& node : nodes )
  {
    if(node.getPosition().x > viewOffset.x - 80
    && node.getPosition().y > viewOffset.y - 101
    && node.getPosition().x < viewOffset.x + 1920 * zoom 
    && node.getPosition().y < viewOffset.y + 1080 * zoom)
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
      }
    }
  }

  //Drawing unselected nodes first, so full selected node's border will be visible
  for( auto& node : nodes )
  {
    if(!node.isSelected
    && node.getPosition().x > viewOffset.x - 80 
    && node.getPosition().y > viewOffset.y - 101
    && node.getPosition().x < viewOffset.x + 1920 * zoom 
    && node.getPosition().y < viewOffset.y + 1080 * zoom)
    {
      node.draw(targetWindow);
    }
  }
  
  for( auto& node : nodes )
  {
    if(node.isSelected
    && node.getPosition().x > viewOffset.x - 80 
    && node.getPosition().y > viewOffset.y - 101
    && node.getPosition().x < viewOffset.x + 1920 * zoom 
    && node.getPosition().y < viewOffset.y + 1080 * zoom)
    {
      node.draw(targetWindow);
    }
  }

  //Drawing units
  for( auto& unit : units )
  {
    if(unit.getPosition().x > viewOffset.x - 80 
    && unit.getPosition().y > viewOffset.y - 101
    && unit.getPosition().x < viewOffset.x + 1920 * zoom 
    && unit.getPosition().y < viewOffset.y + 1080 * zoom)
    {
      riflemenSprite.setPosition(unit.getPosition());
      targetWindow.draw(riflemenSprite);
    }

    //Drawing possible moves
    for( auto& node : nodes )
    {
      if(unit.isSelected
      && node.getPosition().x > viewOffset.x - 80 
      && node.getPosition().y > viewOffset.y - 101
      && node.getPosition().x < viewOffset.x + 1920 * zoom 
      && node.getPosition().y < viewOffset.y + 1080 * zoom)
      {
        HexVector nodePos{ node.getHexPosition() };
        int unitMP{ unit.getMovePoints() };
        int nodeCost{ unit.getMoveCostMap().at(nodePos.toCartesian().y * sizeX + nodePos.toCartesian().x) };
        
        if(nodeCost != 0
        && nodeCost <= unitMP)
        {
          selectedNode.setPosition(node.getPosition());
          targetWindow.draw(selectedNode);
        }
      } 
    }
  }

 for(auto& unit : units)
  {
    for(auto& node : nodes)  
    {
      if(node.getPosition().x > viewOffset.x - 80
      && node.getPosition().x < viewOffset.x + 1920 * zoom
      && node.getPosition().y > viewOffset.y - 101
      && node.getPosition().y < viewOffset.y + 1080 * zoom)
      {
        debugMoveCostText.setPosition(node.getPosition().x + 30, node.getPosition().y + 30);
        debugMoveCostText.setString(std::to_string(unit.getMoveCostMap().at(getNodeID(node.getHexPosition()))));
        targetWindow.draw(debugMoveCostText);
      }
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
      nodes.push_back(MapNode(x, y));
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
  int landmassCount{ static_cast<int>(landmassCountP * nodes.size() / 100) };

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
  int mountainRangeCount{ static_cast<int>(mountainRangeCountP * nodes.size() / 100) };

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

        switch(direction)
        {
          case 0: //NW
            position.r -= 1;
            position.s += 1;
          break;
          
          case 1: //NE
            position.q += 1;
            position.r -= 1;
          break;
          
          case 2: //E
            position.q += 1;
            position.s -= 1;
          break;
          
          case 3: //SE
            position.r += 1;
            position.s -= 1;
          break;
          
          case 4: //SW
            position.q -= 1;
            position.r += 1;
          break;
          
          case 5: //W
            position.q -= 1;
            position.s += 1;
          break;
        }
      }
    }
  }

  for(auto& unit : units)
  {
    unit.generateMCM(sizeX, sizeY, nodes);
  }
}

MapNode& Map::getNode(int q, int r, int s)
{
  HexVector pos{ q, r, s };
  if(pos.toCartesian().x >= 0 && pos.toCartesian().y >= 0 && pos.toCartesian().x < sizeX && pos.toCartesian().y < sizeY)
  {
    return nodes.at(static_cast<std::size_t>(pos.toCartesian().y * sizeX + pos.toCartesian().x));
  }

  return nothingness;
}
      
MapNode& Map::getNode(HexVector position)
{
  return getNode(position.q, position.r, position.s);
}

MapNode& Map::getNode(sf::Vector2i position)
{
  return getNode(HexVector(position));
}
      
int Map::getNodeID(HexVector position)
{
  for(int iii{  }; iii < nodes.size(); ++iii)
  {
    if(nodes.at(iii).getHexPosition() == position)
    {
      return iii;
    }
  } 
  return 0;
}

int Map::getNodeID(int q, int r, int s)
{
  return getNodeID(HexVector(q, r, s));
}
      
MapNode& Map::getNeighbour(int mainQ, int mainR, int mainS, int directionID)
{
  switch(directionID)
  {
    case 0: //NW
      return getNode(mainQ,
                     mainR - 1,
                     mainS + 1);
    break;

    case 1: //NE
      return getNode(mainQ + 1,
                     mainR - 1,
                     mainS    );
       
    break;

    case 2: //E
      return getNode(mainQ + 1,
                     mainR,
                     mainS - 1);
       
    break;

    case 3: //SE
      return getNode(mainQ,
                     mainR + 1,
                     mainS - 1);
       
    break;

    case 4: //SW
      return getNode(mainQ - 1,
                     mainR + 1,
                     mainS    );
       
    break;

    case 5: //W
      return getNode(mainQ - 1,
                     mainR,
                     mainS + 1);
       
    break;
  }

  return nothingness;
}

MapNode& Map::getNeighbour(HexVector mainNodePosition, int directionID)
{
  return getNeighbour(mainNodePosition.q, 
                      mainNodePosition.r, 
                      mainNodePosition.s, directionID);
}

bool Map::neighboursTerrain(int q, int r, int s, TerrainType terrain)
{
  return (getNode(q,     r - 1, s + 1).getTerrainType() == terrain    //NW
       || getNode(q + 1, r - 1, s    ).getTerrainType() == terrain    //NE
       || getNode(q + 1, r,     s - 1).getTerrainType() == terrain    //E
       || getNode(q,     r + 1, s - 1).getTerrainType() == terrain    //SE
       || getNode(q - 1, r + 1, s    ).getTerrainType() == terrain    //SW
       || getNode(q - 1, r,     s + 1).getTerrainType() == terrain);  //W
}

bool Map::neighboursTerrain(HexVector position, TerrainType terrain)
{
  return neighboursTerrain(position.q, position.r, position.s, terrain);
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
