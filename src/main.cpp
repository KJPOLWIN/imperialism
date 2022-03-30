#include "gamestate.h"
#include "game.h"
#include "mainmenu.h"
#include "gamesettings.h"
#include <SFML/Graphics.hpp>

    #include <iostream>

int main()
{
  sf::RenderWindow window(sf::VideoMode(800, 600), "Imperialism");

  sf::Font pressStart2P{  };
  pressStart2P.loadFromFile("font/PressStart2P-Regular.ttf");

  GameState state{ GameState::mainMenu };
  GameState oldState{ GameState::mainMenu };

  MainMenu menu{ pressStart2P };
  GameSettings gameSettings{ pressStart2P };
  Game game{  };
  
  sf::Clock clock{  };
  double timeElapsed{ 0.0 };
  bool canClick{ true };
  sf::Event event{  };

  while(window.isOpen())
  {
    timeElapsed = clock.restart().asSeconds();
    
    //Input
    while(window.pollEvent(event))
    {
      if(event.type == sf::Event::Closed)
      {
        window.close();
      }
      else if(event.type == sf::Event::TextEntered)
      {
        if(event.text.unicode < 128)
        {
          switch(state)
          {
            case GameState::gameSettings:
              gameSettings.textInput(static_cast<char>(event.text.unicode));
            break;
          }
        }
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

        canClick = false;
      }
      else if(!canClick
           && event.type == sf::Event::MouseButtonReleased
           && event.mouseButton.button == sf::Mouse::Left)
      {
        canClick = true;
      }
    }

    //Updating and drawing
    switch(state)
    {
      case GameState::mainMenu:
        menu.run(window);
      break;

      case GameState::gameSettings:
        gameSettings.run(window);
      break;

      case GameState::game:
        if(oldState == GameState::gameSettings)
        {
          game.regenerateMap(gameSettings.getMapWidth(), gameSettings.getMapHeight());
        }
        
        game.run(window, timeElapsed);
      break;
    }
    
    oldState = state;
  }
  

  return 0;
}
