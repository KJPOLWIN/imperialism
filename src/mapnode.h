#ifndef MAPNODE_H
#define MAPNODE_H

  #include <SFML/Graphics.hpp>
  #include <array>

  enum class TerrainType
  {
    grassland,
    water,
    desert,
    tundra
  };

  class MapNode
  {
    public:
      MapNode(int x, int y);

      void select();
      void disselect();
      void draw(sf::RenderWindow& targetWindow);

      void switchTerrainType();
      void switchTerrainType(TerrainType newTerrain);
      TerrainType getTerrainType();

      sf::Vector2f getPosition();
      sf::Vector2i getGridPosition();

      bool isSelected{ false };
   
    private:
      std::array<sf::Vertex, 7> vertices{  };
      sf::Vector2i gridPosition{ 0, 0 };
      TerrainType terrain{ TerrainType::water };
  };
#endif
