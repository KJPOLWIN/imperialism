#include "guiimage.h"
#include "guielement.h"
#include "graphicalresource.h"
#include <SFML/Graphics.hpp>
#include <vector>


GUIImage::GUIImage(sf::Vector2f position, GraphicalResource* image, GUIElement* masterElement)
  : GUIElement{ position, sf::Vector2f(0, 0), masterElement },
    image{ image }
{
  field.setSize(image->getSpriteSize());
}

GUIImage::GUIImage(GUIElement* masterElement)
  : GUIElement{ sf::Vector2f(0, 0), masterElement },
    image{ nullptr }
{

}

void GUIImage::setPosition(sf::Vector2f position)
{
  GUIElement::setPosition(position);
  if(image != nullptr)
  {
    image->setPosition(position);
  }
}
      
void GUIImage::centerHorizontally()
{
  GUIElement::centerHorizontally();
  if(image != nullptr)
  {
    image->setPosition(GUIElement::field.getPosition());
  }
}

void GUIImage::centerVertically()
{
  GUIElement::centerVertically();
  if(image != nullptr)
  {
    image->setPosition(GUIElement::field.getPosition());
  }
}

void GUIImage::centerInMaster()
{
  GUIImage::centerHorizontally();
  GUIImage::centerVertically();
}

void GUIImage::positionAtTop(int pixels)
{
  GUIElement::positionAtTop(pixels);
  if(image != nullptr)
  {
    image->setPosition(GUIElement::field.getPosition());
  }
}

void GUIImage::positionAtRight(int pixels)
{
  GUIElement::positionAtRight(pixels);
  if(image != nullptr)
  {
    image->setPosition(GUIElement::field.getPosition());
  }
}

void GUIImage::positionAtBottom(int pixels)
{
  GUIElement::positionAtBottom(pixels);
  if(image != nullptr)
  {
    image->setPosition(GUIElement::field.getPosition());
  }
}

void GUIImage::positionAtLeft(int pixels)
{
  GUIElement::positionAtLeft(pixels);
  if(image != nullptr)
  {
    image->setPosition(GUIElement::field.getPosition());
  }
}
      
void GUIImage::setImage(GraphicalResource* image)
{
  this->image = image;
  this->image->setPosition(GUIElement::field.getPosition());
  GUIElement::field.setSize(image->getSpriteSize());
}
      
void GUIImage::draw(sf::RenderWindow& window)
{
  if(image != nullptr)
  {
    image->draw(window);
  }
}
