#ifndef UNIT_H
#define UNIT_H
  
  #include "mapnode.h"
  #include <SFML/Graphics.hpp>
  #include <string>
  #include <vector>

  class Unit
  {
    public:
      Unit(int x, int y, std::string name, int movePoints, std::vector<int> moveCosts);

      void calculatePath(HexVector position, int sizeX, int sizeY);
      void move(int sizeX);
      void generateMCM(int sizeX, int sizeY, std::vector<MapNode>& nodes);      

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
      std::vector<int>& getMoveCosts();
      std::vector<int>& getMoveCostMap();
      int getMoveQueueLenght();

      bool isSelected{ false };

    private:
      MapNode positioningNode{ 0, 0 };

      int health{ 0 };
      int maxHealth{ 0 };

      int movePoints{ 0 };
      int maxMovePoints{ 0 };
      std::vector<int> moveCosts{  };

      std::string name{ "" };

      std::vector<HexVector> moveQueue{  };

      std::vector<int> moveCostMap{  };

      std::vector<MapNode*> frontier{  };
      std::vector<int> priority{  }; 
  };

#endif
