#include "mainmenu.h"
#include "gamestate.h"
#include "textbutton.h"
#include <SFML/Graphics.hpp>

  #include <iostream>

MainMenu::MainMenu(sf::Font& buttonFont)
  : title{ "imperialism", buttonFont, 72 },
    newGameButton{ buttonFont, "new game", sf::Vector2f(100.0f, 350.0f), 40 },
    loadGameButton{ buttonFont, "load game", sf::Vector2f(100.0f, 425.0f), 40 },
    optionsButton{ buttonFont, "options", sf::Vector2f(100.0f, 500.0f), 40 },
    creditsButton{ buttonFont, "credits", sf::Vector2f(100.0f, 575.0f), 40 },
    exitButton{ buttonFont, "exit", sf::Vector2f(100.0f, 650.0f), 40 }
{
  title.setPosition(100.0f, 100.0f); 
}

MainMenu::MainMenu(sf::Font& buttonFont, GameState& state)
  : title{ "imperialism", buttonFont, 72 },
    newGameButton{ buttonFont, "new game", sf::Vector2f(100.0f, 350.0f), 40, 
                   [&state]() {
                                state = GameState::gameSettings;
                              }},
    loadGameButton{ buttonFont, "load game", sf::Vector2f(100.0f, 425.0f), 40 },
    optionsButton{ buttonFont, "options", sf::Vector2f(100.0f, 500.0f), 40 },
    creditsButton{ buttonFont, "credits", sf::Vector2f(100.0f, 575.0f), 40 },
    exitButton{ buttonFont, "exit", sf::Vector2f(100.0f, 650.0f), 40 }
{
  title.setPosition(100.0f, 100.0f); 
}

void MainMenu::mouseInput(GameState& state, sf::RenderWindow& window, sf::Vector2i clickPosition)
{
  /*if(newGameButton.isClicked(clickPosition)) 
  {
    state = GameState::gameSettings;
  } */
  newGameButton.isClicked(clickPosition);
  //else if(loadGameButton.isClicked(clickPosition)) 
  if(loadGameButton.isClicked(clickPosition)) 
  {
    state = GameState::mapLoading;
  } 
  else if(optionsButton.isClicked(clickPosition))
  {
    state = GameState::options;
  }
  else if(creditsButton.isClicked(clickPosition))
  {
    state = GameState::credits;
  }
  else if(exitButton.isClicked(clickPosition))
  {
    window.close();
  } 
}

void MainMenu::run(sf::RenderWindow& window)
{
  window.draw(title);
  newGameButton.draw(window);
  loadGameButton.draw(window);
  optionsButton.draw(window);
  creditsButton.draw(window);
  exitButton.draw(window);
}
