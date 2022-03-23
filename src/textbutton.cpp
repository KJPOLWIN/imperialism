#include "textbutton.h"
#include <SFML/Graphics.hpp>
#include <string>

TextButton::TextButton(sf::Font& font, std::string text, sf::Vector2f position)
{
  TextButton::text.setFont(font);
  TextButton::text.setString(text);
  TextButton::text.setPosition(position);
}

void TextButton::draw(sf::RenderWindow& targetWindow)
{
  targetWindow.draw(text);
}
