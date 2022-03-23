#include "mainmenu.h"
#include "gamestate.h"
#include "textbutton.h"
#include <SFML/Graphics.hpp>

MainMenu::MainMenu(sf::Font& buttonFont)
  : startButton(buttonFont, "start", sf::Vector2f(50.0f, 50.0f), 30)
{
  
}

void MainMenu::mouseInput(GameState& state, sf::RenderWindow& window)
{
  sf::Vector2i clickPosition{ sf::Mouse::getPosition(window) };

  if(startButton.isClicked(clickPosition)) 
  {
    state = GameState::gameSettings;
  }
}

void MainMenu::run(sf::RenderWindow& window)
{
  window.clear();
  startButton.draw(window);
  window.display();
}
