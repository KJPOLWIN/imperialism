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
      double getLandToWaterChance();
      double getWaterToLandChance();
      int getMountainRangeMaxLenght();
      int getMountainRangeCount();
      double getFirstPassHillChance();
      double getSecondPassHillChance();
      double getForestChance();
      double getRiverChance();


    private:
      TextButton startButton{  };
      TextButton backButton{  };

      TextInput mapWidth{  };
      TextInput mapHeight{  };
      TextInput landmassCount{  };
      TextInput landmassSize{  };
      TextInput landToWaterChance{  };
      TextInput waterToLandChance{  };
      TextInput mountainRangeMaxLenght{  };
      TextInput mountainRangeCount{  };
      TextInput firstPassHillChance{  };
      TextInput secondPassHillChance{  };
      TextInput forestChance{  };
      TextInput riverChance{  };

      sf::Text mapWidthLabel{  };
      sf::Text mapHeightLabel{  };
      sf::Text landmassCountLabel{  };
      sf::Text landmassSizeLabel{  };
      sf::Text landToWaterChanceLabel{  };
      sf::Text waterToLandChanceLabel{  };
      sf::Text mountainRangeMaxLenghtLabel{  };
      sf::Text mountainRangeCountLabel{  };
      sf::Text firstPassHillChanceLabel{  };
      sf::Text secondPassHillChanceLabel{  };
      sf::Text forestChanceLabel{  };
      sf::Text riverChanceLabel{  };
  };

#endif
