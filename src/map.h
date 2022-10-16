#ifndef MAP_H
#define MAP_H

  #include "mapnode.h"
  #include "unit.h"
  #include "building.h"
  #include "faction.h"
  #include "graphicalresource.h"
  #include <SFML/Graphics.hpp>
  #include "json.hpp"
  #include <vector>
  #include <map>

  class Map
  { 
    public:
      Map();
   
      void nextTurn(); 
      void moveUnits(HexVector position); 
      sf::Vector2i getClickedNode(sf::Vector2f clickPosition, sf::Vector2f viewOffset, double zoom); 
      void selectNodesAndUnits(sf::Vector2f clickPosition, sf::Vector2f viewOffset, double zoom);
      //void switchNodeTerrain();
      void draw(sf::RenderWindow& targetWindow, sf::Vector2f viewOffset, double zoom);
  
      void regenerate(int sizeX, int sizeY, 
                      int landmassCountP, int landmassMaxSize,
                      double landToWaterChance, double waterToLandChance,
                      int mountainRangeMaxLenght, int mountainRangeCountP,
                      double firstPassHillChance, double secondPassHillChance,
                      double forestChance,
                      double riverChance);
      void saveToFile(std::string filename); 
      void loadFromFile(std::string filename);
      
      std::string getSelectedNodeName();
      Unit& getSelectedUnit();
      Building& getSelectedBuilding();

      int getTurn();
      std::vector<Faction>& getFactions();
      std::vector<Unit>& getUnits();
      std::vector<Building>& getBuildings();

    private:
      MapNode& getNode(int q, int r, int s);
      MapNode& getNode(HexVector position);
      MapNode& getNode(sf::Vector2i position);
      std::size_t getNodeID(HexVector position);
      std::size_t getNodeID(int q, int r, int s);
      MapNode& getNeighbour(int mainQ, int mainR, int mainS, int directionID);
      MapNode& getNeighbour(HexVector mainNodePosition, int directionID);
      void createLandmass(int q, int r, int s, int size);
      void createLandmass(HexVector position, int size);
      void createLandmass(int x, int y, int size);
      bool neighboursTerrain(int q, int r, int s, TerrainType terrain);
      bool neighboursTerrain(HexVector position, TerrainType terrain);
      bool neighboursTerrain(int x, int y, TerrainType terrain);
      
      int turn{ 0 };

      std::vector<Faction> factions{
        Faction(0, 100, 100, 100, 100, 100),
        Faction(1, 100, 100, 100, 100, 100)
      };

      std::vector<Building> templateBuildings{
        Building("Farm",
                 3,
                 1, 1,
                 0, 4, 0, 0, 0)
      };

      std::vector<MapNode> nodes{  };
      MapNode nothingness{  };
      Unit nobody{  };
      Building nowhere{  };
      std::vector<Unit> units{  };
      std::vector<Building> buildings{  };
      int sizeX{ 0 };
      int sizeY{ 0 };
      sf::Image clickmap{  };

      GraphicalResource selectedNode{  };
      GraphicalResource nodeBorder{  };
      GraphicalResource nodeBorderSelected{  };
      GraphicalResource nodeBorderAlly{  };
      GraphicalResource nodeBorderEnemy{  };
      GraphicalResource nodeBorderFragment{  };

      GraphicalResource grassNode{  };
      GraphicalResource waterNode{  };
      GraphicalResource desertNode{  };
      GraphicalResource tundraNode{  };
      GraphicalResource grassHillsNode{  };
      GraphicalResource desertHillsNode{  };
      GraphicalResource tundraHillsNode{  };
      GraphicalResource forestNode{  };
      GraphicalResource forestHillsNode{  };
      GraphicalResource jungleNode{  };
      GraphicalResource jungleHillsNode{  };
      GraphicalResource mountainsNode{  };
      GraphicalResource grasslandRiverNode{  };
      GraphicalResource desertRiverNode{  };
      GraphicalResource tundraRiverNode{  };

      GraphicalResource riflemen{  };

      GraphicalResource construction{  };
      GraphicalResource farm{  };
  };

#endif
