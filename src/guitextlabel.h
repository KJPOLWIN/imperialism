#ifndef GUITEXTLABEL_H 
#define GUITEXTLABEL_H 

  #include "guielement.h"
  #include <SFML/Graphics.hpp>
  #include <vector>
  #include <string>

  class GUITextLabel : public GUIElement
  {
    public:
      GUITextLabel(sf::Vector2f position, sf::Font& font, std::string text, unsigned int size, GUIElement* masterElement);
      GUITextLabel(sf::Font& font, std::string text, unsigned int size, GUIElement* masterElement);
      GUITextLabel(unsigned int size, GUIElement* masterElement);
      GUITextLabel() = default;

      void setPosition(sf::Vector2f position);
      
      void centerHorizontally();
      void centerVertically();
      void centerInMaster();
      void positionAtTop(int pixels);
      void positionAtRight(int pixels);
      void positionAtBottom(int pixels);
      void positionAtLeft(int pixels);

      void setFont(sf::Font& font);
      std::string getText();
      void setText(std::string text);

      virtual void draw(sf::RenderWindow& window);

    private:
      sf::Text text{  };
  };

#endif
