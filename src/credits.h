#ifndef CREDITS_H
#define CREDITS_H

  #include "textbutton.h"
  #include "gamestate.h"
  #include <SFML/Graphics.hpp>

  class Credits
  {
    public:
      Credits(sf::Font& font);
      
      void mouseInput(GameState& state, sf::Vector2i clickPosition);
      void run(sf::RenderWindow& window);

    private:
      TextButton backButton{  };
      sf::RectangleShape positioningField{ sf::Vector2f(1920, 1080) };
      sf::Text title{  };
      sf::Text version{  };
      
      sf::Text code{  };
      sf::Text codeAuthors{  };

      sf::Text fontLabel{  };
      sf::Text fontName{  };
      sf::Text fontAuthors{  };
      sf::Text fontLicense{  };

      sf::Text sfml{  };
      sf::Text date{  };
      
  };

#endif
