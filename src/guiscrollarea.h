#ifndef GUISCROLLAREA_H
#define GUISCROLLAREA_H

  #include "guielement.h"
  #include <SFML/Graphics.hpp>

  class GUIScrollArea : public GUIElement
  {
    public:
      GUIScrollArea(sf::Vector2f position, sf::Vector2f size, 
                    GUIElement* masterElement, double scrollingSpeed);
      GUIScrollArea(sf::Vector2f size, 
                    GUIElement* masterElement, double scrollingSpeed);

      GUIScrollArea() = default;

      virtual ~GUIScrollArea() {  };
      
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

      void scroll(int direction);
      void holdInput(sf::Vector2i clickPosition);
      void releaseInput();
      void clickInput(sf::Vector2i clickPosition) override;

      void draw(sf::RenderWindow& window) override;

    private:
      sf::RectangleShape scrollbar{  };
      sf::RectangleShape scrollbarBackground{  };

      double drawingHeight{  };
      double areaHeight{  };
      int scrollLevel{ 0 };
      int maxScrollLevel{ 0 };
      double scrollingSpeed{  };

      bool activatedForMove{ false };
      double mousePosDelta{  };

  };

#endif
