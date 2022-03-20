#include "mapnode.h"
#include <SFML/Graphics.hpp>

int main()
{
  sf::RenderWindow window(sf::VideoMode(800, 600), "Imperialism");
 
  MapNode testNode{ 0, 0 };

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
    testNode.draw(window);
    window.display();
  }

  return 0;
}
