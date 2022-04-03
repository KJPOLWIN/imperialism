#ifndef MAINMENU_H
#define MAINMENU_H
  
  #include "gamestate.h"
  #include "textbutton.h"
  #include <SFML/Graphics.hpp>

  class MainMenu
  {
    public:
      MainMenu(sf::Font& buttonFont);

      void mouseInput(GameState& state, sf::RenderWindow& window, sf::Vector2i clickPosition);
      void run(sf::RenderWindow& window);

    private:
      sf::Text title{  };
      TextButton startButton{  }; 
      TextButton optionsButton{  };
      TextButton creditsButton{  };
      TextButton exitButton{  };
      
  };

#endif
