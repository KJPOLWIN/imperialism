#ifndef GAME_H
#define GAME_H

  #include "map.h"
  #include "textbutton.h"
  #include "imagebutton.h"
  #include "gamestate.h"
  #include "constant.h"
  #include <SFML/Graphics.hpp>

  class Game
  {
    public:
      Game(sf::Font& font);

      void mouseInput(GameState& state, sf::RenderWindow& window, sf::Vector2i clickPosition);
      void scrollInput(double scroll);
      void run(sf::RenderWindow& window, double timeElapsed);

      void switchPause();

      void regenerateMap(int width, int height, 
                         int landmassCount, int landmassSize,
                         double landToWaterChance, double waterToLandChance,
                         int mountainRangeMaxLenght, int mountainRangeCountP,
                         double firstPassHillChance, double secondPassHillChance,
                         double forestChance,
                         double riverChance);
      
    private:
      Map map{ }; 
      sf::View mapView{ sf::FloatRect(0, 0, Constant::windowWidth, Constant::windowHeight) };
      sf::View guiView{ sf::FloatRect(0, 0, Constant::windowWidth, Constant::windowHeight) };
      double maxZoom{ 0.5 };
      double minZoom{ 2 };
      sf::Texture shadeTexture{  };
      sf::Sprite shade{  };
      bool paused{ false };
   
      //Pause menu
      sf::RectangleShape pauseMenuBackground{ sf::Vector2f(400, 600) };
      sf::Text pauseMenuLabel{  };
      TextButton menuButton{  };
      TextButton optionsButton{  };
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
  };

#endif
