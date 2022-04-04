#ifndef UNIT_H
#define UNIT_H
  
  #include "mapnode.h"
  #include <SFML/Graphics.hpp>

  class Unit
  {
    public:
      Unit(int x, int y);

      sf::Vector2f getPosition();

    private:
      MapNode positioningNode{ 0, 0 };

      int health{ 0 };
      int maxHealth{ 0 };
  };

#endif
