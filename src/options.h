#ifndef OPTIONS_H
#define OPTIONS_H

  #include "textbutton.h"
  #include "gamestate.h"
  #include <SFML/Graphics.hpp>

  class Options
  {
    public:
      Options(sf::Font& font);
      
      void mouseInput(GameState& state, GameState previousState, sf::Vector2i clickPosition);
      void run(sf::RenderWindow& window);

    private:
      TextButton backButton{  };

  };

#endif
