#ifndef MAPNODE_H
#define MAPNODE_H

  #include "hexvector.h"
  #include <SFML/Graphics.hpp>
  #include <array>


  enum class TerrainType
  {
    grassland,
    water,
    desert,
    tundra,
    grassHills,
    desertHills,
    tundraHills,
    forest,
    forestHills,
    jungle,
    jungleHills,
    mountains,
    river,
    blank
  };

  class MapNode
  {
    public:
      MapNode(int x, int y);
      MapNode()
        : terrain{ TerrainType::blank } {}

      void select();
      void disselect();
      void draw(sf::RenderWindow& targetWindow);

      void switchTerrainType();
      void switchTerrainType(TerrainType newTerrain);
      TerrainType getTerrainType();

      sf::Vector2f getPosition();
      void setPosition(HexVector newPosition);
      HexVector getHexPosition();

      bool isSelected{ false };
   
    private:
      std::array<sf::Vertex, 7> vertices{  };
      HexVector hexPosition{  };
      //sf::Vector2i gridPosition{ 0, 0 };
      TerrainType terrain{ TerrainType::water };
  };
#endif
