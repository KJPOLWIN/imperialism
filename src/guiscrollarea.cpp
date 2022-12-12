#include "guiscrollarea.h"
#include "guielement.h"
#include <SFML/Graphics.hpp>

GUIScrollArea::GUIScrollArea(sf::Vector2f position, sf::Vector2f size, GUIElement* masterElement, double scrollingSpeed)
  : GUIElement(position, size, masterElement),
    scrollbar{ sf::Vector2f(10.0f, size.y) },
    scrollbarBackground{ sf::Vector2f(14.0f, size.y + 4.0f) },
    drawingHeight{ size.y },
    areaHeight{ size.y },
    maxScrollLevel{ static_cast<int>(areaHeight / scrollingSpeed) },
    scrollingSpeed{ scrollingSpeed }
{
  scrollbar.setPosition(position.x + size.x - 20.0f, position.y);
  scrollbarBackground.setPosition(position.x + size.x - 22.0f, 
                                  position.y - 2.0f);
  scrollbarBackground.setFillColor(sf::Color(17, 17, 17));
}

GUIScrollArea::GUIScrollArea(sf::Vector2f size, GUIElement* masterElement, double scrollingSpeed)
  : GUIElement(size, masterElement),
    scrollbar{ sf::Vector2f(10.0f, size.y) },
    scrollbarBackground{ sf::Vector2f(14.0f, size.y + 4.0f) },
    drawingHeight{ size.y },
    areaHeight{ size.y },
    maxScrollLevel{ static_cast<int>(areaHeight / scrollingSpeed) },
    scrollingSpeed{ scrollingSpeed }
{
  scrollbar.setPosition(size.x - 20.0f, 0.0f);
  scrollbarBackground.setPosition(size.x - 22.0f, 
                                  -2.0f);
  scrollbarBackground.setFillColor(sf::Color(17, 17, 17));
}

void GUIScrollArea::setPosition(sf::Vector2f position)
{
  sf::Vector2f delta{ field.getPosition() - position }; 

  field.setPosition(position);

  scrollbar.setPosition(position.x + field.getSize().x - 20.0f, 
                        position.y);
  scrollbarBackground.setPosition(position.x + field.getSize().x - 22.0f, 
                                  position.y - 2.0f);

  for(auto& slave : slaveElements)
  {
    slave->setPosition(slave->getPosition() + delta);
  }
}

void GUIScrollArea::centerHorizontally()
{
  setPosition(sf::Vector2f(
                masterElement->getPosition().x
                + masterElement->getSize().x / 2
                - GUIScrollArea::field.getSize().x / 2, 
                GUIElement::field.getPosition().y));
}

void GUIScrollArea::centerVertically()
{
  setPosition(sf::Vector2f(
                GUIElement::field.getPosition().x,
                masterElement->getPosition().y
                + masterElement->getSize().y / 2
                - GUIElement::field.getSize().y / 2));
}

void GUIScrollArea::centerInMaster()
{
  centerHorizontally();
  centerVertically();
}

void GUIScrollArea::positionAtTop(int pixels)
{
  setPosition(sf::Vector2f(field.getPosition().x,
                    masterElement->getPosition().y + pixels));
}

void GUIScrollArea::positionAtRight(int pixels)
{
  setPosition(sf::Vector2f(masterElement->getPosition().x
                    + masterElement->getSize().x 
                    - pixels - this->field.getSize().x, 
                    field.getPosition().y));
}

void GUIScrollArea::positionAtBottom(int pixels)
{
  setPosition(sf::Vector2f(field.getPosition().x,
                    masterElement->getPosition().y
                    + masterElement->getSize().y 
                    - pixels - this->field.getSize().y));
}

void GUIScrollArea::positionAtLeft(int pixels)
{
  setPosition(sf::Vector2f(masterElement->getPosition().x + pixels, 
                    field.getPosition().y));
}
      
void GUIScrollArea::positionUpTo(GUIElement* element, int pixels)
{
  setPosition(sf::Vector2f(field.getPosition().x,
                    element->getPosition().y
                    - pixels - this->field.getSize().y));
}

