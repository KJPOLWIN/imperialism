#include "graphicalresource.h"
#include <SFML/Graphics.hpp>
#include <string>

GraphicalResource::GraphicalResource(std::string filename)
{
  texture.loadFromFile(filename);
  sprite.setTexture(texture);
}

void GraphicalResource::load(std::string filename)
{
  texture.loadFromFile(filename);
  sprite.setTexture(texture);
}

void GraphicalResource::setPosition(sf::Vector2f position)
{
  sprite.setPosition(position);
}
      
void GraphicalResource::setTextureRect(int top, int left, int width, int height)
{
  sprite.setTextureRect(sf::Rect(top, left, width, height));
}

void GraphicalResource::draw(sf::RenderWindow& window)
{
  window.draw(sprite);
}
