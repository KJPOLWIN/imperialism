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
