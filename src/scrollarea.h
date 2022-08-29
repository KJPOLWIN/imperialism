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
      void draw(sf::RenderWindow& window);

      void bindButton(TextButton& button, sf::Font& font);
      void bindButton(TextToggle& button, sf::Font& font);

    private:
      std::vector<TextButton*> textButtons{  };
      std::vector<TextToggle*> toggleButtons{  };

      sf::RectangleShape scrollbar{  };

      sf::RectangleShape scrollbarBackground{  };

      sf::Vector2f position{  };
      double drawingHeight{  };
      double areaHeight{  };
      int scrollLevel{ 0 };
      int maxScrollLevel{ 0 };
  };

#endif
