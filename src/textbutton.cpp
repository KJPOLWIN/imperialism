#include "textbutton.h"
#include <SFML/Graphics.hpp>
#include <string>

TextButton::TextButton(sf::Font& font, std::string text, 
                       sf::Vector2f position, unsigned int size)
{
  TextButton::text.setFont(font);
  TextButton::text.setString(text);
  TextButton::text.setPosition(position);
  TextButton::text.setCharacterSize(size);
}

bool TextButton::isClicked(sf::Vector2i clickPosition)
{
  return text.getGlobalBounds().contains(clickPosition.x, clickPosition.y);
}

void TextButton::draw(sf::RenderWindow& targetWindow)
{
  targetWindow.draw(text);
}
      
void TextButton::setPosition(sf::Vector2f newPosition)
{
  text.setPosition(newPosition);
}

void TextButton::setPosition(double x, double y)
{
  text.setPosition(x, y);
}

sf::Vector2f TextButton::getPosition()
{
  return text.getPosition();
}

sf::Vector2f TextButton::getSize()
{
  return sf::Vector2f(text.getGlobalBounds().width, 
                      text.getGlobalBounds().height);
}
      
void TextButton::setText(std::string newText)
{
  text.setString(newText);
}
