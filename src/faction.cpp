#include "faction.h"
#include "unit.h"
#include "building.h"

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

void Faction::updateResources(std::vector<Unit>& units, 
                              std::vector<Building>& buildings)
{
  //Profits
  for(auto& building : buildings)
  {
    if(building.getFaction() == id && building.completed)
    {
      money   += building.getMoneyProduction();
      food    += building.getFoodProduction();
      wood    += building.getWoodProduction();
      stone   += building.getStoneProduction();
      weapons += building.getWeaponsProduction();
    }
  }

  //Expenses
  for(auto& unit : units)
  {
    if(unit.getFaction() == id)
    {
      --food;
      money -= unit.getUpkeep();
    }
  }

  for(auto& building : buildings)
  {
    if(building.getFaction() == id)
    {
      food -= building.getFoodCost();
      money -= building.getUpkeep();
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
