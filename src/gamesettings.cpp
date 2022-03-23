#include "gamesettings.h"
#include "textbutton.h"
#include "gamestate.h"
#include <SFML/Graphics.hpp>
#include <string>

GameSettings::GameSettings(sf::Font& buttonFont)
  : startButton(buttonFont, "start", sf::Vector2f(50.0f, 500.0f), 30)
{
  
}

void GameSettings::mouseInput(GameState& state, sf::RenderWindow& window)
{
  sf::Vector2i clickPosition{ sf::Mouse::getPosition(window) };

  if(startButton.isClicked(clickPosition))
  {
    state = GameState::game;
  }
}

void GameSettings::run(sf::RenderWindow& window)
{
  window.clear();
  startButton.draw(window);
  window.display();
}
