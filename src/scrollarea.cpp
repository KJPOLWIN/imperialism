#include "scrollarea.h"
#include "textbutton.h"
#include "texttoggle.h"
#include "constant.h"
#include <SFML/Graphics.hpp>
#include <cmath>

  #include <iostream>
      
ScrollArea::ScrollArea(sf::Vector2f position, double height)
  : scrollbar{ sf::Vector2f(10.0f, height) },
    scrollbarBackground{ sf::Vector2f(14.0f, height + 4.0f) },
    position{ position },
    drawingHeight{ height },
    areaHeight{ height },
    maxScrollLevel{ static_cast<int>(areaHeight / 100) }
{
  scrollbar.setPosition(Constant::windowWidth - 20.0f, position.y);
  scrollbarBackground.setPosition(Constant::windowWidth - 22.0f, 
                                  position.y - 2.0f);
  scrollbarBackground.setFillColor(sf::Color(17, 17, 17));
}
     
void ScrollArea::scroll(int direction)
{
  if(scrollLevel - direction >= 0 && scrollLevel - direction < maxScrollLevel)
  { 
    for(auto& button : textButtons)
    {
      button->setPosition(
        sf::Vector2f(button->getPosition().x, 
                     button->getPosition().y + 100 * direction));
    }
    
    for(auto& button : toggleButtons)
    {
      button->setPosition(
        sf::Vector2f(button->getPosition().x, 
                     button->getPosition().y + 100 * direction));
    }
  
    scrollLevel -= direction;

    scrollbar.setPosition(sf::Vector2f(scrollbar.getPosition().x,
                                       position.y 
                                       + static_cast<double>(
                                           scrollLevel) / (maxScrollLevel - 1)
                                       * (drawingHeight 
                                       - scrollbar.getSize().y)));
  }
}

void ScrollArea::draw(sf::RenderWindow& window)
{
  window.draw(scrollbarBackground);
  window.draw(scrollbar);

  for(const auto& button : textButtons)
  {
    if(button->getPosition().y >= position.y && button->getPosition().y < position.y + drawingHeight)
    {
      button->draw(window);
    }
  }
  
  for(const auto& button : toggleButtons)
  {
    if(button->getPosition().y >= position.y && button->getPosition().y < position.y + drawingHeight)
    {
      button->draw(window);
    }
  }
}

void ScrollArea::bindButton(TextButton& button, sf::Font& font)
{
  textButtons.push_back(&button);
  textButtons.back()->setFont(font);

  if(textButtons.back()->getPosition().y 
   + textButtons.back()->getSize().y > areaHeight)
  {
    areaHeight = textButtons.back()->getPosition().y 
               + textButtons.back()->getSize().y;
    
    //Scrollbar should be drawHeight/areaHeight of drawHeight
    scrollbar.setSize(sf::Vector2f(scrollbar.getSize().x, 
                                   pow(drawingHeight, 2) / areaHeight));

    maxScrollLevel = ((areaHeight - drawingHeight) / 100) + 1 ;
    if(maxScrollLevel < 1) maxScrollLevel = 1;
  }
}

void ScrollArea::bindButton(TextToggle& button, sf::Font& font)
{
  toggleButtons.push_back(&button);
  toggleButtons.back()->setFont(font);
  
  if(toggleButtons.back()->getPosition().y 
   + toggleButtons.back()->getSize().y > areaHeight)
  {
    areaHeight = toggleButtons.back()->getPosition().y 
               + toggleButtons.back()->getSize().y;
    
    //Scrollbar should be drawHeight/areaHeight of drawHeight
    scrollbar.setSize(sf::Vector2f(scrollbar.getSize().x, 
                                   pow(drawingHeight, 2) / areaHeight));

    maxScrollLevel = ((areaHeight - drawingHeight) / 100) + 1;

    if(maxScrollLevel < 1) maxScrollLevel = 1;
  }
}
