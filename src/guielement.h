#ifndef GUIELEMENT_H
#define GUIELEMENT_H

  #include <SFML/Graphics.hpp>
  #include <vector>
  #include <functional>

  #include <iostream>
    
  namespace GUIFlag
  {
    enum Flag
    {
      clickable   = 1 << 0,
      togglable   = 1 << 1,
      scrollable  = 1 << 2
    };
  }

  class GUIElement
  {
    public:
      GUIElement(sf::Vector2f position, sf::Vector2f size, GUIElement* masterElement, int flags);
      GUIElement(sf::Vector2f position, sf::Vector2f size, GUIElement* masterElement);
      GUIElement(sf::Vector2f size, GUIElement* masterElement, int flags);
      GUIElement(sf::Vector2f size, GUIElement* masterElement);
      GUIElement() = default;

      void bindElement(GUIElement* slave);
      void setFunction(std::function<void()> func);

      sf::Vector2f getPosition();
      void setPosition(sf::Vector2f position);

      void centerHorizontally();
      void centerVertically();
      void centerInMaster();
      void positionAtTop(int pixels);
      void positionAtRight(int pixels);
      void positionAtBottom(int pixels);
      void positionAtLeft(int pixels);
      void positionUpTo(GUIElement* element, int pixels);
      void positionRightTo(GUIElement* element, int pixels);
      void positionDownTo(GUIElement* element, int pixels);
      void positionLeftTo(GUIElement* element, int pixels);

      bool isClicked(sf::Vector2i clickPosition);
      void clickInput(sf::Vector2i clickPosition);

      void update();
      virtual void draw(sf::RenderWindow& window);

      bool testFlag(int flag);
      void setFlag(int flag);

      /*inline Flag operator|(Flag a, Flag b)
      {
        return static_cast<Flag>(static_cast<int>(a) | static_cast<int>(b));
      }*/

    protected:
      sf::RectangleShape field{  };
      GUIElement* masterElement{ nullptr };
      std::vector<GUIElement*> slaveElements{  };
      int flags{ 0 };
      std::function<void()> function{
        [](){}
      };
  };

#endif
