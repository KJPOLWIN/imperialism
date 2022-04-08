
#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

  #include <SFML/Graphics.hpp>

  class ImageButton
  {
    public:
      ImageButton(sf::Sprite* sprite, sf::Vector2f position, sf::Vector2f size);
      ImageButton();
      
      bool isClicked(sf::Vector2i clickPosition);
      void draw(sf::RenderWindow& targetWindow);

      void setPosition(sf::Vector2f newPosition);
      void setPosition(double x, double y);
      sf::Vector2f getPosition();

      sf::Vector2f getSize();

    private:
      sf::Sprite* sprite{  };
      sf::Vector2f position{  };
      sf::Vector2f size{  };
  };

#endif
