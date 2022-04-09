#ifndef UNIT_H
#define UNIT_H
  
  #include "mapnode.h"
  #include <SFML/Graphics.hpp>
  #include <string>

  class Unit
  {
    public:
      Unit(int x, int y, std::string name);

      sf::Vector2f getPosition();
      sf::Vector2i getGridPosition();
      std::string getName();

      bool isSelected{ false };

    private:
      MapNode positioningNode{ 0, 0 };

      int health{ 0 };
      int maxHealth{ 0 };
      std::string name{ "" };
  };

#endif
