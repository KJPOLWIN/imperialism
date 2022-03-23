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
      void run(sf::RenderWindow& window);
      
    private:
      Map map{ 8, 7 }; 

  };

#endif
