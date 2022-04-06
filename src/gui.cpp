#include "gui.h"
#include "textbutton.h"
#include <SFML/Graphics.hpp>

  #include <iostream>

namespace GUI
{
  void centerTextInField(sf::Text& text, const sf::RectangleShape& field)
  {
    text.setPosition(field.getPosition().x + (field.getSize().x
                                            - text.getGlobalBounds().width) / 2, 
                     text.getPosition().y);
  }
  
  void centerTextInField(TextButton& text, const sf::RectangleShape& field)
  {
    text.setPosition(field.getPosition().x + (field.getSize().x
                                            - text.getSize().x) / 2, 
                     text.getPosition().y);
  }
}
