#include "map.h"
#include "mapnode.h"
#include "random.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

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
  riverNodeTexture.loadFromFile("texture/noderiver.png");
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
  riverNode.setTexture(riverNodeTexture);
  riflemenSprite.setTexture(riflemenTexture);
    
  units.push_back(Unit(1, 1, "Riflemen", 3));
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
      HexVector unitPos{ unit.getHexPosition() };
      int unitMP{ unit.getMovePoints() };
      if(position.q >= unitPos.q - unitMP && position.q <= unitPos.q + unitMP
      && position.r >= unitPos.r - unitMP && position.r <= unitPos.r + unitMP
      && position.s >= unitPos.s - unitMP && position.s <= unitPos.s + unitMP)
      {
        unit.setPosition(position);
      }
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

void Map::switchNodeTerrain()
{
  for( auto& node : nodes )
  {
    if(node.isSelected)
    {
      node.switchTerrainType();
      break;
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
      if(node.getTerrainType() == TerrainType::grassland)
      {
        //Check how it should be done and change this
        grassNode.setPosition(node.getPosition());
        targetWindow.draw(grassNode);
      }
      else if(node.getTerrainType() == TerrainType::water)
      { 
        waterNode.setPosition(node.getPosition());
        targetWindow.draw(waterNode);
      }
      else if(node.getTerrainType() == TerrainType::desert)
      {
        desertNode.setPosition(node.getPosition());
        targetWindow.draw(desertNode);
      } 
      else if(node.getTerrainType() == TerrainType::tundra)
      {
        tundraNode.setPosition(node.getPosition());
        targetWindow.draw(tundraNode);
      }
      else if(node.getTerrainType() == TerrainType::grassHills)
      {
        grassHillsNode.setPosition(node.getPosition());
        targetWindow.draw(grassHillsNode);
      }
      else if(node.getTerrainType() == TerrainType::desertHills)
      {
        desertHillsNode.setPosition(node.getPosition());
        targetWindow.draw(desertHillsNode);
      }
      else if(node.getTerrainType() == TerrainType::tundraHills)
      {
        tundraHillsNode.setPosition(node.getPosition());
        targetWindow.draw(tundraHillsNode);
      }
      else if(node.getTerrainType() == TerrainType::forest)
      {
        forestNode.setPosition(node.getPosition());
        targetWindow.draw(forestNode);
      }
      else if(node.getTerrainType() == TerrainType::forestHills)
      {
        forestHillsNode.setPosition(node.getPosition());
        targetWindow.draw(forestHillsNode);
      }
      else if(node.getTerrainType() == TerrainType::jungle)
      {
        jungleNode.setPosition(node.getPosition());
        targetWindow.draw(jungleNode);
      }
      else if(node.getTerrainType() == TerrainType::jungleHills)
      {
        jungleHillsNode.setPosition(node.getPosition());
        targetWindow.draw(jungleHillsNode);
      }
      else if(node.getTerrainType() == TerrainType::mountains)
      {
        mountainsNode.setPosition(node.getPosition());
        targetWindow.draw(mountainsNode);
      }
      else if(node.getTerrainType() == TerrainType::river)
      {
        riverNode.setPosition(node.getPosition());
        targetWindow.draw(riverNode);
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
    riflemenSprite.setPosition(unit.getPosition());
    targetWindow.draw(riflemenSprite);
  
    if(unit.isSelected
    && unit.getPosition().x > viewOffset.x - 80 
    && unit.getPosition().y > viewOffset.y - 101
    && unit.getPosition().x < viewOffset.x + 1920 * zoom 
    && unit.getPosition().y < viewOffset.y + 1080 * zoom)
    {
      for( auto& node : nodes )
      {
        HexVector nodePos{ node.getHexPosition() };
        HexVector unitPos{ unit.getHexPosition() };
        int unitMP{ unit.getMovePoints() };
        if(nodePos.q >= unitPos.q - unitMP && nodePos.q <= unitPos.q + unitMP
        && nodePos.r >= unitPos.r - unitMP && nodePos.r <= unitPos.r + unitMP
        && nodePos.s >= unitPos.s - unitMP && nodePos.s <= unitPos.s + unitMP)
        {
          selectedNode.setPosition(node.getPosition());
          targetWindow.draw(selectedNode);
        }
      } 
    }
  }
}
 
void Map::regenerate(int sizeX, int sizeY, int landmassCountP, int landmassMaxSize)
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
    if(node.getTerrainType() != TerrainType::water
    && neighboursTerrain(node.getHexPosition(), 
                         TerrainType::water)
    && Random::testForProbability(0.5))
    {
      node.switchTerrainType(TerrainType::water);
    }
    else if(node.getTerrainType() == TerrainType::water
    && neighboursTerrain(node.getHexPosition(), 
                         TerrainType::grassland)
    && Random::testForProbability(0.5))
    {
      node.switchTerrainType(TerrainType::grassland);
    }
  }

  //Biome generation
  for( auto& node : nodes )
  {
    if(node.getTerrainType() != TerrainType::water)
    {
      int y{ node.getHexPosition().toCartesian().y };
      //Tundra: 1st, 7th
      if(y < sizeY / 7 || y > 6 * sizeY / 7)
      { 
        node.switchTerrainType(TerrainType::tundra);
      }
      //Grasslands: 2nd, 4th, 6th
      //Desert: 3rd, 5th
      if((y >= 2 * sizeY / 7 && y <= 3 * sizeY / 7)
      || (y >= 4 * sizeY / 7 && y <= 5 * sizeY / 7))
      {
        node.switchTerrainType(TerrainType::desert);
      }
    }
  }

  //Mountains generation
  const int mountainRangeLenght{ 5 };
  int mountainRangeCountP{ 1 };
  int mountainRangeCount{ static_cast<int>(mountainRangeCountP * nodes.size() / 100) };

  int rangeX{ 0 };
  int rangeY{ 0 };

  for(int iii{ 0 }; iii < mountainRangeCount; ++iii)
  {
    rangeX = Random::getRandomInt(0, sizeX - 1);
    rangeY = Random::getRandomInt(0, sizeY - 1);
    HexVector rangeHexPosition{ rangeX, rangeY };
  
    for(int jjj{ 0 }; jjj < mountainRangeLenght; ++jjj)
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
    && Random::testForProbability(0.5))
    {
      if(node.getTerrainType() == TerrainType::grassland)
      {
        node.switchTerrainType(TerrainType::grassHills);
      }
      else if(node.getTerrainType() == TerrainType::desert)
      {
        node.switchTerrainType(TerrainType::desertHills);
      }
      else if(node.getTerrainType() == TerrainType::tundra)
      {
        node.switchTerrainType(TerrainType::tundraHills);
      }
    }
  }
  
  for(auto& node : nodes)
  {
    if((node.getTerrainType() == TerrainType::grassland
     || node.getTerrainType() == TerrainType::desert
     || node.getTerrainType() == TerrainType::tundra)
    && (neighboursTerrain(node.getHexPosition(), TerrainType::grassHills)
     || neighboursTerrain(node.getHexPosition(), TerrainType::tundraHills)
     || neighboursTerrain(node.getHexPosition(), TerrainType::desertHills))
    && Random::testForProbability(0.5))
    {
      if(node.getTerrainType() == TerrainType::grassland)
      {
        node.switchTerrainType(TerrainType::grassHills);
      }
      else if(node.getTerrainType() == TerrainType::desert)
      {
        node.switchTerrainType(TerrainType::desertHills);
      }
      else if(node.getTerrainType() == TerrainType::tundra)
      {
        node.switchTerrainType(TerrainType::tundraHills);
      }
    }
  }

  //Forest generation
  for(auto& node : nodes)
  {
    if((node.getTerrainType() == TerrainType::grassland
     || node.getTerrainType() == TerrainType::grassHills)
    && Random::testForProbability(0.25))
    {
      int y{ node.getHexPosition().toCartesian().y };
      if((y >= 3 * sizeY / 7 && y <= 4 * sizeY / 7))
      {
        if(node.getTerrainType() == TerrainType::grassHills)
        {
          node.switchTerrainType(TerrainType::jungleHills);
        }
        else
        {
          node.switchTerrainType(TerrainType::jungle);
        }
      }
      else
      {
        if(node.getTerrainType() == TerrainType::grassHills)
        {
          node.switchTerrainType(TerrainType::forestHills);
        }
        else
        {
          node.switchTerrainType(TerrainType::forest);
        }
      }
    }
  }

  //River generation
  for(auto& node : nodes)
  {
    if(node.getTerrainType() != TerrainType::water && Random::testForProbability(0.01))
    {
      node.switchTerrainType(TerrainType::river);

      double shortestDistanceToWater{ 0 };
      for(auto& waterNode : nodes)
      {
        if(waterNode.getTerrainType() == TerrainType::water)
        {
          sf::Vector2f nPos{ node.getPosition() };
          sf::Vector2f wnPos{ waterNode.getPosition() }; 
          double distance{ sqrt(pow(nPos.x - wnPos.x, 2) + pow(nPos.y - wnPos.y, 2)) };
          if(distance < shortestDistanceToWater || shortestDistanceToWater < 0.1)
          {
            shortestDistanceToWater = distance;
          }
        }
      }

      HexVector position{ node.getHexPosition() };
      int direction{ Random::getRandomInt(0, 5) };
      while(true)
      {
        direction += Random::getRandomInt(-1, 1);
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

        if(getNode(position).getTerrainType() == TerrainType::water)
        {
          break;
        }
        else
        {
          getNode(position).switchTerrainType(TerrainType::river);
        }
      }
    }
  }
  /*int riverCount{ Random::getRandomInt(0, 5) };
  for(int iii{ 0 }; iii < riverCount; ++iii)
  {
    sf::Vector2i startCoords{ Random::getRandomInt(0, sizeX - 1),
                              Random::getRandomInt(0, sizeY - 1) };
    HexVector currentNodePos{ startCoords.x, startCoords.y }; 
  
    HexVector riverDirection{ Random::getRandomInt(-1, 1), 
                              Random::getRandomInt(-1, 1),
                              Random::getRandomInt(-1, 1) };

    int riverLenght{ Random::getRandomInt(3, 10) };


    for(int jjj{ 0 }; jjj < riverLenght; ++jjj)
    {
      if(getNode(currentNodePos.q, 
                 currentNodePos.r, 
                 currentNodePos.s).getTerrainType() == TerrainType::water)
      {
        break; 
      }

      getNode(currentNodePos.q, 
              currentNodePos.r, 
              currentNodePos.s).switchTerrainType(TerrainType::river);
    
      currentNodePos = HexVector(currentNodePos.q + riverDirection.q,
                                 currentNodePos.r + riverDirection.r,
                                 currentNodePos.s + riverDirection.s);
    
      riverDirection = HexVector{ Random::getRandomInt(-1, 1), 
                                  Random::getRandomInt(-1, 1),
                                  Random::getRandomInt(-1, 1) };
    }
  }*/
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
      node.switchTerrainType(TerrainType::grassland);
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
        case TerrainType::grassland:
          return "Grassland";
        break;

        case TerrainType::water:
          return "Water";
        break;

        case TerrainType::desert:
          return "Desert";
        break;

        case TerrainType::tundra:
          return "Tundra";
        break;

        case TerrainType::grassHills:
          return "Grassland hills";
        break;

        case TerrainType::desertHills:
          return "Desert hills";
        break;

        case TerrainType::tundraHills:
          return "Tundra hills";
        break;

        case TerrainType::forest:
          return "Forest";
        break;

        case TerrainType::forestHills:
          return "Forest hills";
        break;
        
        case TerrainType::jungle:
          return "Rainforest";
        break;
        
        case TerrainType::jungleHills:
          return "Rainforest hills";
        break;
        
        case TerrainType::mountains:
          return "Mountains";
        break;
      
        case TerrainType::river:
          return "River";
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
