#include "graphicalresource.h"
#include <SFML/Graphics.hpp>
#include <string>

GraphicalResource::GraphicalResource(std::string filename)
{
  texture.loadFromFile(filename);
  sprite.setTexture(texture);
}
      
GraphicalResource::GraphicalResource(const GraphicalResource& copy)
  : texture{ copy.texture },
    sprite{ copy.sprite }
{
  
}

void GraphicalResource::load(std::string filename)
{
  texture.loadFromFile(filename);
  sprite.setTexture(texture);
}
      
sf::Sprite* GraphicalResource::getSpritePointer()
{
  return &sprite;
}

void GraphicalResource::setPosition(sf::Vector2f position)
{
  sprite.setPosition(position);
}
      
void GraphicalResource::setTextureRect(int top, int left, int width, int height)
{
  sprite.setTextureRect(sf::Rect(top, left, width, height));
}
      
sf::Vector2f GraphicalResource::getSpriteSize()
{
  return sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
}

void GraphicalResource::draw(sf::RenderWindow& window)
{
  window.draw(sprite);
}
