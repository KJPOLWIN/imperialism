#include "gamestate.h"
#include "game.h"
#include "mainmenu.h"
#include "gamesettings.h"
#include "options.h"
#include "credits.h"
#include "constant.h"
#include <SFML/Graphics.hpp>
#include "json.hpp"
#include <fstream>

int main()
{
  //Reading JSON
  nlohmann::json savedOptions{  };
  std::fstream optionsFile{  };
  optionsFile.open("options.json", std::ios::in);

  if(optionsFile.peek() == std::ifstream::traits_type::eof())
  {
    savedOptions["fpsDisplay"] = false;
    savedOptions["vSync"] = false;
  }
  else
  {
    optionsFile >> savedOptions;
  }
  
  //Setting up the window
  sf::RenderWindow window(sf::VideoMode(Constant::windowWidth, 
                                        Constant::windowHeight), 
                          "Imperialism", 
                          //sf::Style::Fullscreen);
                          sf::Style::None);
  window.setKeyRepeatEnabled(false);
  window.setPosition(sf::Vector2i(0,0));


  //Loading fonts
  sf::Font pressStart2P{  };
  pressStart2P.loadFromFile("font/PressStart2P-Regular.ttf");

  //Game state variables
  GameState state{ GameState::mainMenu };
  GameState lastFrameState{ GameState::mainMenu };
  GameState previousState{ GameState::mainMenu };

  //Setting up game states
  MainMenu menu{ pressStart2P };
  GameSettings gameSettings{ pressStart2P };
  Game game{ pressStart2P };
  Options options{ pressStart2P };
  Credits credits{ pressStart2P };

  //Uploading saved options
  options.fpsDisplaySelected = savedOptions["fpsDisplay"];
  options.vSyncSelected = savedOptions["vSync"];
  if(options.fpsDisplaySelected)
  {
    options.toggleFPSDisplay();
  }
  if(options.vSyncSelected)
  {
    options.toggleVSync();
  }
 
  //Setting up fps display
  sf::Text fpsDisplay{ "e", pressStart2P, 16 };
  fpsDisplay.setPosition(5, 5);
  fpsDisplay.setFillColor(sf::Color::Red);

  //Setting up clock, click control and events
  sf::Clock clock{  };
  double timeElapsed{ 0.0 };
  bool canClick{ true };
  sf::Event event{  };

  while(window.isOpen())
  {
    timeElapsed = clock.restart().asSeconds();
    
    window.clear();

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

            case GameState::mainMenu:
            case GameState::game:
            case GameState::options:
            case GameState::credits:
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
            gameSettings.mouseInput(state, clickPosition);
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
      else if(event.type == sf::Event::KeyPressed)
      {
        if(event.key.code == sf::Keyboard::Escape)
        {
          if(state == GameState::game)
          {
            game.switchPause();
          }
        }
        else if(event.key.code == sf::Keyboard::Up)
        {
          if(state == GameState::gameSettings)
          {
            gameSettings.arrowUpPressed();
          }
        }
        else if(event.key.code == sf::Keyboard::Right)
        {
          if(state == GameState::gameSettings)
          {
            gameSettings.arrowRightPressed();
          }
        }
        else if(event.key.code == sf::Keyboard::Left)
        {
          if(state == GameState::gameSettings)
          {
            gameSettings.arrowLeftPressed();
          }
        }
        else if(event.key.code == sf::Keyboard::Down)
        {
          if(state == GameState::gameSettings)
          {
            gameSettings.arrowDownPressed();
          }
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
          game.regenerateMap(gameSettings.getMapWidth(), gameSettings.getMapHeight(), 
                             gameSettings.getLandmassCount(), gameSettings.getLandmassSize(),
                             gameSettings.getLandToWaterChance(), gameSettings.getWaterToLandChance(),
                             gameSettings.getMountainRangeMaxLenght(), gameSettings.getMountainRangeCount(),
                             gameSettings.getFirstPassHillChance(), gameSettings.getSecondPassHillChance(),
                             gameSettings.getForestChance(),
                             gameSettings.getRiverChance());
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

    //Options
    if(options.fpsDisplaySelected)
    {
      fpsDisplay.setString(std::to_string(static_cast<int>(1 / timeElapsed)));
      window.draw(fpsDisplay);
    }

    if(options.vSyncSelected)
    {
      window.setVerticalSyncEnabled(true);
    }
    else
    {
      window.setVerticalSyncEnabled(false);
    }

    window.display();
   
    if(lastFrameState != state)
    {
      previousState = lastFrameState;
    }
    lastFrameState = state;
  }
 
  //Saving options
  savedOptions["fpsDisplay"] = options.fpsDisplaySelected;
  savedOptions["vSync"] = options.vSyncSelected;
  optionsFile.close();
  optionsFile.open("options.json", std::ios::out | std::ios::trunc);
  if(optionsFile.is_open())
  { 
    optionsFile << std::setw(4) << savedOptions << std::endl;
    optionsFile.close();
  }

  return 0;
}
