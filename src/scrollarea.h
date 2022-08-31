#ifndef SCROLLAREA_H
#define SCROLLAREA_H

  #include "textbutton.h"
  #include "texttoggle.h"
  #include <SFML/Graphics.hpp>
  #include <string>

  class ScrollArea
  {
    public:
      ScrollArea(sf::Vector2f position, sf::Vector2f size, 
                 double scrollingSpeed);
      ScrollArea() = default;

      void addButton(sf::Font& font, std::string text, 
                     sf::Vector2f position, unsigned int size);
      void addToggle(sf::Font& font, std::string text, 
                     sf::Vector2f position, unsigned int size);

      void scroll(int direction);
      void holdInput(sf::Vector2i clickPosition);
      void clickInput(sf::Vector2i clickPosition);
      void releaseInput();
      void draw(sf::RenderWindow& window);

      std::vector<TextButton>& getButtons();
      std::vector<TextToggle>& getToggles();

    private:
      std::vector<TextButton> textButtons{  };
      std::vector<TextToggle> toggleButtons{  };

      sf::RectangleShape scrollbar{  };

      sf::RectangleShape scrollbarBackground{  };

      sf::RectangleShape areaStart{  };
      sf::RectangleShape areaEnd{  };

      sf::Vector2f position{  };
      double drawingHeight{  };
      double areaHeight{  };
      int scrollLevel{ 0 };
      int maxScrollLevel{ 0 };
      double scrollingSpeed{  };

      bool activatedForMove{ false };
      double mousePosDelta{  };
  
  };

#endif
