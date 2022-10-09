#ifndef FACTION_H
#define FACTION_H

  #include "unit.h"
  #include "building.h"
  #include "hexvector.h"
  #include <vector>

  class Faction
  {
    public:
      Faction(std::size_t id, int startingMoney, 
              int startingFood, int startingWood, 
              int startingStone, int startingWeapons);

      void updateResources(std::vector<Unit>& units,
                           std::vector<Building>& buildings);

      int getMoney();
      int getFood();
      int getWood();
      int getStone();
      int getWeapons();

      void addNodeToBorders(HexVector node);
      std::vector<HexVector>& getBorders();

    private:
      std::size_t id{  };

      int money{ 0 };
      int food{ 0 };
      int wood{ 0 };
      int stone{ 0 };
      int weapons{ 0 };

      std::vector<HexVector> borders{  };
  };

#endif
