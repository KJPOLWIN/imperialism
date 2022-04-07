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
      
  };

#endif
