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

  grassNode.setTexture(grassNodeTexture);
  waterNode.setTexture(waterNodeTexture);
  desertNode.setTexture(desertNodeTexture);

}

void Map::selectNodes(sf::Vector2f clickPosition)
{
  int x{ static_cast<int>(clickPosition.x) / 88 };  //Node width in px
  int y{ 2 * static_cast<int>(clickPosition.y) / 151 }; //Node height in px + 50 px below

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
//void Map::switchNodeTerrain(bool& canClick)
{
  /*if(canClick && sf::Mouse::isButtonPressed(sf::Mouse::Left))
  {*/
    for( auto& node : nodes )
    {
      if(node.isSelected)
      {
        node.switchTerrainType();
        //canClick = false;
        break;
      }
    }
  //}
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

  //Terrain generation
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
}

MapNode& Map::getNode(int x, int y)
{
  return nodes.at(static_cast<long unsigned int>(y * sizeX + x));

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
      createLandmass(x, y - 1, size - 1); //NE
      createLandmass(x - 1, y + 1, size - 1); //SW
      createLandmass(x, y + 1, size - 1); //SE
    }
    else
    {
      createLandmass(x, y - 1, size - 1); //NW
      createLandmass(x + 1, y - 1, size - 1); //NE
      createLandmass(x, y + 1, size - 1); //SW
      createLandmass(x + 1, y + 1, size - 1); //SE
    }
  }
}
