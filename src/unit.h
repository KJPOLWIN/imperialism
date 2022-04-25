#ifndef UNIT_H
#define UNIT_H
  
  #include "mapnode.h"
  #include <SFML/Graphics.hpp>
  #include <string>

  class Unit
  {
    public:
      Unit(int x, int y, std::string name, int movePoints);

      

      sf::Vector2f getPosition();
      void setPosition(HexVector newPosition);
      HexVector getHexPosition();
      std::string getName();
      int getHealth();
      int getMaxHealth();
      void regenerateMovePoints();
      void decreaseMovePoints(int pointsToDecrease);
      int getMovePoints();
      int getMaxMovePoints();

      bool isSelected{ false };

    private:
      MapNode positioningNode{ 0, 0 };

      int health{ 0 };
      int maxHealth{ 0 };

      int movePoints{ 0 };
      int maxMovePoints{ 0 };

      std::string name{ "" };
  };

#endif
