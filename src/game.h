#ifndef GAME_H
#define GAME_H

  #include "map.h"
  #include "textbutton.h"
  #include "imagebutton.h"
  #include "scrollarea.h"
  #include "textinput.h"
  #include "faction.h"
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
      Map map{ }; 
      int turn{ 0 };

      std::vector<Faction> factions{
        Faction(0, 100, 100, 100, 100, 100),
        Faction(1, 100, 100, 100, 100, 100)
      };

      sf::View mapView{ sf::FloatRect(0, 0, Constant::windowWidth, Constant::windowHeight) };
      sf::View guiView{ sf::FloatRect(0, 0, Constant::windowWidth, Constant::windowHeight) };
      double maxZoom{ 0.5 };
      double minZoom{ 2 };
      
      sf::Texture shadeTexture{  };
      sf::Sprite shade{  };
      
      DisplayMode mode{ DisplayMode::game };
   
      //Pause menu
      sf::RectangleShape pauseMenuBackground{ sf::Vector2f(400, 600) };
      sf::Text pauseMenuLabel{  };
      TextButton menuButton{  };
      TextButton optionsButton{  };
      TextButton saveGameButton{  };
      TextButton exitToDesktopButton{  };

      //Pause button
      sf::Texture pauseButtonTexture{  };
      sf::Sprite pauseButtonSprite{  };
      ImageButton pauseButton{  };

      //Unpause button
      sf::Texture unpauseButtonTexture{  };
      sf::Sprite unpauseButtonSprite{  };
      ImageButton unpauseButton{  };
  
      //Node widget
      sf::RectangleShape nodeWidgetBackground{ sf::Vector2f(400, 200) };
      sf::Text nodeNameLabel{  };
      sf::Texture seaTerrainTexture{  };
      sf::Texture tundraTerrainTexture{  };
      sf::Texture desertTerrainTexture{  };
      sf::Texture grasslandTerrainTexture{  };
      sf::Texture tundraHillsTerrainTexture{  };
      sf::Texture desertHillsTerrainTexture{  };
      sf::Texture grasslandHillsTerrainTexture{  };
      sf::Texture mountainsTerrainTexture{  };
      sf::Texture forestTerrainTexture{  };
      sf::Texture rainforestTerrainTexture{  };
      sf::Texture forestHillsTerrainTexture{  };
      sf::Texture rainforestHillsTerrainTexture{  };
      sf::Texture tundraRiverTerrainTexture{  };
      sf::Texture desertRiverTerrainTexture{  };
      sf::Texture grasslandRiverTerrainTexture{  };
      sf::Sprite seaTerrain{  };
      sf::Sprite tundraTerrain{  };
      sf::Sprite desertTerrain{  };
      sf::Sprite grasslandTerrain{  };
      sf::Sprite tundraHillsTerrain{  };
      sf::Sprite desertHillsTerrain{  };
      sf::Sprite grasslandHillsTerrain{  };
      sf::Sprite mountainsTerrain{  };
      sf::Sprite forestTerrain{  };
      sf::Sprite rainforestTerrain{  };
      sf::Sprite forestHillsTerrain{  };
      sf::Sprite rainforestHillsTerrain{  };
      sf::Sprite tundraRiverTerrain{  };
      sf::Sprite desertRiverTerrain{  };
      sf::Sprite grasslandRiverTerrain{  };
      sf::RectangleShape terrainTest{ sf::Vector2f(300, 80) };

      //Unit widget
      sf::RectangleShape unitWidgetBackground{ sf::Vector2f(800, 200) };
      sf::Text unitNameLabel{  };
      sf::Text unitHealth{  };
      sf::Text unitMovePoints{  };
      sf::Texture riflemenLargeTexture{  };
      sf::Sprite riflemenLarge{  };

      //Next turn button
      TextButton nextTurnButton{  };

      //Map saving menu
      sf::RectangleShape saveMenuBackground{ sf::Vector2f(600, 600) };
      TextButton backButton{  };
      TextButton saveButton{  };
      ScrollArea saveSelect{  };
      TextInput filenameInput{  };
      bool textInputUnclicked{ true };

      //Yields widget
      sf::RectangleShape yieldWidgetBackground{ sf::Vector2f(1000, 50) };
      sf::Text turnCounter{  };
      sf::Texture moneyIconTexture{  };
      sf::Texture foodIconTexture{  };
      sf::Texture woodIconTexture{  };
      sf::Texture stoneIconTexture{  };
      sf::Texture weaponsIconTexture{  };
      sf::Sprite moneyIcon{  };
      sf::Sprite foodIcon{  };
      sf::Sprite woodIcon{  };
      sf::Sprite stoneIcon{  };
      sf::Sprite weaponsIcon{  };
      sf::Text moneyCounter{  };
      sf::Text foodCounter{  };
      sf::Text woodCounter{  };
      sf::Text stoneCounter{  };
      sf::Text weaponsCounter{  };
  };

#endif
