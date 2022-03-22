#include "map.h"
#include <SFML/Graphics.hpp>
#include <vector>

int main()
{
  sf::RenderWindow window(sf::VideoMode(800, 600), "Imperialism");

  Map map(8, 7);

  bool canClick{ true };
  sf::Event event{  };
  while(window.isOpen())
  {
    while(window.pollEvent(event))
    {
      if(event.type == sf::Event::Closed)
      {
        window.close();
      }
      else if(event.type == sf::Event::MouseButtonPressed)
      {
        canClick = false;
      }
      else if(event.type == sf::Event::MouseButtonReleased)
      {
        canClick = true;
      }
    }

    map.selectNodes(sf::Mouse::getPosition(window));
    //map.switchNodeTerrain(canClick);
    map.switchNodeTerrain();

    window.clear();
    map.draw(window);
    window.display();
  }

  return 0;
}
