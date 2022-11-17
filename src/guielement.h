#ifndef GUIELEMENT_H
#define GUIELEMENT_H

  #include <SFML/Graphics.hpp>
  #include <vector>

  class GUIElement
  {
    public:
      GUIElement(sf::Vector2f position, sf::Vector2f size, GUIElement* masterElement);
      GUIElement(sf::Vector2f size, GUIElement* masterElement);
      GUIElement() = default;

      sf::Vector2f getPosition();
      void setPosition(sf::Vector2f position);

      void centerHorizontally();
      void centerVertically();
      void centerInMaster();
      void positionAtTop(int pixels);
      void positionAtRight(int pixels);
      void positionAtBottom(int pixels);
      void positionAtLeft(int pixels);

      bool isClicked(sf::Vector2i clickPosition);

      void update();
      void draw(sf::RenderWindow& window);
      
      enum class Flag
      {
        clickable   = 1,
        togglable   = 2,
        scrollable  = 4
      };

    private:
      sf::RectangleShape field{  };
      GUIElement* masterElement{ nullptr };
      std::vector<GUIElement*> slaveElements{  };
  };

#endif
