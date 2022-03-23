#include "gamestate.h"
#include "game.h"
#include "mainmenu.h"
#include "gamesettings.h"
#include <SFML/Graphics.hpp>
#include <vector>

int main()
{
  sf::RenderWindow window(sf::VideoMode(800, 600), "Imperialism");

  sf::Font pressStart2P{  };
  pressStart2P.loadFromFile("font/PressStart2P-Regular.ttf");

  GameState state{ GameState::mainMenu };

  MainMenu menu{ pressStart2P };
  GameSettings gameSettings{ pressStart2P };
  Game game{  };

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
      else if(canClick
          && event.type == sf::Event::MouseButtonPressed
          && event.mouseButton.button == sf::Mouse::Left)
      {
        switch(state)
        {
          case GameState::mainMenu:
            menu.mouseInput(state, window);
          break;

          case GameState::gameSettings:
            gameSettings.mouseInput(state, window);
          break;

          case GameState::game:
            game.mouseInput(state);
          break;
        }

        //map.switchNodeTerrain();
        canClick = false;
      }
      else if(!canClick
           && event.type == sf::Event::MouseButtonReleased
           && event.mouseButton.button == sf::Mouse::Left)
      {
        canClick = true;
      }
    }

    switch(state)
    {
      case GameState::mainMenu:
        menu.run(window);
      break;

      case GameState::gameSettings:
        gameSettings.run(window);
      break;

      case GameState::game:
        game.run(window);
      break;
    }
  }

  return 0;
}
