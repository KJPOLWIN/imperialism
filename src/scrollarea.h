#ifndef SCROLLAREA_H
#define SCROLLAREA_H

  #include "textbutton.h"
  #include "texttoggle.h"
  #include <SFML/Graphics.hpp>

  class ScrollArea
  {
    public:
      ScrollArea(sf::Vector2f position, double height);
      ScrollArea() = default;

      void scroll(int direction);
      void holdInput(sf::Vector2i clickPosition);
      void clickInput(sf::Vector2i clickPosition);
      void releaseInput();
      void draw(sf::RenderWindow& window);

      void bindButton(TextButton& button, sf::Font& font);
      void bindButton(TextToggle& button, sf::Font& font);

    private:
      std::vector<TextButton*> textButtons{  };
      std::vector<TextToggle*> toggleButtons{  };

      sf::RectangleShape scrollbar{  };

      sf::RectangleShape scrollbarBackground{  };

      sf::RectangleShape areaStart{  };
      sf::RectangleShape areaEnd{  };

      sf::Vector2f position{  };
      double drawingHeight{  };
      double areaHeight{  };
      int scrollLevel{ 0 };
      int maxScrollLevel{ 0 };

      bool activatedForMove{ false };
      double mousePosDelta{  };

  };

#endif
