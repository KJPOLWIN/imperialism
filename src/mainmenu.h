#ifndef MAINMENU_H
#define MAINMENU_H
  
  #include "gamestate.h"
  #include "textbutton.h"
  #include <SFML/Graphics.hpp>

  class MainMenu
  {
    public:
      MainMenu(sf::Font& buttonFont);
      MainMenu(sf::Font& buttonFont, GameState& state);

      void mouseInput(GameState& state, sf::RenderWindow& window, sf::Vector2i clickPosition);
      void run(sf::RenderWindow& window);

    private:
      sf::Text title{  };
      TextButton newGameButton{  }; 
      TextButton loadGameButton{  }; 
      TextButton optionsButton{  };
      TextButton creditsButton{  };
      TextButton exitButton{  };
      
  };

#endif
