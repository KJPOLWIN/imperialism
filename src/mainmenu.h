#ifndef MAINMENU_H
#define MAINMENU_H
  
  #include "gamestate.h"
  #include "textbutton.h"
  #include <SFML/Graphics.hpp>

  class MainMenu
  {
    public:
      MainMenu(sf::Font& buttonFont);

      void mouseInput(GameState& state, sf::RenderWindow& window);
      void run(sf::RenderWindow& window);

    private:
     TextButton startButton{  }; 
      
  };

#endif
