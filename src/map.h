#ifndef MAP_H
#define MAP_H

  #include "mapnode.h"
  #include <SFML/Graphics.hpp>
  #include <vector>

  class Map
  { 
    public:
      Map(int sizeX, int sizeY);
      
      void selectNodes(sf::Vector2f clickPosition);
      void switchNodeTerrain();
      //void switchNodeTerrain(bool& canClick);
      void draw(sf::RenderWindow& targetWindow);
  
      void regenerate(int sizeX, int sizeY, int landmassCountP, int landmassMaxSize);

    private:
      MapNode& getNode(int x, int y);
      void createLandmass(int x, int y, int size);

      std::vector<MapNode> nodes{  };
      int sizeX{ 0 };
      int sizeY{ 0 };
      sf::Image clickmap{  };

      sf::Texture grassNodeTexture{  };
      sf::Texture waterNodeTexture{  };
      sf::Texture desertNodeTexture{  };
      
      sf::Sprite grassNode{  };
      sf::Sprite waterNode{  };
      sf::Sprite desertNode{  };
  };

#endif
