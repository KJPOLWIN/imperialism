#include "gamesettings.h"
#include "textbutton.h"
#include "gamestate.h"
#include <SFML/Graphics.hpp>
#include <string>

GameSettings::GameSettings(sf::Font& buttonFont)
  : startButton{ buttonFont, "start", sf::Vector2f(1720.0f, 980.0f), 32 },
    backButton{ buttonFont, "back", sf::Vector2f(50.0f, 980.0f), 32 },
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
  inputs.emplace_back(buttonFont, "30", 
                      24, sf::Vector2f(1000.0f, 50.0f));  //Map width
  inputs.emplace_back(buttonFont, "20", 
                      24, sf::Vector2f(1000.0f, 100.0f));  //Map height
  inputs.emplace_back(buttonFont, "3", 
                      24, sf::Vector2f(1000.0f, 150.0f));  //Landmass count
  inputs.emplace_back(buttonFont, "6", 
                      24, sf::Vector2f(1000.f, 200.0f));  //Landmass size
  inputs.emplace_back(buttonFont, "0.4", 
                      24, sf::Vector2f(1000.0f, 250.0f));  //LtW chance
  inputs.emplace_back(buttonFont, "0.4", 
                      24, sf::Vector2f(1000.0f, 300.0f));  //WtL chance
  inputs.emplace_back(buttonFont, "2", 
                      24, sf::Vector2f(1000.0f, 350.0f));  //Moun. range lenght
  inputs.emplace_back(buttonFont, "5", 
                      24, sf::Vector2f(1000.0f, 400.0f));  //Moun. range count
  inputs.emplace_back(buttonFont, "0.25", 
                      24, sf::Vector2f(1000.0f, 450.0f));  //1st pass hill chance
  inputs.emplace_back(buttonFont, "0.25", 
                      24, sf::Vector2f(1000.0f, 500.0f));  //2nd pass hill chance
  inputs.emplace_back(buttonFont, "0.25", 
                      24, sf::Vector2f(1000.0f, 550.0f));  //Forest chance
  inputs.emplace_back(buttonFont, "0.02", 
                      24, sf::Vector2f(1000.0f, 600.0f));  //River chance 

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

void GameSettings::mouseInput(GameState& state, sf::Vector2i clickPosition)
{
  if(startButton.isClicked(clickPosition))
  {
    for(auto& input : inputs)
    {
      if(input.getText() == "")
      {
        canProceed = false;
        break;
      }
    }

    if(canProceed)
    {
      state = GameState::game;
    }
    else
    {
      startButton.setText("Fill all input fields");
      startButton.setPosition(1200.0f, 980.0f);
    }
  }
  else if(backButton.isClicked(clickPosition))
  {
    state = GameState::mainMenu;
  }
  else
  {
    bool anyInputActive{ false };
    for(std::size_t iii{ 0 }; iii < inputs.size(); ++iii)
    {
      inputs.at(iii).clickInput(clickPosition);
      if(inputs.at(iii).isActive())
      {
        anyInputActive = true;
        activeInputId = iii;
      }

      /*if(inputs.at(iii).isClicked(clickPosition)
      && !anyInputActive)
      {
        inputs.at(iii).active = true;
        anyInputActive = true;
        activeInputId = iii;
      }
      else
      {
        inputs.at(iii).active = false;
      }*/
    }
  }
}

void GameSettings::textInput(char input)
{
  for(auto& inputField : inputs)
  {
    inputField.updateText(input);
  }
}
      
void GameSettings::arrowUpPressed()
{
  --activeInputId;
  for(auto& input : inputs)
  {
    input.deactivate();
  }
  inputs.at(activeInputId).activate();
}

void GameSettings::arrowRightPressed()
{
  ++activeInputId;
  for(auto& input : inputs)
  {
    input.deactivate();
  }
  inputs.at(activeInputId).activate();
}

void GameSettings::arrowDownPressed()
{
  ++activeInputId;
  for(auto& input : inputs)
  {
    input.deactivate();
  }
  inputs.at(activeInputId).activate();
}

void GameSettings::arrowLeftPressed()
{
  --activeInputId;
  for(auto& input : inputs)
  {
    input.deactivate();
  }
  inputs.at(activeInputId).activate();
}

void GameSettings::run(sf::RenderWindow& window)
{
  if(!canProceed)
  {
    canProceed = true;
    for(auto& input : inputs)
    {
      if(input.getText() == "")
      {
        canProceed = false;
        break;
      }
    }

    if(canProceed)
    {
      startButton.setText("start");
      startButton.setPosition(1720.0f, 980.0f);
    }
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)
  || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
  {
    for(auto& inputField : inputs)
    {
      inputField.deactivate();
    }
  }

  startButton.draw(window);
  backButton.draw(window);
  for(auto& inputField : inputs)
  {
    inputField.draw(window);
  }
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
  return std::stoi(inputs.at(0).getText());
}

int GameSettings::getMapHeight()
{
  return std::stoi(inputs.at(1).getText());
}

int GameSettings::getLandmassCount()
{
  return std::stoi(inputs.at(2).getText());
}

int GameSettings::getLandmassSize()
{
  return std::stoi(inputs.at(3).getText());
}
      
double GameSettings::getLandToWaterChance()
{
  return std::stod(inputs.at(4).getText());
}

double GameSettings::getWaterToLandChance()
{
  return std::stod(inputs.at(5).getText());
}

int GameSettings::getMountainRangeMaxLenght()
{
  return std::stoi(inputs.at(6).getText());
}

int GameSettings::getMountainRangeCount()
{
  return std::stoi(inputs.at(7).getText());
}

double GameSettings::getFirstPassHillChance()
{
  return std::stod(inputs.at(8).getText());
}

double GameSettings::getSecondPassHillChance()
{
  return std::stod(inputs.at(9).getText());
}

double GameSettings::getForestChance()
{
  return std::stod(inputs.at(10).getText());
}

double GameSettings::getRiverChance()
{
  return std::stod(inputs.at(11).getText());
}
