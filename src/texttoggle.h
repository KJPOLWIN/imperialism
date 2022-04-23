#ifndef TEXTTOGGLE_H
#define TEXTTOGGLE_H

  #include <SFML/Graphics.hpp>
  #include <string>

  class TextToggle
  {
    public:
      TextToggle(sf::Font& font, std::string text,
                 sf::Vector2f position, unsigned int characterSize);
      TextToggle();

      bool isClicked(sf::Vector2i clickPosition);
      void draw(sf::RenderWindow& targetWindow);

      void setPosition(sf::Vector2f newPosition);
      void setPosition(double x, double y);
      sf::Vector2f getPosition();

      sf::Vector2f getSize();

    private:
      sf::Text text{  };
      sf::RectangleShape background{  };
 
  };
#endif
