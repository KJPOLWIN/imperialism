#ifndef MAP_H
#define MAP_H

  #include "mapnode.h"
  #include <SFML/Graphics.hpp>
  #include <vector>

  class Map
  { 
    public:
      Map(int sizeX, int sizeY);
      
      void selectNodes(sf::Vector2i clickPosition);
      void switchNodeTerrain();
      //void switchNodeTerrain(bool& canClick);
      void draw(sf::RenderWindow& targetWindow);

    private:
      MapNode& getNode(int x, int y);

      std::vector<MapNode> nodes{  };
      const int sizeX{ 0 };
      const int sizeY{ 0 };
      sf::Image clickmap{  };

      sf::Texture grassNodeTexture{  };
      sf::Texture waterNodeTexture{  };
      sf::Texture desertNodeTexture{  };
      
      sf::Sprite grassNode{  };
      sf::Sprite waterNode{  };
      sf::Sprite desertNode{  };
  };

#endif
