#include "gamesettings.h"
#include "textbutton.h"
#include "gamestate.h"
#include <SFML/Graphics.hpp>
#include <string>

GameSettings::GameSettings(sf::Font& buttonFont)
  : startButton{ buttonFont, "start", sf::Vector2f(1720.0f, 980.0f), 32 },
    backButton{ buttonFont, "back", sf::Vector2f(50.0f, 980.0f), 32 },
    mapWidth{ buttonFont, "30", 24, sf::Vector2f(1000.0f, 50.0f) },
    mapHeight{ buttonFont, "20", 24, sf::Vector2f(1000.0f, 100.0f) },
    landmassCount{ buttonFont, "3", 24, sf::Vector2f(1000.0f, 150.0f) },
    landmassSize{ buttonFont, "6", 24, sf::Vector2f(1000.f, 200.0f) },
    landToWaterChance{ buttonFont, "0.4", 24, sf::Vector2f(1000.0f, 250.0f) },
    waterToLandChance{ buttonFont, "0.4", 24, sf::Vector2f(1000.0f, 300.0f) },
    mountainRangeMaxLenght{ buttonFont, "2", 24, sf::Vector2f(1000.0f, 350.0f) },
    mountainRangeCount{ buttonFont, "5", 24, sf::Vector2f(1000.0f, 400.0f) },
    firstPassHillChance{ buttonFont, "0.25", 24, sf::Vector2f(1000.0f, 450.0f) },
    secondPassHillChance{ buttonFont, "0.25", 24, sf::Vector2f(1000.0f, 500.0f) },
    forestChance{ buttonFont, "0.25", 24, sf::Vector2f(1000.0f, 550.0f) },
    riverChance{ buttonFont, "0.02", 24, sf::Vector2f(1000.0f, 600.0f) },
    mapWidthLabel{ "Map width", buttonFont, 24 },
    mapHeightLabel{ "Map height", buttonFont, 24 },
    landmassCountLabel{ "Landmasses / 100 nodes", buttonFont, 24 },
    landmassSizeLabel{ "Landmass max size", buttonFont, 24 },
    landToWaterChanceLabel{ "Land to water transition chance", buttonFont, 24 },
    waterToLandChanceLabel{ "Water to land transition chance", buttonFont, 24 },
    mountainRangeMaxLenghtLabel{ "Mountain range max lenght", buttonFont, 24 },
    mountainRangeCountLabel{ "Mountain ranges / 100 nodes", buttonFont, 24 },
    firstPassHillChanceLabel{ "Chance for hills next to mountains", buttonFont, 24 },
    secondPassHillChanceLabel{ "Chance for hills next to other hills", buttonFont, 24 },
    forestChanceLabel{ "Chance for forest", buttonFont, 24 },
    riverChanceLabel{ "Chance for river source", buttonFont, 24 }
{
  mapWidthLabel.setPosition(sf::Vector2f(50.0f, 50.0f));
  mapHeightLabel.setPosition(sf::Vector2f(50.0f, 100.0f));
  landmassCountLabel.setPosition(sf::Vector2f(50.0f, 150.0f));
  landmassSizeLabel.setPosition(sf::Vector2f(50.0f, 200.0f));
  landToWaterChanceLabel.setPosition(sf::Vector2f(50.0f, 250.0f));;
  waterToLandChanceLabel.setPosition(sf::Vector2f(50.0f, 300.0f));;
  mountainRangeMaxLenghtLabel.setPosition(sf::Vector2f(50.0f, 350.0f));;
  mountainRangeCountLabel.setPosition(sf::Vector2f(50.0f, 400.0f));;
  firstPassHillChanceLabel.setPosition(sf::Vector2f(50.0f, 450.0f));;
  secondPassHillChanceLabel.setPosition(sf::Vector2f(50.0f, 500.0f));;
  forestChanceLabel.setPosition(sf::Vector2f(50.0f, 550.0f));;
  riverChanceLabel.setPosition(sf::Vector2f(50.0f, 600.0f));;
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
    landToWaterChance.active = false;
    waterToLandChance.active = false;
    mountainRangeMaxLenght.active = false;
    mountainRangeCount.active = false;
    firstPassHillChance.active = false;
    secondPassHillChance.active = false;
    forestChance.active = false;
    riverChance.active = false;
  }
  else if(mapHeight.isClicked(clickPosition))
  {
    mapWidth.active = false;
    mapHeight.active = true;
    landmassCount.active = false;
    landmassSize.active = false;
    landToWaterChance.active = false;
    waterToLandChance.active = false;
    mountainRangeMaxLenght.active = false;
    mountainRangeCount.active = false;
    firstPassHillChance.active = false;
    secondPassHillChance.active = false;
    forestChance.active = false;
    riverChance.active = false;
  }
  else if(landmassCount.isClicked(clickPosition))
  {
    mapWidth.active = false;
    mapHeight.active = false;
    landmassCount.active = true;
    landmassSize.active = false;
    landToWaterChance.active = false;
    waterToLandChance.active = false;
    mountainRangeMaxLenght.active = false;
    mountainRangeCount.active = false;
    firstPassHillChance.active = false;
    secondPassHillChance.active = false;
    forestChance.active = false;
    riverChance.active = false;
  }
  else if(landmassSize.isClicked(clickPosition))
  {
    mapWidth.active = false;
    mapHeight.active = false;
    landmassCount.active = false;
    landmassSize.active = true;
    landToWaterChance.active = false;
    waterToLandChance.active = false;
    mountainRangeMaxLenght.active = false;
    mountainRangeCount.active = false;
    firstPassHillChance.active = false;
    secondPassHillChance.active = false;
    forestChance.active = false;
    riverChance.active = false;
  }
  else if(landToWaterChance.isClicked(clickPosition))
  {
    mapHeight.active = false;
    mapWidth.active = false;
    landmassCount.active = false;
    landmassSize.active = false;
    landToWaterChance.active = true;
    waterToLandChance.active = false;
    mountainRangeMaxLenght.active = false;
    mountainRangeCount.active = false;
    firstPassHillChance.active = false;
    secondPassHillChance.active = false;
    forestChance.active = false;
    riverChance.active = false;
  }
  else if(waterToLandChance.isClicked(clickPosition))
  {
    mapHeight.active = false;
    mapWidth.active = false;
    landmassCount.active = false;
    landmassSize.active = false;
    landToWaterChance.active = false;
    waterToLandChance.active = true;
    mountainRangeMaxLenght.active = false;
    mountainRangeCount.active = false;
    firstPassHillChance.active = false;
    secondPassHillChance.active = false;
    forestChance.active = false;
    riverChance.active = false;
  }
  else if(mountainRangeMaxLenght.isClicked(clickPosition))
  {
    mapHeight.active = false;
    mapWidth.active = false;
    landmassCount.active = false;
    landmassSize.active = false;
    landToWaterChance.active = false;
    waterToLandChance.active = false;
    mountainRangeMaxLenght.active = true;
    mountainRangeCount.active = false;
    firstPassHillChance.active = false;
    secondPassHillChance.active = false;
    forestChance.active = false;
    riverChance.active = false;
  }
  else if(mountainRangeCount.isClicked(clickPosition))
  {
    mapHeight.active = false;
    mapWidth.active = false;
    landmassCount.active = false;
    landmassSize.active = false;
    landToWaterChance.active = false;
    waterToLandChance.active = false;
    mountainRangeMaxLenght.active = false;
    mountainRangeCount.active = true;
    firstPassHillChance.active = false;
    secondPassHillChance.active = false;
    forestChance.active = false;
    riverChance.active = false;
  }
  else if(firstPassHillChance.isClicked(clickPosition))
  {
    mapHeight.active = false;
    mapWidth.active = false;
    landmassCount.active = false;
    landmassSize.active = false;
    landToWaterChance.active = false;
    waterToLandChance.active = false;
    mountainRangeMaxLenght.active = false;
    mountainRangeCount.active = false;
    firstPassHillChance.active = true;
    secondPassHillChance.active = false;
    forestChance.active = false;
    riverChance.active = false;
  }
  else if(secondPassHillChance.isClicked(clickPosition))
  {
    mapHeight.active = false;
    mapWidth.active = false;
    landmassCount.active = false;
    landmassSize.active = false;
    landToWaterChance.active = false;
    waterToLandChance.active = false;
    mountainRangeMaxLenght.active = false;
    mountainRangeCount.active = false;
    firstPassHillChance.active = false;
    secondPassHillChance.active = true;
    forestChance.active = false;
    riverChance.active = false;
  }
  else if(forestChance.isClicked(clickPosition))
  {
    mapHeight.active = false;
    mapWidth.active = false;
    landmassCount.active = false;
    landmassSize.active = false;
    landToWaterChance.active = false;
    waterToLandChance.active = false;
    mountainRangeMaxLenght.active = false;
    mountainRangeCount.active = false;
    firstPassHillChance.active = false;
    secondPassHillChance.active = false;
    forestChance.active = true;
    riverChance.active = false;
  }
  else if(riverChance.isClicked(clickPosition))
  {
    mapHeight.active = false;
    mapWidth.active = false;
    landmassCount.active = false;
    landmassSize.active = false;
    landToWaterChance.active = false;
    waterToLandChance.active = false;
    mountainRangeMaxLenght.active = false;
    mountainRangeCount.active = false;
    firstPassHillChance.active = false;
    secondPassHillChance.active = false;
    forestChance.active = false;
    riverChance.active = true;
  }
  else
  {
    mapWidth.active = false;
    mapHeight.active = false;
    landmassCount.active = false;
    landmassSize.active = false;
    landToWaterChance.active = false;
    waterToLandChance.active = false;
    mountainRangeMaxLenght.active = false;
    mountainRangeCount.active = false;
    firstPassHillChance.active = false;
    secondPassHillChance.active = false;
    forestChance.active = false;
    riverChance.active = false;
  }

}

