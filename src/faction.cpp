#include "faction.h"
#include "unit.h"

Faction::Faction(std::size_t id, int startingMoney, 
                 int startingFood, int startingWood, 
                 int startingStone, int startingWeapons)
  : id{ id },
    money{ startingMoney },
    food{ startingFood },
    wood{ startingWood },
    stone{ startingStone },
    weapons{ startingWeapons }
{

}

void Faction::updateResources(std::vector<Unit>& units)
{
  //Profits

  //Expenses
  for(auto& unit : units)
  {
    if(unit.getFaction() == id)
    {
      //Upkeep
      --food;
      money -= unit.getUpkeep();
    }
  }
}
      
int Faction::getMoney()
{
  return money;
}

int Faction::getFood()
{
  return food;
}

int Faction::getWood()
{
  return wood;
}

int Faction::getStone()
{
  return stone;
}

int Faction::getWeapons()
{
  return weapons;
}
