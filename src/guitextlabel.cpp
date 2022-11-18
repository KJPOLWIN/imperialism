#include "guitextlabel.h"
#include "guielement.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

GUITextLabel::GUITextLabel(sf::Vector2f position, sf::Font& font, std::string text, unsigned int size, GUIElement* masterElement)
  : GUIElement{ position, sf::Vector2f(0, 0), masterElement },
    text{ text, font, size }
{
  field.setSize(sf::Vector2f(this->text.getGlobalBounds().width, this->text.getGlobalBounds().height));
  setPosition(position);
}

GUITextLabel::GUITextLabel(sf::Font& font, std::string text, unsigned int size, GUIElement* masterElement)
  : GUIElement{ sf::Vector2f(0, 0), masterElement },
    text{ text, font, size }
{
  field.setSize(sf::Vector2f(this->text.getGlobalBounds().width, this->text.getGlobalBounds().height));
}
      
GUITextLabel::GUITextLabel(unsigned int size, GUIElement* masterElement)
  : GUIElement{ sf::Vector2f(0, 0), masterElement },
    text{ "", sf::Font(), size }
{

}
      
void GUITextLabel::setPosition(sf::Vector2f position)
{
  GUIElement::setPosition(position);
  text.setPosition(position);
}
      
void GUITextLabel::centerHorizontally()
{
  GUIElement::centerHorizontally();
  text.setPosition(GUIElement::field.getPosition());
}

void GUITextLabel::centerVertically()
{
  GUIElement::centerVertically();
  text.setPosition(GUIElement::field.getPosition());
}

void GUITextLabel::centerInMaster()
{
  GUITextLabel::centerHorizontally();
  GUITextLabel::centerVertically();
}

void GUITextLabel::positionAtTop(int pixels)
{
  GUIElement::positionAtTop(pixels);
  text.setPosition(GUIElement::field.getPosition());
}

void GUITextLabel::positionAtRight(int pixels)
{
  GUIElement::positionAtRight(pixels);
  text.setPosition(GUIElement::field.getPosition());
}

void GUITextLabel::positionAtBottom(int pixels)
{
  GUIElement::positionAtBottom(pixels);
  text.setPosition(GUIElement::field.getPosition());
}

void GUITextLabel::positionAtLeft(int pixels)
{
  GUIElement::positionAtLeft(pixels);
  text.setPosition(GUIElement::field.getPosition());
}
      
void GUITextLabel::setFont(sf::Font& font)
{
  text.setFont(font);
}
      
std::string GUITextLabel::getText()
{
  return this->text.getString();
}

void GUITextLabel::setText(std::string text)
{
  this->text.setString(text);
  field.setSize(sf::Vector2f(this->text.getGlobalBounds().width, this->text.getGlobalBounds().height));
}

void GUITextLabel::draw(sf::RenderWindow& window)
{
  window.draw(text);
}
