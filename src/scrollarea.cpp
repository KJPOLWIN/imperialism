#include "scrollarea.h"
#include "textbutton.h"
#include "texttoggle.h"
#include <SFML/Graphics.hpp>
#include <cmath>

  #include <iostream>
      
ScrollArea::ScrollArea(sf::Vector2f position, sf::Vector2f size, 
                       double scrollingSpeed)
  : scrollbar{ sf::Vector2f(10.0f, size.y) },
    scrollbarBackground{ sf::Vector2f(14.0f, size.y + 4.0f) },
    areaStart{ sf::Vector2f(size.x, 100.0f) },
    areaEnd{ sf::Vector2f(size.x, 50.0f) },
    position{ position },
    drawingHeight{ size.y },
    areaHeight{ size.y },
    maxScrollLevel{ static_cast<int>(areaHeight / scrollingSpeed) },
    scrollingSpeed{ scrollingSpeed }
{
  scrollbar.setPosition(position.x + size.x - 20.0f, position.y);
  scrollbarBackground.setPosition(position.x + size.x - 22.0f, 
                                  position.y - 2.0f);
  scrollbarBackground.setFillColor(sf::Color(17, 17, 17));

  areaStart.setFillColor(sf::Color::Black);
  areaEnd.setFillColor(sf::Color::Black);
  areaStart.setPosition(sf::Vector2f(position.x, 
                                     position.y - areaStart.getSize().y));
  areaEnd.setPosition(sf::Vector2f(position.x, position.y + size.y));
}

void ScrollArea::addButton(sf::Font& font, std::string text,
                           sf::Vector2f position, unsigned int size)
{
  textButtons.emplace_back(font, text, position, size);
  
  if(textButtons.back().getPosition().y 
   + textButtons.back().getSize().y > areaHeight)
  {
    areaHeight = textButtons.back().getPosition().y 
               + textButtons.back().getSize().y;
    
    //Scrollbar should be (drawHeight/areaHeight) of drawHeight
    scrollbar.setSize(sf::Vector2f(scrollbar.getSize().x, 
                                   pow(drawingHeight, 2) / areaHeight));

    maxScrollLevel = ((areaHeight - drawingHeight) / scrollingSpeed) + 1;

    if(maxScrollLevel < 1) maxScrollLevel = 1;
  }
}

void ScrollArea::addToggle(sf::Font& font, std::string text,
                           sf::Vector2f position, unsigned int size)
{
  toggleButtons.emplace_back(font, text, position, size);
  
  if(toggleButtons.back().getPosition().y 
   + toggleButtons.back().getSize().y > areaHeight)
  {
    areaHeight = toggleButtons.back().getPosition().y 
               + toggleButtons.back().getSize().y;
    
    //Scrollbar should be (drawHeight/areaHeight) of drawHeight
    scrollbar.setSize(sf::Vector2f(scrollbar.getSize().x, 
                                   pow(drawingHeight, 2) / areaHeight));

    maxScrollLevel = ((areaHeight - drawingHeight) / scrollingSpeed) + 1;

    if(maxScrollLevel < 1) maxScrollLevel = 1;
  }
}
     
void ScrollArea::scroll(int direction)
{
  if(scrollLevel - direction >= 0 && scrollLevel - direction < maxScrollLevel)
  { 
    scrollLevel -= direction;
    double oldPos{ scrollbar.getPosition().y };

    scrollbar.setPosition(sf::Vector2f(scrollbar.getPosition().x,
                                       position.y 
                                       + static_cast<double>(
                                           scrollLevel) / (maxScrollLevel - 1)
                                       * (drawingHeight 
                                       - scrollbar.getSize().y)));
    
    for(auto& button : textButtons)
    {
      button.setPosition(
        sf::Vector2f(button.getPosition().x, 
                     button.getPosition().y 
                     - (scrollbar.getPosition().y - oldPos) 
                       * areaHeight / drawingHeight));
    }
    
    for(auto& button : toggleButtons)
    {
      button.setPosition(
        sf::Vector2f(button.getPosition().x, 
                     button.getPosition().y 
                     - (scrollbar.getPosition().y - oldPos) 
                       * areaHeight / drawingHeight));
    }
  }
}

void ScrollArea::holdInput(sf::Vector2i clickPosition)
{
  if(clickPosition.y > position.y 
  && clickPosition.y < position.y + drawingHeight 
  && activatedForMove)
  {
    double oldPos{ scrollbar.getPosition().y };

    scrollbar.setPosition(scrollbar.getPosition().x, 
                          clickPosition.y - mousePosDelta);

    if(scrollbar.getPosition().y > position.y 
                                 + drawingHeight 
                                 - scrollbar.getSize().y)
    {
      scrollbar.setPosition(scrollbar.getPosition().x, 
                            position.y 
                            + drawingHeight 
                            - scrollbar.getSize().y);
    }
    else if(scrollbar.getPosition().y < position.y)
    {
      scrollbar.setPosition(scrollbar.getPosition().x,
                            position.y);
    }

    for(auto& button : textButtons)
    {
      button.setPosition(
        sf::Vector2f(button.getPosition().x, 
                     button.getPosition().y 
                     - (scrollbar.getPosition().y - oldPos) 
                       * areaHeight/drawingHeight));
    }
    
    for(auto& button : toggleButtons)
    {
      button.setPosition(
        sf::Vector2f(button.getPosition().x, 
                     button.getPosition().y 
                     - (scrollbar.getPosition().y - oldPos) 
                       * areaHeight/drawingHeight));
    }

    scrollLevel = static_cast<int>(
                    (scrollbar.getPosition().y - position.y) 
                    / (drawingHeight - scrollbar.getSize().y) 
                    * maxScrollLevel);
  }
}

void ScrollArea::clickInput(sf::Vector2i clickPosition)
{
  if(scrollbar.getGlobalBounds().contains(clickPosition.x, clickPosition.y))
  {
    activatedForMove = true;

    mousePosDelta = clickPosition.y - scrollbar.getPosition().y;
  }
  else
  {
    /*for(auto& button : textButtons)
    {
      button.isClciked(clickPosition);
    }*/
    
    for(auto& button : toggleButtons)
    {
      button.clickInput(clickPosition);
    }
  }
}

void ScrollArea::releaseInput()
{
  activatedForMove = false;
}

void ScrollArea::draw(sf::RenderWindow& window)
{
  for(auto& button : textButtons)
  {
    if(button.getPosition().y + button.getSize().y >= position.y 
    && button.getPosition().y < position.y + drawingHeight)
    {
      button.draw(window);
    }
  }
  
  for(auto& button : toggleButtons)
  {
    if(button.getPosition().y + button.getSize().y >= position.y 
    && button.getPosition().y < position.y + drawingHeight)
    {
      button.draw(window);
    }
  }

  window.draw(areaStart);
  window.draw(areaEnd);
  
  window.draw(scrollbarBackground);
  window.draw(scrollbar);
}

std::vector<TextButton>& ScrollArea::getButtons()
{
  return textButtons;
}

std::vector<TextToggle>& ScrollArea::getToggles()
{
  return toggleButtons;
}
