#include "textinput.h"
#include <SFML/Graphics.hpp>
#include <string>

TextInput::TextInput(sf::Font& font, std::string string, unsigned int size, sf::Vector2f position)
  : text{ string, font, size }
{
  text.setPosition(position);
  background.setPosition(position);
  background.setSize(sf::Vector2f(text.getGlobalBounds().width, text.getGlobalBounds().height));
  background.setFillColor(sf::Color::Green);
}

bool TextInput::isClicked(sf::Vector2i clickPosition)
{
  return text.getGlobalBounds().contains(clickPosition.x, clickPosition.y);
}

void TextInput::updateText(char newString)
{
  if(active)
  {
    if(newString == static_cast<char>(8)) //Backspace character
    {
      if(text.getString().getSize() > 0)
      {
      
        text.setString(text.getString().substring(0, text.getString().getSize() - 1));
      }
    }
    else
    {
      text.setString(text.getString() + newString);
    }
    background.setSize(sf::Vector2f(text.getGlobalBounds().width, text.getGlobalBounds().height));
  }
}

std::string TextInput::getText()
{
  return text.getString();
}

void TextInput::draw(sf::RenderWindow& window)
{
  if(active)
  {
    window.draw(background);
  }

  window.draw(text);
}
