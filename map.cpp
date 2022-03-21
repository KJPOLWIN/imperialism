#include "map.h"
#include "mapnode.h"
#include <SFML/Graphics.hpp>
#include <vector>

Map::Map(int sizeX, int sizeY)
  : sizeX{ sizeX },
    sizeY{ sizeY }
{
  clickmap.loadFromFile("clickmap.png");

  for(int y{ 0 }; y < sizeY; ++y)
  {
    for(int x{ 0 }; x < sizeX; ++x)
    {
      nodes.push_back(MapNode(x, y));
    }
  }
}

void Map::selectNodes(sf::Vector2i clickPosition)
{
  int x{ clickPosition.x / 88 };  //Node width in px
  int y{ 2 * (clickPosition.y / 151) }; //Node height in px + 50 px below

  for( auto& node : nodes )
  {
    node.disselect();
  }
  
  sf::Color area{ sf::Color::White }; 
  if(clickPosition.x >= 0 && clickPosition.y >= 0)
  {
    area = clickmap.getPixel(static_cast<unsigned int>(clickPosition.x % 88), 
                             static_cast<unsigned int>(clickPosition.y % 151));
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

void Map::draw(sf::RenderWindow& targetWindow)
{
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

MapNode& Map::getNode(int x, int y)
{
  return nodes.at(static_cast<long unsigned int>(y * sizeX + x));
}
