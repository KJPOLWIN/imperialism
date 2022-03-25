#ifndef GAME_H
#define GAME_H

  #include "map.h"
  #include "textbutton.h"
  #include "gamestate.h"
  #include <SFML/Graphics.hpp>

  class Game
  {
    public:
      Game();

      void mouseInput(GameState& state);
      void run(sf::RenderWindow& window, double timeElapsed);
      
    private:
      Map map{ 8, 7 }; 
      sf::View view{ sf::FloatRect(0, 0, 800, 600) };
  };

#endif
