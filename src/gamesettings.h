#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

  #include "textbutton.h"
  #include "textinput.h"
  #include "gamestate.h"
  #include <SFML/Graphics.hpp>
  #include <vector>

  class GameSettings
  {
    public:
      GameSettings(sf::Font& buttonFont);
      
      void mouseInput(GameState& state, sf::Vector2i clickPosition);
      void textInput(char input);
      void arrowUpPressed();
      void arrowRightPressed();
      void arrowDownPressed();
      void arrowLeftPressed();
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
      
      std::vector<TextInput> inputs{  };
      std::size_t activeInputId{ 0 };

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

      bool canProceed{ true };
  };

#endif
