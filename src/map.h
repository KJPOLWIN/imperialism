#ifndef MAP_H
#define MAP_H

  #include "mapnode.h"
  #include "unit.h"
  #include <SFML/Graphics.hpp>
  #include <vector>

  class Map
  { 
    public:
      Map();
   
      void nextTurn(); 
      void moveUnits(HexVector position); 
      sf::Vector2i getClickedNode(sf::Vector2f clickPosition, sf::Vector2f viewOffset, double zoom); 
      void selectNodesAndUnits(sf::Vector2f clickPosition, sf::Vector2f viewOffset, double zoom);
      void switchNodeTerrain();
      //void switchNodeTerrain(bool& canClick);
      void draw(sf::RenderWindow& targetWindow);
  
      void regenerate(int sizeX, int sizeY, int landmassCountP, int landmassMaxSize);
      std::string getSelectedNodeName();
      //std::string getSelectedUnitName();
      Unit& getSelectedUnit();

    private:
      MapNode& getNode(int q, int r, int s);
      void createLandmass(int q, int r, int s, int size);
      bool neighboursTerrain(int q, int r, int s, TerrainType terrain);

      std::vector<MapNode> nodes{  };
      MapNode nothingness{  };
      Unit nobody{ 0, 0, "", 0 };
      std::vector<Unit> units{  };
      int sizeX{ 0 };
      int sizeY{ 0 };
      sf::Image clickmap{  };

      sf::Texture selectedNodeTexture{  };
      sf::Texture grassNodeTexture{  };
      sf::Texture waterNodeTexture{  };
      sf::Texture desertNodeTexture{  };
      sf::Texture tundraNodeTexture{  };
      sf::Texture mountainsNodeTexture{  };
      sf::Texture riflemenTexture{  };
      
      sf::Sprite selectedNode{  };
      sf::Sprite grassNode{  };
      sf::Sprite waterNode{  };
      sf::Sprite desertNode{  };
      sf::Sprite tundraNode{  };
      sf::Sprite mountainsNode{  };
      sf::Sprite riflemenSprite{  };

      sf::Text debug{  };
  };

#endif
