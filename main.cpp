#include "mapnode.h"
#include <SFML/Graphics.hpp>
#include <vector>

int main()
{
  sf::RenderWindow window(sf::VideoMode(800, 600), "Imperialism");
 
  std::vector<MapNode> nodes{  };
  nodes.push_back(MapNode(0, 0));
  nodes.push_back(MapNode(1, 0));
  nodes.push_back(MapNode(2, 0));
  nodes.push_back(MapNode(3, 0));

  nodes.push_back(MapNode(0, 1));
  nodes.push_back(MapNode(1, 1));
  nodes.push_back(MapNode(2, 1));
  nodes.push_back(MapNode(3, 1));
  
  nodes.push_back(MapNode(0, 2));
  nodes.push_back(MapNode(1, 2));
  nodes.push_back(MapNode(2, 2));
  nodes.push_back(MapNode(3, 2));
  
  nodes.push_back(MapNode(0, 3));
  nodes.push_back(MapNode(1, 3));
  nodes.push_back(MapNode(2, 3));
  nodes.push_back(MapNode(3, 3));


  sf::Event event{  };
  while(window.isOpen())
  {
    while(window.pollEvent(event))
    {
      if(event.type == sf::Event::Closed)
      {
        window.close();
      }
    }

    window.clear();
    for( auto& node : nodes )
    {
      node.draw(window);
    }
    window.display();
  }

  return 0;
}
