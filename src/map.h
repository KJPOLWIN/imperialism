#ifndef MAP_H
#define MAP_H

  #include "mapnode.h"
  #include "unit.h"
  #include <SFML/Graphics.hpp>
  #include <vector>

  class Map
  { 
    public:
      Map(int sizeX, int sizeY);
      
      void selectNodesAndUnits(sf::Vector2f clickPosition, sf::Vector2f viewOffset, double zoom);
      void switchNodeTerrain();
      //void switchNodeTerrain(bool& canClick);
      void draw(sf::RenderWindow& targetWindow);
  
      void regenerate(int sizeX, int sizeY, int landmassCountP, int landmassMaxSize);
      std::string getSelectedNodeName();
      std::string getSelectedUnitName();

    private:
      MapNode& getNode(int x, int y);
      void createLandmass(int x, int y, int size);
      bool neighboursTerrain(int x, int y, TerrainType terrain);

      std::vector<MapNode> nodes{  };
      std::vector<Unit> units{  };
      int sizeX{ 0 };
      int sizeY{ 0 };
      sf::Image clickmap{  };

      sf::Texture grassNodeTexture{  };
      sf::Texture waterNodeTexture{  };
      sf::Texture desertNodeTexture{  };
      sf::Texture tundraNodeTexture{  };
      sf::Texture riflemenTexture{  };
      
      sf::Sprite grassNode{  };
      sf::Sprite waterNode{  };
      sf::Sprite desertNode{  };
      sf::Sprite tundraNode{  };
      sf::Sprite riflemenSprite{  };
  };

#endif
