#ifndef BUILDING_H
#define BUILDING_H

  #include "mapnode.h"
  #include <SFML/Graphics.hpp>
  #include <string>

  class Building
  {
    public:
      Building(int x, int y, std::string name, int faction,
               int turnsToBuild, 
               int upkeep, int population,
               int moneyProduction, int foodProduction,
               int woodProduction, int stoneProduction,
               int weaponsProduction);
      Building() = default;

      void update();

      sf::Vector2f getPosition();
      HexVector getHexPosition();
      void setPosition(HexVector newPosition);

      std::string getName();
      int getFaction();

      int getUpkeep();
      int getFoodCost();

      int getMoneyProduction();
      int getFoodProduction();
      int getWoodProduction();
      int getStoneProduction();
      int getWeaponsProduction();

      bool isSelected{ false };
      bool completed{ false };
      int getTurnsToBuild();

    private:
      MapNode positioningNode{ 0, 0 };

      int turnsToBuild{ 3 };

      std::string name{ "" };

      int faction{ 0 };

      int upkeep{ 0 };
      int population{ 0 };

      int moneyProduction{ 0 };
      int foodProduction{ 0 };
      int woodProduction{ 0 };
      int stoneProduction{ 0 };
      int weaponsProduction{ 0 };
  };

#endif
