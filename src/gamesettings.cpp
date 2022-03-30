#include "gamesettings.h"
#include "textbutton.h"
#include "gamestate.h"
#include <SFML/Graphics.hpp>
#include <string>

GameSettings::GameSettings(sf::Font& buttonFont)
  : startButton(buttonFont, "start", sf::Vector2f(50.0f, 500.0f), 30),
    mapWidth(buttonFont, "8", 30, sf::Vector2f(50.0f, 50.0f)),
    mapHeight(buttonFont, "7", 30, sf::Vector2f(50.0f, 100.0f))
{
  
}

void GameSettings::mouseInput(GameState& state, sf::RenderWindow& window)
{
  sf::Vector2i clickPosition{ sf::Mouse::getPosition(window) };

  if(startButton.isClicked(clickPosition))
  {
    state = GameState::game;
  }
  else if(mapWidth.isClicked(clickPosition))
  {
    mapWidth.active = true;
    mapHeight.active = false;
  }
  else if(mapHeight.isClicked(clickPosition))
  {
    mapHeight.active = true;
    mapWidth.active = false;
  }
  else
  {
    mapWidth.active = false;
    mapHeight.active = false;
  }

}

void GameSettings::textInput(char input)
{
  mapWidth.updateText(input);
  mapHeight.updateText(input);
}

void GameSettings::run(sf::RenderWindow& window)
{
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
  {
    mapWidth.active = false;
    mapHeight.active = false;
  }

  window.clear();
  startButton.draw(window);
  mapWidth.draw(window);
  mapHeight.draw(window);
  window.display();
}
      
int GameSettings::getMapWidth()
{
  return std::stoi(mapWidth.getText());
}

int GameSettings::getMapHeight()
{
  return std::stoi(mapHeight.getText());
}
