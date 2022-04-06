#ifndef GUI_H
#define GUI_H
  
  #include "textbutton.h"
  #include <SFML/Graphics.hpp>

  namespace GUI
  {
    void centerTextInField(sf::Text& text, const sf::RectangleShape& field);
    void centerTextInField(TextButton& text, const sf::RectangleShape& field);
  }

#endif
