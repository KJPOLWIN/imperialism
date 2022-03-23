#ifndef TEXTBUTTON_H
#define TEXTBUTTON_H

  #include <SFML/Graphics.hpp>
  #include <string>

  class TextButton
  {
    public:
      TextButton(sf::Font& font, std::string text, 
                 sf::Vector2f position, unsigned int size);
      TextButton();
      
      bool isClicked(sf::Vector2i clickPosition);
      void draw(sf::RenderWindow& targetWindow);

    private:
      sf::Text text{  };

  };

#endif
