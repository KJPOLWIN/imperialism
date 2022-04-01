#ifndef GAME_H
#define GAME_H

  #include "map.h"
  #include "textbutton.h"
  #include "gamestate.h"
  #include <SFML/Graphics.hpp>

  class Game
  {
    public:
      Game(sf::Font& font);

      void mouseInput(GameState& state, sf::RenderWindow& window);
      void run(sf::RenderWindow& window, double timeElapsed);

      void switchPause();

      void regenerateMap(int width, int height, int landmassCount, int landmassSize);
      
    private:
      Map map{ 8, 7 }; 
      sf::View mapView{ sf::FloatRect(0, 0, 800, 600) };
      sf::View guiView{ sf::FloatRect(0, 0, 800, 600) };
      sf::Texture shadeTexture{  };
      sf::Sprite shade{  };
      bool paused{ false };

      sf::RectangleShape pauseMenuBackground{ sf::Vector2f(300, 400) };
      sf::Text pauseMenuLabel{  };
      TextButton menuButton{  };
  };

#endif
