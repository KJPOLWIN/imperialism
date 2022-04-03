#include "map.h"
#include "mapnode.h"
#include "random.h"
#include <SFML/Graphics.hpp>
#include <vector>

  #include <iostream>

Map::Map(int sizeX, int sizeY)
  : sizeX{ sizeX },
    sizeY{ sizeY }
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
  grassNodeTexture.loadFromFile("texture/nodegrass.png");
  waterNodeTexture.loadFromFile("texture/nodewater.png");
  desertNodeTexture.loadFromFile("texture/nodedesert.png");
  tundraNodeTexture.loadFromFile("texture/nodetundra.png");

  grassNode.setTexture(grassNodeTexture);
  waterNode.setTexture(waterNodeTexture);
  desertNode.setTexture(desertNodeTexture);
  tundraNode.setTexture(tundraNodeTexture);

}

void Map::selectNodes(sf::Vector2f clickPosition, sf::Vector2f viewOffset)
{
  int x{ static_cast<int>(clickPosition.x - viewOffset.x) / 88 };  //Node width in px
  int y{ 2 * static_cast<int>(clickPosition.y - viewOffset.y) / 151 }; //Node height in px + 50 px below

  for( auto& node : nodes )
  {
    node.disselect();
  }
  
  sf::Color area{ sf::Color::White }; 
  if(clickPosition.x >= 0 && clickPosition.y >= 0)
  {
    area = clickmap.getPixel(static_cast<unsigned int>(clickPosition.x) % 88, 
                             static_cast<unsigned int>(clickPosition.y) % 151);
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


  if(x >= 0 && x < sizeX && y >= 0 && y < sizeY)
  {
    getNode(x, y).select();
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

  //Smearing landmasses
  for(int y{ 0 }; y < sizeY; ++y)
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
  }

  //Biome generation
  for(int y{ 0 }; y < sizeY; ++y)
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
  }
}

MapNode& Map::getNode(int x, int y)
{
  return nodes.at(static_cast<long unsigned int>(y * sizeX + x));
}

bool Map::neighboursTerrain(int x, int y, TerrainType terrain)
{
  if(x - 1 >= 0 && getNode(x - 1, y).getTerrainType() == terrain)
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

  return false;
}

void Map::createLandmass(int x, int y, int size)
{
  if(size > 0)
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
  }
}
