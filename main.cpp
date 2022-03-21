#include "map.h"
#include <SFML/Graphics.hpp>
#include <vector>

  #include <iostream>

int main()
{
  sf::RenderWindow window(sf::VideoMode(800, 600), "Imperialism");

  Map map(8, 7);

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

    //std::cout << "x: " << sf::Mouse::getPosition(window).x
    //          << "\ty: " << sf::Mouse::getPosition(window).y << "\n";
    
    //if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    //{
      map.selectNodes(sf::Mouse::getPosition(window));
    //}

    window.clear();
    map.draw(window);
    window.display();
  }

  return 0;
}
