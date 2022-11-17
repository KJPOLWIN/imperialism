#include "guielement.h"
#include <SFML/Graphics.hpp>
#include <vector>

GUIElement::GUIElement(sf::Vector2f position, sf::Vector2f size, GUIElement* masterElement)
  : field{ size },
    masterElement{ masterElement }
{
  field.setPosition(position);

  //style
  field.setFillColor(sf::Color::Black);
  field.setOutlineColor(sf::Color::White);
  field.setOutlineThickness(10);
}

GUIElement::GUIElement(sf::Vector2f size, GUIElement* masterElement)
  : field{ size },
    masterElement{ masterElement }
{
  field.setPosition(0, 0);

  //style
  field.setFillColor(sf::Color::Black);
  field.setOutlineColor(sf::Color::White);
  field.setOutlineThickness(10);
}

sf::Vector2f GUIElement::getPosition()
{
  return field.getPosition();
}
      
void GUIElement::setPosition(sf::Vector2f position)
{
  sf::Vector2f delta{ field.getPosition() - position }; 

  field.setPosition(position);

  for(auto& slave : slaveElements)
  {
    slave->setPosition(slave->getPosition() + delta);
  }
}

void GUIElement::centerHorizontally()
{
  field.setPosition(masterElement->field.getPosition().x
                    + masterElement->field.getSize().x
                    - field.getSize().x / 2, 
                    field.getPosition().y);
}

void GUIElement::centerVertically()
{
  field.setPosition(field.getPosition().x,
                    masterElement->field.getPosition().y
                    + masterElement->field.getSize().y
                    - field.getSize().y / 2);
}

void GUIElement::centerInMaster()
{
  centerHorizontally();
  centerVertically();
}

void GUIElement::positionAtTop(int pixels)
{
  field.setPosition(field.getPosition().x,
                    masterElement->field.getPosition().y + pixels);
}

void GUIElement::positionAtRight(int pixels)
{
  field.setPosition(masterElement->field.getPosition().x
                    + masterElement->field.getSize().x 
                    - pixels - this->field.getSize().x, 
                    field.getPosition().y);
}

void GUIElement::positionAtBottom(int pixels)
{
  field.setPosition(field.getPosition().x,
                    masterElement->field.getPosition().y
                    + masterElement->field.getSize().y 
                    - pixels - this->field.getSize().y);
}

void GUIElement::positionAtLeft(int pixels)
{
  field.setPosition(masterElement->field.getPosition().x + pixels, 
                    field.getPosition().y);
}
      
bool GUIElement::isClicked(sf::Vector2i clickPosition)
{

}

void GUIElement::update()
{

}

void GUIElement::draw(sf::RenderWindow& window)
{
  window.draw(field);
  
  for(auto& slave : slaveElements)
  {
    slave->draw(window);
  }
}