void GUIScrollArea::positionRightTo(GUIElement* element, int pixels)
{
  setPosition(sf::Vector2f(element->getPosition().x
                    + element->getSize().x 
                    + pixels, 
                    field.getPosition().y));
}

void GUIScrollArea::positionDownTo(GUIElement* element, int pixels)
{
  setPosition(sf::Vector2f(field.getPosition().x,
                    element->getPosition().y
                    + element->getSize().y 
                    + pixels));
}

void GUIScrollArea::positionLeftTo(GUIElement* element, int pixels)
{
  setPosition(sf::Vector2f(element->getPosition().x
                    - pixels - this->field.getSize().x, 
                    field.getPosition().y));
}

void GUIScrollArea::scroll(int direction)
{
  if(scrollLevel - direction >= 0 && scrollLevel - direction < maxScrollLevel)
  { 
    scrollLevel -= direction;
    double oldPos{ scrollbar.getPosition().y };

    scrollbar.setPosition(sf::Vector2f(scrollbar.getPosition().x,
                                       getPosition().y 
                                       + static_cast<double>(
                                           scrollLevel) / (maxScrollLevel - 1)
                                       * (drawingHeight 
                                       - scrollbar.getSize().y)));
    
    for(auto& slave : slaveElements)
    {
      slave->setPosition(
        sf::Vector2f(slave->getPosition().x, 
                     slave->getPosition().y 
                     - (scrollbar.getPosition().y - oldPos) 
                       * areaHeight / drawingHeight));
    }
  }
}

void GUIScrollArea::holdInput(sf::Vector2i clickPosition)
{
  if(field.getGlobalBounds().contains(clickPosition.x, 
                                      clickPosition.y)
  && activatedForMove)
  {
    double oldPos{ scrollbar.getPosition().y };

    scrollbar.setPosition(scrollbar.getPosition().x, 
                          clickPosition.y - mousePosDelta);

    if(scrollbar.getPosition().y > field.getPosition().y 
                                 + drawingHeight 
                                 - scrollbar.getSize().y)
    {
      scrollbar.setPosition(scrollbar.getPosition().x, 
                            field.getPosition().y 
                            + drawingHeight 
                            - scrollbar.getSize().y);
    }
    else if(scrollbar.getPosition().y < field.getPosition().y)
    {
      scrollbar.setPosition(scrollbar.getPosition().x,
                            field.getPosition().y);
    }
    
    for(auto& slave : slaveElements)
    {
      slave->setPosition(
        sf::Vector2f(slave->getPosition().x, 
                     slave->getPosition().y 
                     - (scrollbar.getPosition().y - oldPos) 
                       * areaHeight / drawingHeight));
    }

    scrollLevel = static_cast<int>(
                    (scrollbar.getPosition().y 
                     - field.getPosition().y) 
                    / (drawingHeight - scrollbar.getSize().y) 
                    * maxScrollLevel);
  }
}

void GUIScrollArea::releaseInput()
{
  activatedForMove = false;
}

void GUIScrollArea::clickInput(sf::Vector2i clickPosition)
{
  if(scrollbar.getGlobalBounds().contains(clickPosition.x, clickPosition.y))
  {
    activatedForMove = true;

    mousePosDelta = clickPosition.y - scrollbar.getPosition().y;
  }
  else
  {
    for(auto& slave : slaveElements)
    {
      slave->clickInput(clickPosition);
    }
  }
}

void GUIScrollArea::draw(sf::RenderWindow& window)
{
  //std::cout << slaveElements.size() << "\n";
  for(auto& slave : slaveElements)
  {
    //std::cout << "it works 1\n";
    if(slave->getPosition().y + slave->getSize().y >= field.getPosition().y 
    && slave->getPosition().y < field.getPosition().y + drawingHeight)
    {
      slave->draw(window);
      //std::cout << "it works 2\n";
    }
  }

  window.draw(scrollbarBackground);
  window.draw(scrollbar);
}
