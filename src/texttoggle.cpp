#include "texttoggle.h"
#include <SFML/Graphics.hpp>
#include <string>

  #include <iostream>

TextToggle::TextToggle(sf::Font& font, std::string text, 
                       sf::Vector2f position, unsigned int characterSize)
{
  TextToggle::text.setFont(font);
  TextToggle::text.setString(text);
  TextToggle::text.setPosition(position);
  TextToggle::text.setCharacterSize(characterSize);

  background.setPosition(position);
  background.setSize(sf::Vector2f(TextToggle::text.getGlobalBounds().width,
                                  TextToggle::text.getGlobalBounds().height));
  background.setFillColor(sf::Color::Black);
}

void TextToggle::clickInput(sf::Vector2i clickPosition)
{
  if(text.getGlobalBounds().contains(clickPosition.x, clickPosition.y))
  {
    toggle();
  }
}

void TextToggle::draw(sf::RenderWindow& targetWindow)
{
  targetWindow.draw(background);
  targetWindow.draw(text);
}
      
void TextToggle::toggle()
{
  if(text.getFillColor() == sf::Color::White)
  {
    background.setFillColor(sf::Color(30, 30, 30));
    text.setFillColor(sf::Color::Yellow);
  }
  else
  {
    background.setFillColor(sf::Color::Black);
    text.setFillColor(sf::Color::White);
  }
}
      
void TextToggle::setState(bool state)
{
  if(state)
  {
    background.setFillColor(sf::Color(30, 30, 30));
    text.setFillColor(sf::Color::Yellow);
  }
  else
  {
    background.setFillColor(sf::Color::Black);
    text.setFillColor(sf::Color::White);
  }
}
      
bool TextToggle::getState()
{
  return (text.getFillColor() == sf::Color::Yellow);
}
      
void TextToggle::setPosition(sf::Vector2f newPosition)
{
  text.setPosition(newPosition);
  background.setPosition(newPosition);
}

void TextToggle::setPosition(double x, double y)
{
  text.setPosition(x, y);
  background.setPosition(x, y);
}

sf::Vector2f TextToggle::getPosition()
{
  return text.getPosition();
}

sf::Vector2f TextToggle::getSize()
{
  return sf::Vector2f(text.getGlobalBounds().width, 
                      text.getGlobalBounds().height);
}

void TextToggle::setFont(sf::Font& font)
{
  text.setFont(font);
}
