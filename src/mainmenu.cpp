#include "mainmenu.h"
#include "gamestate.h"
#include "textbutton.h"
#include <SFML/Graphics.hpp>

MainMenu::MainMenu(sf::Font& buttonFont)
  : title{ "imperialism", buttonFont, 50 },
    startButton{ buttonFont, "start", sf::Vector2f(50.0f, 150.0f), 30 },
    optionsButton{ buttonFont, "options", sf::Vector2f(50.0f, 200.0f), 30 },
    creditsButton{ buttonFont, "credits", sf::Vector2f(50.0f, 250.0f), 30 },
    exitButton{ buttonFont, "exit", sf::Vector2f(50.0f, 300.0f), 30 }
{
  title.setPosition(50.0f, 50.0f); 
}

void MainMenu::mouseInput(GameState& state, sf::RenderWindow& window)
{
  sf::Vector2i clickPosition{ sf::Mouse::getPosition(window) };

  if(startButton.isClicked(clickPosition)) 
  {
    state = GameState::gameSettings;
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
  window.clear();
  window.draw(title);
  startButton.draw(window);
  optionsButton.draw(window);
  creditsButton.draw(window);
  exitButton.draw(window);
  window.display();
}
