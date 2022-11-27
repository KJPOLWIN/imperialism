#include "guitextinput.h"
#include "guitextlabel.h"
#include "guielement.h"
#include <SFML/Graphics.hpp>
#include <string>
     
GUITextInput::GUITextInput(sf::Vector2f position, sf::Font& font, std::string text, unsigned int size, 
                           GUIElement* masterElement, int flags)
  : GUITextLabel(position, font, text, size, masterElement, flags)
{
  field.setOutlineThickness(0);
}
      
GUITextInput::GUITextInput(sf::Vector2f position, sf::Font& font, std::string text, 
                           unsigned int size, GUIElement* masterElement)
  : GUITextLabel(position, font, text, size, masterElement)
{
  field.setOutlineThickness(0);
}

GUITextInput::GUITextInput(sf::Font& font, std::string text, unsigned int size, 
                           GUIElement* masterElement, int flags)
  : GUITextLabel(font, text, size, masterElement, flags)
{
  field.setOutlineThickness(0);
}

GUITextInput::GUITextInput(sf::Font& font, std::string text, unsigned int size, 
                           GUIElement* masterElement)
  : GUITextLabel(font, text, size, masterElement)
{
  field.setOutlineThickness(0);
}
      
GUITextInput::GUITextInput(unsigned int size, GUIElement* masterElement, int flags)
  : GUITextLabel(size, masterElement, flags)
{
  field.setOutlineThickness(0);
}

GUITextInput::GUITextInput(unsigned int size, GUIElement* masterElement)
  : GUITextLabel(size, masterElement)
{
  field.setOutlineThickness(0);
}
      
void GUITextInput::setType(GUITextInputType type)
{
  this->type = type;
}

void GUITextInput::clickInput(sf::Vector2i clickPosition)
{
  if(isClicked(clickPosition))
  {
    active = true;
  }
  else
  {
    active = false;
  }
}

void GUITextInput::textEnteredInput(char newString)
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
      if(type == GUITextInputType::numeric
      && ((static_cast<int>(newString) >= 48  //0
        && static_cast<int>(newString) <= 57) //9
       || static_cast<int>(newString) == 46)) //.
      {
        text.setString(text.getString() + newString);
      }
      else if(type == GUITextInputType::text)
      {
        text.setString(text.getString() + newString);
      }
    }

    if(text.getString() == "")
    {
      field.setSize(sf::Vector2f(50,
                                 field.getSize().x));
    }
    else
    {
      field.setSize(sf::Vector2f(text.getGlobalBounds().width, 
                                 text.getGlobalBounds().height));
    }
  }
}
      
void GUITextInput::draw(sf::RenderWindow& window)
{
  if(active)
  {
    field.setFillColor(sf::Color::Green);
    GUIElement::draw(window);
  }
  else if(text.getString() == "")
  {
    field.setFillColor(sf::Color(68, 9, 4));
    GUIElement::draw(window);
  }

  GUITextLabel::draw(window);
}
