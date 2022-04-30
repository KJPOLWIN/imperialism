#include "gamesettings.h"
#include "textbutton.h"
#include "gamestate.h"
#include <SFML/Graphics.hpp>
#include <string>

GameSettings::GameSettings(sf::Font& buttonFont)
  : startButton{ buttonFont, "start", sf::Vector2f(1720.0f, 980.0f), 32 },
    backButton{ buttonFont, "back", sf::Vector2f(50.0f, 980.0f), 32 },
    mapWidth{ buttonFont, "30", 24, sf::Vector2f(600.0f, 50.0f) },
    mapHeight{ buttonFont, "20", 24, sf::Vector2f(600.0f, 100.0f) },
    landmassCount{ buttonFont, "3", 24, sf::Vector2f(600.0f, 150.0f) },
    landmassSize{ buttonFont, "6", 24, sf::Vector2f(600.f, 200.0f) },
    mapWidthLabel{ "Map width", buttonFont, 24 },
    mapHeightLabel{ "Map height", buttonFont, 24 },
    landmassCountLabel{ "Landmasses/100 nodes", buttonFont, 24 },
    landmassSizeLabel{ "Landmass max size", buttonFont, 24 }
{
  mapWidthLabel.setPosition(sf::Vector2f(50.0f, 50.0f));
  mapHeightLabel.setPosition(sf::Vector2f(50.0f, 100.0f));
  landmassCountLabel.setPosition(sf::Vector2f(50.0f, 150.0f));
  landmassSizeLabel.setPosition(sf::Vector2f(50.0f, 200.0f));
}

void GameSettings::mouseInput(GameState& state, sf::RenderWindow& window, sf::Vector2i clickPosition)
{
  if(startButton.isClicked(clickPosition))
  {
    state = GameState::game;
  }
  else if(backButton.isClicked(clickPosition))
  {
    state = GameState::mainMenu;
  }
  else if(mapWidth.isClicked(clickPosition))
  {
    mapWidth.active = true;
    mapHeight.active = false;
    landmassCount.active = false;
    landmassSize.active = false;
  }
  else if(mapHeight.isClicked(clickPosition))
  {
    mapHeight.active = true;
    mapWidth.active = false;
    landmassCount.active = false;
    landmassSize.active = false;
  }
  else if(landmassCount.isClicked(clickPosition))
  {
    landmassCount.active = true;
    mapHeight.active = false;
    mapWidth.active = false;
    landmassSize.active = false;
  }
  else if(landmassSize.isClicked(clickPosition))
  {
    landmassSize.active = true;
    mapHeight.active = false;
    mapWidth.active = false;
    landmassCount.active = false;
  }
  else
  {
    mapWidth.active = false;
    mapHeight.active = false;
    landmassCount.active = false;
    landmassSize.active = false;
  }

}

void GameSettings::textInput(char input)
{
  mapWidth.updateText(input);
  mapHeight.updateText(input);
  landmassCount.updateText(input);
  landmassSize.updateText(input);
}

void GameSettings::run(sf::RenderWindow& window)
{
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
  {
    mapWidth.active = false;
    mapHeight.active = false;
    landmassCount.active = false;
    landmassSize.active = false;
  }

  startButton.draw(window);
  backButton.draw(window);
  mapWidth.draw(window);
  mapHeight.draw(window);
  landmassCount.draw(window);
  landmassSize.draw(window);
  window.draw(mapWidthLabel);
  window.draw(mapHeightLabel);
  window.draw(landmassCountLabel);
  window.draw(landmassSizeLabel);
}
      
int GameSettings::getMapWidth()
{
  return std::stoi(mapWidth.getText());
}

int GameSettings::getMapHeight()
{
  return std::stoi(mapHeight.getText());
}

int GameSettings::getLandmassCount()
{
  return std::stoi(landmassCount.getText());
}

int GameSettings::getLandmassSize()
{
  return std::stoi(landmassSize.getText());
}
