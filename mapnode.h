#ifndef MAPNODE_H
#define MAPNODE_H

  #include <SFML/Graphics.hpp>
  #include <array>

  class MapNode
  {
    public:
      MapNode(int x, int y);

      void draw(sf::RenderWindow& targetWindow);

    private:
      std::array<sf::Vertex, 7> vertices{  };

  };
#endif
