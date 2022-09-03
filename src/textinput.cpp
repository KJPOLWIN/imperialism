#include "textinput.h"
#include <SFML/Graphics.hpp>
#include <string>

TextInput::TextInput(sf::Font& font, std::string string, unsigned int size, 
                     sf::Vector2f position, InputType type)
  : text{ string, font, size },
    type{ type }
{
  text.setPosition(position);
  background.setPosition(position);
  background.setSize(sf::Vector2f(text.getGlobalBounds().width, text.getGlobalBounds().height));
  background.setFillColor(sf::Color::Green);
}

bool TextInput::clickInput(sf::Vector2i clickPosition)
{
  if(background.getGlobalBounds().contains(clickPosition.x, clickPosition.y))
  {
    active = true;
    return true;
  }
  else 
  {
    active = false;
  }

  return false;
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
      if(type == InputType::numeric
      && ((static_cast<int>(newString) >= 48  //0
        && static_cast<int>(newString) <= 57) //9
       || static_cast<int>(newString) == 46)) //.
      {
        text.setString(text.getString() + newString);
      }
      else if(type == InputType::text)
      {
        text.setString(text.getString() + newString);
      }
    }
  }
}

std::string TextInput::getText()
{
  return text.getString();
}

void TextInput::setText(std::string text)
{
  TextInput::text.setString(text);
}

void TextInput::draw(sf::RenderWindow& window)
{
  if(text.getString() == "")
  {
    background.setSize(sf::Vector2f(50, 25));
    
    if(active)
    {
      background.setFillColor(sf::Color::Green);
    }
    else
    {
      background.setFillColor(sf::Color(68, 9, 4));
    }   
  }
  else
  {
    background.setSize(sf::Vector2f(text.getGlobalBounds().width, text.getGlobalBounds().height));
    background.setFillColor(sf::Color::Green);
  }

  if(active || text.getString() == "")
  {
    window.draw(background);
  }

  window.draw(text);
}

bool TextInput::isActive()
{
  return active;
}

void TextInput::deactivate()
{
  active = false;
}

void TextInput::activate()
{
  active = true;
}
