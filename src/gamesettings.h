#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

  #include "textbutton.h"
  #include "textinput.h"
  #include "gamestate.h"
  #include "guielement.h"
  #include "guitextlabel.h"
  #include "guitextinput.h"
  #include <SFML/Graphics.hpp>
  #include <vector>

  class GameSettings
  {
    public:
      GameSettings(sf::Font& buttonFont, GameState& state);
      
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
      GUIElement screen{ sf::Vector2f(1920, 1080), nullptr };

      GUITextLabel startButton{  };
      GUITextLabel backButton{  };

      GUITextLabel mapWidthLabel{  };
      GUITextLabel mapHeightLabel{  };
      GUITextLabel landmassCountLabel{  };
      GUITextLabel landmassSizeLabel{  };
      GUITextLabel landToWaterChanceLabel{  };
      GUITextLabel waterToLandChanceLabel{  };
      GUITextLabel mountainRangeMaxLenghtLabel{  };
      GUITextLabel mountainRangeCountLabel{  };
      GUITextLabel firstPassHillChanceLabel{  };
      GUITextLabel secondPassHillChanceLabel{  };
      GUITextLabel forestChanceLabel{  };
      GUITextLabel riverChanceLabel{  };

      std::vector<GUITextInput> inputs{  };
      std::size_t activeInputId{ 0 };
      
      /*TextButton startButton{  };
      
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
      sf::Text riverChanceLabel{  };*/

      bool canProceed{ true };
  };

#endif
