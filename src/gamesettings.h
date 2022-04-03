#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

  #include "textbutton.h"
  #include "textinput.h"
  #include "gamestate.h"
  #include <SFML/Graphics.hpp>

  class GameSettings
  {
    public:
      GameSettings(sf::Font& buttonFont);
      
      void mouseInput(GameState& state, sf::RenderWindow& window, sf::Vector2i clickPosition);
      void textInput(char input);
      void run(sf::RenderWindow& window);

      int getMapWidth();
      int getMapHeight();
      int getLandmassCount();
      int getLandmassSize();

    private:
      TextButton startButton{  };
      TextButton backButton{  };

      TextInput mapWidth{  };
      TextInput mapHeight{  };
      TextInput landmassCount{  };
      TextInput landmassSize{  };

      sf::Text mapWidthLabel{  };
      sf::Text mapHeightLabel{  };
      sf::Text landmassCountLabel{  };
      sf::Text landmassSizeLabel{  };
  };

#endif
