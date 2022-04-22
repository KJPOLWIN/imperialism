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

  //creating map
  for(int y{ 0 }; y < sizeY; ++y)
  {
    for(int x{ 0 }; x < sizeX; ++x)
    {
      nodes.push_back(MapNode(x, y));
    }
  }

  //loading textures and sprites
  selectedNodeTexture.loadFromFile("texture/selectednode.png");
  grassNodeTexture.loadFromFile("texture/nodegrass.png");
  waterNodeTexture.loadFromFile("texture/nodewater.png");
  desertNodeTexture.loadFromFile("texture/nodedesert.png");
  tundraNodeTexture.loadFromFile("texture/nodetundra.png");
  mountainsNodeTexture.loadFromFile("texture/nodemountain.png");
  riflemenTexture.loadFromFile("texture/riflemen.png");

  selectedNode.setTexture(selectedNodeTexture);
  grassNode.setTexture(grassNodeTexture);
  waterNode.setTexture(waterNodeTexture);
  desertNode.setTexture(desertNodeTexture);
  tundraNode.setTexture(tundraNodeTexture);
  mountainsNode.setTexture(mountainsNodeTexture);
  riflemenSprite.setTexture(riflemenTexture);
    
  units.push_back(Unit(1, 1, "Riflemen", 3));
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
  HexVector chosenHex{ selectedNodeCartesian.x, selectedNodeCartesian.y }; 

  if(selectedNodeCartesian.x >= 0 && selectedNodeCartesian.x < sizeX 
  && selectedNodeCartesian.y >= 0 && selectedNodeCartesian.y < sizeY)
  {
    getNode(chosenHex.q, chosenHex.r, chosenHex.s).select();

    for( auto& unit : units )
    {
      if(unit.getHexPosition() == chosenHex)
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

void Map::draw(sf::RenderWindow& targetWindow)
{
  for( auto& node : nodes )
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
    else if(node.getTerrainType() == TerrainType::mountains)
    {
      mountainsNode.setPosition(node.getPosition());
      targetWindow.draw(mountainsNode);
    }
  }

  //Drawing unselected nodes first, so full selected node's border will be visible
  for( auto& node : nodes )
  {
    if(!node.isSelected)
    {
      node.draw(targetWindow);
    }
  }
  
  for( auto& node : nodes )
  {
    if(node.isSelected)
    {
      node.draw(targetWindow);
    }
  }

  //Drawing units
  for( auto& unit : units )
  {
    riflemenSprite.setPosition(unit.getPosition());
    targetWindow.draw(riflemenSprite);
  
    if(unit.isSelected)
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
    HexVector landmassPosition{ landmassX, landmassY };
  
    createLandmass(landmassPosition.q, landmassPosition.r, landmassPosition.s, landmassSize);
  }

  //Smudging landmasses
  /*for(int y{ 0 }; y < sizeY; ++y)
  {
    for(int x{ 0 }; x < sizeX; ++x)
    {
      if(getNode(x, y).getTerrainType() != TerrainType::water
      && neighboursTerrain(x, y, TerrainType::water)
      && Random::testForProbability(0.5))
      {
        getNode(x, y).switchTerrainType(TerrainType::water);
      }
      else if(getNode(x, y).getTerrainType() == TerrainType::water
      && neighboursTerrain(x, y, TerrainType::grassland)
      && Random::testForProbability(0.5))
      {
        getNode(x, y).switchTerrainType(TerrainType::grassland);
      }
    }
  }*/
  for( auto& node : nodes )
  {
    if(node.getTerrainType() != TerrainType::water
    && neighboursTerrain(node.getHexPosition().q, 
                         node.getHexPosition().r, 
                         node.getHexPosition().s, 
                         TerrainType::water)
    && Random::testForProbability(0.5))
    {
      node.switchTerrainType(TerrainType::water);
    }
    else if(node.getTerrainType() == TerrainType::water
    && neighboursTerrain(node.getHexPosition().q, 
                         node.getHexPosition().r, 
                         node.getHexPosition().s, 
                         TerrainType::grassland)
    && Random::testForProbability(0.5))
    {
      node.switchTerrainType(TerrainType::grassland);
    }
  }

  //Biome generation
  /*for(int y{ 0 }; y < sizeY; ++y)
  {
    for(int x{ 0 }; x < sizeX; ++x)
    {
      if(getNode(x, y).getTerrainType() != TerrainType::water)
      {
        //Tundra: 1st and 7th of 7 climate zones
        if(y < sizeY / 7 || y > 6 * sizeY / 7)
        {
          getNode(x, y).switchTerrainType(TerrainType::tundra);
        }
        //Grasslands: 2nd, 4th and 6th of 7 climate zones
        //Desert: 3rd and 5th of 7 climate zones
        else if((y >= 2 * sizeY / 7 && y <= 3 * sizeY / 7)
             || (y >= 4 * sizeY / 7 && y <= 5 * sizeY / 7))
        {
          getNode(x, y).switchTerrainType(TerrainType::desert);
        }
      }
    }
  }*/
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

  //Mountains generator
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
      if(getNode(rangeHexPosition.q, rangeHexPosition.r, rangeHexPosition.s).getTerrainType()
          != TerrainType::blank)
      {
        getNode(rangeHexPosition.q, rangeHexPosition.r, rangeHexPosition.s).switchTerrainType(TerrainType::mountains);
        rangeHexPosition.q += Random::getRandomInt(-1, 1);
        rangeHexPosition.r += Random::getRandomInt(-1, 1);
        rangeHexPosition.s += Random::getRandomInt(-1, 1);
      }
    }
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

bool Map::neighboursTerrain(int q, int r, int s, TerrainType terrain)
{
  return (getNode(q,     r - 1, s + 1).getTerrainType() == terrain    //NW
       || getNode(q + 1, r - 1, s    ).getTerrainType() == terrain    //NE
       || getNode(q + 1, r,     s - 1).getTerrainType() == terrain    //E
       || getNode(q,     r + 1, s - 1).getTerrainType() == terrain    //SE
       || getNode(q - 1, r + 1, s    ).getTerrainType() == terrain    //SW
       || getNode(q - 1, r,     s + 1).getTerrainType() == terrain);  //W


  /*if(x - 1 >= 0 && getNode(x - 1, y).getTerrainType() == terrain)
  {
    return true;
  }
  else if(x + 1 < sizeX && getNode(x + 1, y).getTerrainType() == terrain)
  {
    return true;
  }

  if(y % 2 == 0)
  {
    if(x - 1 >= 0 && y - 1 >= 0 && getNode(x - 1, y - 1).getTerrainType() == terrain)
    {
      return true;
    }
    else if(y - 1 >= 0 && getNode(x, y - 1).getTerrainType() == terrain)
    {
      return true;
    }
    else if(x - 1 >= 0 && y + 1 < sizeY && getNode(x - 1, y + 1).getTerrainType() == terrain)
    {
      return true;
    }
    else if(y + 1 < sizeY && getNode(x, y + 1).getTerrainType() == terrain)
    {
      return true;
    }
  }
  else
  {
    if(y - 1 >= 0 && getNode(x, y - 1).getTerrainType() == terrain)
    {
      return true;
    }
    else if(x + 1 < sizeX && y - 1 >= 0 && getNode(x + 1, y - 1).getTerrainType() == terrain)
    {
      return true;
    }
    else if(y + 1 < sizeY && getNode(x, y + 1).getTerrainType() == terrain)
    {
      return true;
    }
    else if(x + 1 < sizeX && y + 1 < sizeY && getNode(x + 1, y + 1).getTerrainType() == terrain)
    {
      return true;
    }
  }

  return false;*/
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

  /*if(size > 0)
  {
    if(x >= 0 && x < sizeX && y >= 0 && y < sizeY)
    {
      getNode(x, y).switchTerrainType(TerrainType::grassland);
      //std::cout << "Creating land on " << x << ", " << y << "\n"; 
    }
    
    createLandmass(x - 1, y, size - 1); //W
    createLandmass(x + 1, y, size - 1); //E
    if(y % 2 == 0)
    {
      createLandmass(x - 1, y - 1, size - 1); //NW
      createLandmass(x, y - 1, size - 1);     //NE
      createLandmass(x - 1, y + 1, size - 1); //SW
      createLandmass(x, y + 1, size - 1);     //SE
    }
    else
    {
      createLandmass(x, y - 1, size - 1);     //NW
      createLandmass(x + 1, y - 1, size - 1); //NE
      createLandmass(x, y + 1, size - 1);     //SW
      createLandmass(x + 1, y + 1, size - 1); //SE
    }
  }*/
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

        case TerrainType::mountains:
          return "Mountains";
        break;
      }
    }
  }

  return "";
}

std::string Map::getSelectedUnitName()
{
  for( auto& unit : units )
  {
    if(unit.isSelected)
    {
      return unit.getName();
    }
  }

  return "";
}
