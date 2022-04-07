#include "gamestate.h"
#include "game.h"
#include "mainmenu.h"
#include "gamesettings.h"
#include "options.h"
#include "credits.h"
#include <SFML/Graphics.hpp>

    #include <iostream>

int main()
{
  sf::RenderWindow window(sf::VideoMode(1920, 1080), "Imperialism", sf::Style::Fullscreen);
  window.setKeyRepeatEnabled(false);

  sf::Font pressStart2P{  };
  pressStart2P.loadFromFile("font/PressStart2P-Regular.ttf");

  GameState state{ GameState::mainMenu };
  GameState lastFrameState{ GameState::mainMenu };
  GameState previousState{ GameState::mainMenu };

  MainMenu menu{ pressStart2P };
  GameSettings gameSettings{ pressStart2P };
  Game game{ pressStart2P };
  Options options{ pressStart2P };
  Credits credits{ pressStart2P };
  
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
        sf::Vector2i clickPosition{ sf::Mouse::getPosition(window) };

        switch(state)
        {
          case GameState::mainMenu:
            menu.mouseInput(state, window, clickPosition);
          break;

          case GameState::gameSettings:
            gameSettings.mouseInput(state, window, clickPosition);
          break;

          case GameState::game:
            game.mouseInput(state, window, clickPosition);
          break;

          case GameState::options:
            options.mouseInput(state, previousState, clickPosition);
          break;

          case GameState::credits:
            credits.mouseInput(state, clickPosition);
        }

        canClick = false;
      }
      else if(!canClick
           && event.type == sf::Event::MouseButtonReleased
           && event.mouseButton.button == sf::Mouse::Left)
      {
        canClick = true;
      }
      else if(event.type == sf::Event::KeyPressed
           && event.key.code == sf::Keyboard::Escape)
      {
        if(state == GameState::game)
        {
          game.switchPause();
        }
      }
      else if(event.type == sf::Event::MouseWheelScrolled)
      {
        if(state == GameState::game)
        {
          game.scrollInput(event.mouseWheelScroll.delta);
        }
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
        if(lastFrameState == GameState::gameSettings)
        {
          game.regenerateMap(gameSettings.getMapWidth(), gameSettings.getMapHeight(), gameSettings.getLandmassCount(), gameSettings.getLandmassSize());
        }
        
        game.run(window, timeElapsed);
      break;

      case GameState::options:
        options.run(window);
      break;

      case GameState::credits:
        credits.run(window);
      break;
    }
   
    if(lastFrameState != state)
    {
      previousState = lastFrameState;
    }
    lastFrameState = state;
  }
  

  return 0;
}
