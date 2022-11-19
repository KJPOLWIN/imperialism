#ifndef GUITEXTLABEL_H 
#define GUITEXTLABEL_H 

  #include "guielement.h"
  #include <SFML/Graphics.hpp>
  #include <vector>
  #include <string>

  class GUITextLabel : public GUIElement
  {
    public:
      GUITextLabel(sf::Vector2f position, sf::Font& font, std::string text, 
                   unsigned int size, GUIElement* masterElement, int flags);
      GUITextLabel(sf::Vector2f position, sf::Font& font, std::string text, 
                   unsigned int size, GUIElement* masterElement);
      GUITextLabel(sf::Font& font, std::string text, unsigned int size, 
                   GUIElement* masterElement, int flags);
      GUITextLabel(sf::Font& font, std::string text, unsigned int size, 
                   GUIElement* masterElement);
      GUITextLabel(unsigned int size, GUIElement* masterElement, int flags);
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
      void positionUpTo(GUIElement* element, int pixels);
      void positionRightTo(GUIElement* element, int pixels);
      void positionDownTo(GUIElement* element, int pixels);
      void positionLeftTo(GUIElement* element, int pixels);

      void setFont(sf::Font& font);
      std::string getText();
      void setText(std::string text);
      void setTextColor(sf::Color color);

      virtual void draw(sf::RenderWindow& window);

    private:
      sf::Text text{  };
  };

#endif
