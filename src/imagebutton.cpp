#include "imagebutton.h"
#include <SFML/Graphics.hpp>

ImageButton::ImageButton(sf::Sprite* sprite, sf::Vector2f position, sf::Vector2f size)
  : sprite{ sprite },
    position{ position },
    size{ size }
{

}

bool ImageButton::isClicked(sf::Vector2i clickPosition)
{
  return (position.x <= clickPosition.x) && (position.x + size.x >= clickPosition.x) 
      && (position.y <= clickPosition.y) && (position.y + size.y >= clickPosition.y);
}

void ImageButton::draw(sf::RenderWindow& targetWindow)
{
  sprite->setPosition(position);
  targetWindow.draw(*sprite);
}
      
void ImageButton::setPosition(sf::Vector2f newPosition)
{
  position = newPosition;
}

void ImageButton::setPosition(double x, double y)
{
  position = sf::Vector2f(x, y);
}

sf::Vector2f ImageButton::getPosition()
{
  return position;
}

sf::Vector2f ImageButton::getSize()
{
  return size;
}