void GameSettings::textInput(char input)
{
  mapWidth.updateText(input);
  mapHeight.updateText(input);
  landmassCount.updateText(input);
  landmassSize.updateText(input);
  landToWaterChance.updateText(input);
  waterToLandChance.updateText(input);
  mountainRangeMaxLenght.updateText(input);
  mountainRangeCount.updateText(input);
  firstPassHillChance.updateText(input);
  secondPassHillChance.updateText(input);
  forestChance.updateText(input);
  riverChance.updateText(input);
}

void GameSettings::run(sf::RenderWindow& window)
{
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
  {
    mapWidth.active = false;
    mapHeight.active = false;
    landmassCount.active = false;
    landmassSize.active = false;
    landToWaterChance.active = false;
    waterToLandChance.active = false;
    mountainRangeMaxLenght.active = false;
    mountainRangeCount.active = false;
    firstPassHillChance.active = false;
    secondPassHillChance.active = false;
    forestChance.active = false;
    riverChance.active = false;
  }

  startButton.draw(window);
  backButton.draw(window);
  mapWidth.draw(window);
  mapHeight.draw(window);
  landToWaterChance.draw(window);
  waterToLandChance.draw(window);
  mountainRangeMaxLenght.draw(window);
  mountainRangeCount.draw(window);
  firstPassHillChance.draw(window);
  secondPassHillChance.draw(window);
  forestChance.draw(window);
  riverChance.draw(window);
  landmassCount.draw(window);
  landmassSize.draw(window);
  window.draw(mapWidthLabel);
  window.draw(mapHeightLabel);
  window.draw(landmassCountLabel);
  window.draw(landmassSizeLabel);
  window.draw(landToWaterChanceLabel);
  window.draw(waterToLandChanceLabel);
  window.draw(mountainRangeMaxLenghtLabel);
  window.draw(mountainRangeCountLabel);
  window.draw(firstPassHillChanceLabel);
  window.draw(secondPassHillChanceLabel);
  window.draw(forestChanceLabel);
  window.draw(riverChanceLabel);
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
      
double GameSettings::getLandToWaterChance()
{
  return std::stod(landToWaterChance.getText());
}

double GameSettings::getWaterToLandChance()
{
  return std::stod(waterToLandChance.getText());

}

int GameSettings::getMountainRangeMaxLenght()
{
  return std::stoi(mountainRangeMaxLenght.getText());

}

int GameSettings::getMountainRangeCount()
{
  return std::stoi(mountainRangeCount.getText());

}

double GameSettings::getFirstPassHillChance()
{
  return std::stod(firstPassHillChance.getText());

}

double GameSettings::getSecondPassHillChance()
{

  return std::stod(secondPassHillChance.getText());
}

double GameSettings::getForestChance()
{
  return std::stod(forestChance.getText());

}

double GameSettings::getRiverChance()
{
  return std::stod(riverChance.getText());

}
