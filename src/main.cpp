#include "gamestate.h"
#include "game.h"
#include "mainmenu.h"
#include "gamesettings.h"
#include "options.h"
#include "credits.h"
#include "maploading.h"
#include "constant.h"
#include <SFML/Graphics.hpp>
#include "json.hpp"
#include <fstream>

  #include <iostream>

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
  MainMenu menu{ pressStart2P, state };
  GameSettings gameSettings{ pressStart2P };
  Game game{ pressStart2P, state };
  Options options{ pressStart2P, state, previousState };
  Credits credits{ pressStart2P, state };
  MapLoading mapLoading{ pressStart2P };

  //Uploading saved options
  options.fpsDisplaySelected = savedOptions["fpsDisplay"];
  options.vSyncSelected = savedOptions["vSync"];
  options.setFPSDisplay(savedOptions["fpsDisplay"]);
  options.setVSync(savedOptions["vSync"]);
 
  //Setting up fps display
  sf::Text fpsDisplay{ "e", pressStart2P, 16 };
  fpsDisplay.setPosition(5, 5);
  fpsDisplay.setFillColor(sf::Color::Red);
      
  //Loading splash screen
  sf::Texture backgroundTexture{  };
  sf::Texture shadeTexture{  };
  sf::Sprite background{  };
  sf::Sprite shade{  };
  sf::Text mainTitle{ "imperialism", pressStart2P, 72 };
  sf::Text loadingText{ "loading...", pressStart2P, 32 };
  
  backgroundTexture.loadFromFile("texture/loadingbackground.png");
  shadeTexture.loadFromFile("texture/loadingshade.png");
  background.setTexture(backgroundTexture);
  shade.setTexture(shadeTexture);
  mainTitle.setPosition(sf::Vector2f(75.0f,830.0f));
  loadingText.setPosition(sf::Vector2f(75.0f,950.0f));

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
      if(event.type == sf::Event::Closed) //Close window
      {
        window.close();
      }
      else if(event.type == sf::Event::TextEntered) //Text is entered
      {
        if(event.text.unicode < 128)
        {
          switch(state)
          {
            case GameState::gameSettings:
              gameSettings.textInput(static_cast<char>(event.text.unicode));
            break;

            case GameState::game:
              game.textInput(static_cast<char>(event.text.unicode));
            break;
            
            case GameState::mainMenu:
            case GameState::options:
            case GameState::credits:
            case GameState::mapLoading:
            break;
          }
        }
      }
      else if(canClick    //Single click
          && event.type == sf::Event::MouseButtonPressed
          && event.mouseButton.button == sf::Mouse::Left)
      {
        sf::Vector2i clickPosition{ sf::Mouse::getPosition(window) };

        switch(state)
        {
          case GameState::mainMenu:
            menu.mouseInput(clickPosition);
          break;

          case GameState::gameSettings:
            gameSettings.mouseInput(state, clickPosition);
          break;

          case GameState::game:
            game.mouseInput(window, clickPosition, pressStart2P);
          break;

          case GameState::options:
            options.mouseInput(clickPosition);
          break;

          case GameState::credits:
            credits.mouseInput(clickPosition);
          break;

          case GameState::mapLoading:
            mapLoading.mouseInput(state, clickPosition);
          break;
        }

        canClick = false;
      }
      else if(!canClick   //Mouse button is released
           && event.type == sf::Event::MouseButtonReleased
           && event.mouseButton.button == sf::Mouse::Left)
      {
        canClick = true;

        switch(state)
        {
          case GameState::mapLoading:
            mapLoading.releaseInput();
          break;

          case GameState::mainMenu:
          case GameState::gameSettings:
          case GameState::game:
          case GameState::options:
          case GameState::credits:
          break;
        }
      }
      else if(event.type == sf::Event::KeyPressed)
      {
        if(event.key.code == sf::Keyboard::Escape)  //Enter pressed
        {
          if(state == GameState::game)
          {
            game.switchPause();
          }
        }
        else if(event.key.code == sf::Keyboard::Up) //Up arrow pressed
        {
          if(state == GameState::gameSettings)
          {
            gameSettings.arrowUpPressed();
          }
        }
        else if(event.key.code == sf::Keyboard::Right)  //Right arrow pressed
        {
          if(state == GameState::gameSettings)
          {
            gameSettings.arrowRightPressed();
          }
        }
        else if(event.key.code == sf::Keyboard::Left) //Left arrow pressed
        {
          if(state == GameState::gameSettings)
          {
            gameSettings.arrowLeftPressed();
          }
        }
        else if(event.key.code == sf::Keyboard::Down) //Down arrow pressed
        {
          if(state == GameState::gameSettings)
          {
            gameSettings.arrowDownPressed();
          }
        }

      }
      else if(event.type == sf::Event::MouseWheelScrolled)  //Mouse wheel scrolled
      {
        switch(state)
        {
          case GameState::game:
            game.scrollInput(event.mouseWheelScroll.delta);
          break;
          
          case GameState::mapLoading:
            mapLoading.scrollInput(event.mouseWheelScroll.delta);
          break;

          case GameState::mainMenu:
          case GameState::gameSettings:
          case GameState::options:
          case GameState::credits:
          break;
        }
      }
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) //Continuous click
    {
      sf::Vector2i clickPosition{ sf::Mouse::getPosition(window) };
      
      switch(state)
      {
        case GameState::mapLoading:
          mapLoading.holdInput(clickPosition);
        break;
        
        case GameState::game:
          game.holdInput(clickPosition);
        break;

        case GameState::mainMenu:
        case GameState::gameSettings:
        case GameState::options:
        case GameState::credits:
        break;
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
          window.draw(background);
          window.draw(shade);
          window.draw(mainTitle);
          window.draw(loadingText);
          window.display();

          game.regenerateMap(gameSettings.getMapWidth(), gameSettings.getMapHeight(), 
                             gameSettings.getLandmassCount(), gameSettings.getLandmassSize(),
                             gameSettings.getLandToWaterChance(), gameSettings.getWaterToLandChance(),
                             gameSettings.getMountainRangeMaxLenght(), gameSettings.getMountainRangeCount(),
                             gameSettings.getFirstPassHillChance(), gameSettings.getSecondPassHillChance(),
                             gameSettings.getForestChance(),
                             gameSettings.getRiverChance());
        }
        else if(lastFrameState == GameState::mapLoading)
        {
          window.draw(background);
          window.draw(shade);
          window.draw(mainTitle);
          window.draw(loadingText);
          window.display();

          //std::cout << mapLoading.getMapFilename() << "\n";

          game.loadMapFromFile(mapLoading.getMapFilename());
        }
        
        game.run(window, timeElapsed);
      break;

      case GameState::options:
        options.run(window);
      break;

      case GameState::credits:
        credits.run(window);
      break;

      case GameState::mapLoading:
        if(lastFrameState != GameState::mapLoading)
        {
          mapLoading.loadFilenames(pressStart2P);
        }
        
        mapLoading.run(window);
      break;

      case GameState::exit:
        window.close();
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
