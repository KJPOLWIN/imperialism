#ifndef GAME_H
#define GAME_H

  #include "map.h"
  #include "textbutton.h"
  #include "imagebutton.h"
  #include "scrollarea.h"
  #include "textinput.h"
  #include "faction.h"
  #include "guielement.h"
  #include "guitextlabel.h"
  #include "guiimage.h"
  #include "graphicalresource.h"
  #include "gamestate.h"
  #include "constant.h"
  #include <SFML/Graphics.hpp>
  #include <string>

  enum class DisplayMode
  {
    game,
    pauseMenu,
    saveMenu
  };

  class Game
  {
    public:
      Game(sf::Font& font);

      void mouseInput(GameState& state, sf::RenderWindow& window, sf::Vector2i clickPosition, sf::Font& font);
      void holdInput(sf::Vector2i clickPosition);
      void scrollInput(double scroll);
      void textInput(char input);
      void run(sf::RenderWindow& window, double timeElapsed);

      void switchPause();

      void regenerateMap(int width, int height, 
                         int landmassCount, int landmassSize,
                         double landToWaterChance, double waterToLandChance,
                         int mountainRangeMaxLenght, int mountainRangeCountP,
                         double firstPassHillChance, double secondPassHillChance,
                         double forestChance,
                         double riverChance);
      void loadMapFromFile(std::string filename);
      
    private:
      GUIElement screen{ sf::Vector2f(0, 0), sf::Vector2f(1920, 1080), nullptr };

      Map map{ }; 

      sf::View mapView{ sf::FloatRect(0, 0, Constant::windowWidth, Constant::windowHeight) };
      sf::View guiView{ sf::FloatRect(0, 0, Constant::windowWidth, Constant::windowHeight) };
      double maxZoom{ 0.5 };
      double minZoom{ 2 };
     
      GraphicalResource shade{  };
      
      DisplayMode mode{ DisplayMode::game };
   
      //Pause menu
      sf::RectangleShape pauseMenuBackground{ sf::Vector2f(400, 600) };
      sf::Text pauseMenuLabel{  };
      TextButton menuButton{  };
      TextButton optionsButton{  };
      TextButton saveGameButton{  };
      TextButton exitToDesktopButton{  };
  
      //Node widget
      GUIElement nodeWidget{ sf::Vector2f(400, 200), &screen };
      GUITextLabel nodeName{ 24, &nodeWidget };
      GUIImage nodeImage{ &nodeWidget };

      GraphicalResource seaTerrain{  };
      GraphicalResource tundraTerrain{  };
      GraphicalResource desertTerrain{  };
      GraphicalResource grasslandTerrain{  };
      GraphicalResource tundraHillsTerrain{  };
      GraphicalResource desertHillsTerrain{  };
      GraphicalResource grasslandHillsTerrain{  };
      GraphicalResource mountainsTerrain{  };
      GraphicalResource forestTerrain{  };
      GraphicalResource rainforestTerrain{  };
      GraphicalResource forestHillsTerrain{  };
      GraphicalResource rainforestHillsTerrain{  };
      GraphicalResource tundraRiverTerrain{  };
      GraphicalResource desertRiverTerrain{  };
      GraphicalResource grasslandRiverTerrain{  };

      //Building widget
      GUIElement buildingWidget{ sf::Vector2f(400, 150), &screen };
      GUITextLabel buildingName{ 24, &buildingWidget };
      GUITextLabel underConstructionLabel{ 16, &buildingWidget };

      //Unit widget
      GUIElement unitWidget{ sf::Vector2f(800, 200), &screen };
      GUITextLabel unitName{ 24, &unitWidget };
      GUITextLabel unitHealth{ 16, &unitWidget };
      GUITextLabel unitMovePoints{ 16, &unitWidget };
      GUIImage unitImage{ &unitWidget };
      GraphicalResource riflemenLarge{  };

      //Next turn button
      GUITextLabel nextTurnButton{32, &screen };

      //Map saving menu
      sf::RectangleShape saveMenuBackground{ sf::Vector2f(600, 600) };
      TextButton backButton{  };
      TextButton saveButton{  };
      ScrollArea saveSelect{  };
      TextInput filenameInput{  };
      bool textInputUnclicked{ true };

      //Yields widget
      GUIElement yieldWidget{ sf::Vector2f(1100, 50), &screen };
      GUITextLabel turnCounter{ 24, &yieldWidget };
      GUIImage moneyIcon{ &yieldWidget };
      GUIImage foodIcon{ &yieldWidget };
      GUIImage woodIcon{ &yieldWidget };
      GUIImage stoneIcon{ &yieldWidget };
      GUIImage weaponsIcon{ &yieldWidget };
      GUITextLabel moneyCounter{ 24, &yieldWidget };
      GUITextLabel foodCounter{ 24, &yieldWidget };
      GUITextLabel woodCounter{ 24, &yieldWidget };
      GUITextLabel stoneCounter{ 24, &yieldWidget };
      GUITextLabel weaponsCounter{ 24, &yieldWidget };
     
      GraphicalResource moneyIconSprite{  };
      GraphicalResource foodIconSprite{  };
      GraphicalResource woodIconSprite{  };
      GraphicalResource stoneIconSprite{  };
      GraphicalResource weaponsIconSprite{  };
      
      //Pause button
      GraphicalResource pauseButtonSprite{  };
      GUIImage pauseButton{ &yieldWidget };

  };

#endif
