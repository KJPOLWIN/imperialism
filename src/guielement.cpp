#include "guielement.h"
#include <SFML/Graphics.hpp>
#include <vector>

GUIElement::GUIElement(sf::Vector2f position, sf::Vector2f size, 
                       GUIElement* masterElement, int flags)
  : field{ size },
    masterElement{ masterElement },
    flags{ flags }
{
  field.setPosition(position);

  if(masterElement != nullptr)
  {
    masterElement->bindElement(this);
  }

  //style
  field.setFillColor(sf::Color::Black);
  field.setOutlineColor(sf::Color::White);
  field.setOutlineThickness(10);
}

GUIElement::GUIElement(sf::Vector2f position, sf::Vector2f size, 
                       GUIElement* masterElement)
  : field{ size },
    masterElement{ masterElement }
{
  field.setPosition(position);

  if(masterElement != nullptr)
  {
    masterElement->bindElement(this);
  }

  //style
  field.setFillColor(sf::Color::Black);
  field.setOutlineColor(sf::Color::White);
  field.setOutlineThickness(10);
}

GUIElement::GUIElement(sf::Vector2f size, GUIElement* masterElement, int flags)
  : field{ size },
    masterElement{ masterElement },
    flags{ flags }
{
  field.setPosition(0, 0);
  
  if(masterElement != nullptr)
  {
    masterElement->bindElement(this);
  }

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
  
  if(masterElement != nullptr)
  {
    masterElement->bindElement(this);
  }

  //style
  field.setFillColor(sf::Color::Black);
  field.setOutlineColor(sf::Color::White);
  field.setOutlineThickness(10);
}
      
void GUIElement::bindElement(GUIElement* slave)
{
  slaveElements.push_back(slave);
}
      
void GUIElement::setFunction(std::function<void()> func)
{
  function = func;
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
  setPosition(sf::Vector2f(
                masterElement->field.getPosition().x
                + masterElement->field.getSize().x / 2
                - GUIElement::field.getSize().x / 2, 
                GUIElement::field.getPosition().y));
}

void GUIElement::centerVertically()
{
  setPosition(sf::Vector2f(
                GUIElement::field.getPosition().x,
                masterElement->field.getPosition().y
                + masterElement->field.getSize().y / 2
                - GUIElement::field.getSize().y / 2));
}

void GUIElement::centerInMaster()
{
  centerHorizontally();
  centerVertically();
}

void GUIElement::positionAtTop(int pixels)
{
  setPosition(sf::Vector2f(field.getPosition().x,
                    masterElement->field.getPosition().y + pixels));
}

void GUIElement::positionAtRight(int pixels)
{
  setPosition(sf::Vector2f(masterElement->field.getPosition().x
                    + masterElement->field.getSize().x 
                    - pixels - this->field.getSize().x, 
                    field.getPosition().y));
}

void GUIElement::positionAtBottom(int pixels)
{
  setPosition(sf::Vector2f(field.getPosition().x,
                    masterElement->field.getPosition().y
                    + masterElement->field.getSize().y 
                    - pixels - this->field.getSize().y));
}

void GUIElement::positionAtLeft(int pixels)
{
  setPosition(sf::Vector2f(masterElement->field.getPosition().x + pixels, 
                    field.getPosition().y));
}
      
void GUIElement::positionUpTo(GUIElement* element, int pixels)
{
  setPosition(sf::Vector2f(field.getPosition().x,
                    element->field.getPosition().y
                    - pixels - this->field.getSize().y));
}

void GUIElement::positionRightTo(GUIElement* element, int pixels)
{
  setPosition(sf::Vector2f(element->field.getPosition().x
                    + element->field.getSize().x 
                    + pixels, 
                    field.getPosition().y));
}

void GUIElement::positionDownTo(GUIElement* element, int pixels)
{
  setPosition(sf::Vector2f(field.getPosition().x,
                    element->field.getPosition().y
                    + element->field.getSize().y 
                    + pixels));
}

void GUIElement::positionLeftTo(GUIElement* element, int pixels)
{
  setPosition(sf::Vector2f(element->field.getPosition().x
                    - pixels - this->field.getSize().x, 
                    field.getPosition().y));
}
      
bool GUIElement::isClicked(sf::Vector2i clickPosition)
{
  return (field.getGlobalBounds().contains(clickPosition.x, clickPosition.y));
}
      
void GUIElement::clickInput(sf::Vector2i clickPosition)
{
  if(testFlag(GUIFlag::clickable) && isClicked(clickPosition))
  {
    function();
  }

  for(auto& slave : slaveElements)
  {
    slave->clickInput(clickPosition);
  }
}

void GUIElement::update()
{

}

void GUIElement::draw(sf::RenderWindow& window)
{
  window.draw(field);
  
  for(auto& slave : slaveElements)
  {
    if(slave != nullptr)
    {
      slave->draw(window);
    }
  }
}

bool GUIElement::testFlag(int flag)
{
  /*if(flags >> flag == 0)
  {
    std::cout << "flag set\n";
  }
  else
  {
    std::cout << "flag not set\n";
  }*/
    
  return (flags >> flag == 0);
}

void GUIElement::setFlag(int flag)
{
  if(!testFlag(flag))
  {
    flags += flag;
  }
}
