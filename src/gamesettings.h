#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

  #include "textbutton.h"
  #include "gamestate.h"
  #include <SFML/Graphics.hpp>

  class GameSettings
  {
    public:
      GameSettings(sf::Font& buttonFont);
      
      void mouseInput(GameState& state, sf::RenderWindow& window);
      void run(sf::RenderWindow& window);

    private:
      TextButton startButton{  };

  };

#endif
