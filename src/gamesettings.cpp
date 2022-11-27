#include "gamesettings.h"
#include "textbutton.h"
#include "gamestate.h"
#include <SFML/Graphics.hpp>
#include <string>

GameSettings::GameSettings(sf::Font& buttonFont, GameState& state)
  : startButton{ buttonFont, "start", 32, &screen },
    backButton{ buttonFont, "back", 32, &screen },
    mapWidthLabel{ buttonFont, "Map width", 24, &screen },
    mapHeightLabel{ buttonFont, "Map height", 24, &screen },
    landmassCountLabel{ buttonFont, "Landmasses / 100 nodes", 24, &screen },
    landmassSizeLabel{ buttonFont, "Landmass max size", 24, &screen },
    landToWaterChanceLabel{ buttonFont, "Land to water transition chance", 24, &screen },
    waterToLandChanceLabel{ buttonFont, "Water to land transition chance", 24, &screen },
    mountainRangeMaxLenghtLabel{ buttonFont, "Mountain range max lenght", 24, &screen },
    mountainRangeCountLabel{ buttonFont, "Mountain ranges / 100 nodes", 24, &screen },
    firstPassHillChanceLabel{ buttonFont, "Chance for hills next to mountains", 24, &screen },
    secondPassHillChanceLabel{ buttonFont, "Chance for hills next to other hills", 24, &screen },
    forestChanceLabel{ buttonFont, "Chance for forest", 24, &screen },
    riverChanceLabel{ buttonFont, "Chance for river source", 24, &screen }
  /*: startButton{ buttonFont, "start", sf::Vector2f(1720.0f, 980.0f), 32 },
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
    riverChanceLabel{ "Chance for river source", buttonFont, 24 }*/
{
  startButton.positionAtBottom(100);
  startButton.positionAtRight(100);
  startButton.setFlag(GUIFlag::clickable);
  startButton.setFunction([&state, this](){
    if(this->canProceed)
    {
      state = GameState::game;
    }
      });

  backButton.positionAtBottom(100);
  backButton.positionAtLeft(100);
  backButton.setFlag(GUIFlag::clickable);
  backButton.setFunction([&state](){
        state = GameState::mainMenu;
      });

  inputs.emplace_back(buttonFont, "30", 
                      24, &screen);  //Map width
  inputs.emplace_back(buttonFont, "20", 
                      24, &screen);  //Map height
  inputs.emplace_back(buttonFont, "3", 
                      24, &screen);  //Landmass count
  inputs.emplace_back(buttonFont, "6", 
                      24, &screen);  //Landmass size
  inputs.emplace_back(buttonFont, "0.4", 
                      24, &screen);  //LtW chance
  inputs.emplace_back(buttonFont, "0.4", 
                      24, &screen);  //WtL chance
  inputs.emplace_back(buttonFont, "2", 
                      24, &screen);  //Moun. range lenght
  inputs.emplace_back(buttonFont, "5", 
                      24, &screen);  //Moun. range count
  inputs.emplace_back(buttonFont, "0.25", 
                      24, &screen);  //1st pass hill chance
  inputs.emplace_back(buttonFont, "0.25", 
                      24, &screen);  //2nd pass hill chance
  inputs.emplace_back(buttonFont, "0.25", 
                      24, &screen);  //Forest chance
  inputs.emplace_back(buttonFont, "0.02", 
                      24, &screen);  //River chance 

  inputs.at(0).positionAtTop(50);
  inputs.at(0).positionAtLeft(1000);
  inputs.at(0).setType(GUITextInputType::numeric);
  for(std::size_t iii{ 1 }; iii < inputs.size(); ++iii)
  {
    inputs.at(iii).positionAtLeft(1000);
    inputs.at(iii).positionDownTo(&inputs.at(iii - 1), 50);
    inputs.at(iii).setType(GUITextInputType::numeric);
  }

  mapWidthLabel.positionAtLeft(50);
  mapWidthLabel.positionAtTop(50);

  mapHeightLabel.positionAtLeft(50);
  mapHeightLabel.positionDownTo(&mapWidthLabel, 50);

  landmassCountLabel.positionAtLeft(50);
  landmassCountLabel.positionDownTo(&mapHeightLabel, 50);

  landmassSizeLabel.positionAtLeft(50);
  landmassSizeLabel.positionDownTo(&landmassCountLabel, 50);

  landToWaterChanceLabel.positionAtLeft(50);
  landToWaterChanceLabel.positionDownTo(&landmassSizeLabel, 50);

  waterToLandChanceLabel.positionAtLeft(50);
  waterToLandChanceLabel.positionDownTo(&landToWaterChanceLabel, 50);

  mountainRangeMaxLenghtLabel.positionAtLeft(50);
  mountainRangeMaxLenghtLabel.positionDownTo(&waterToLandChanceLabel, 50);

  mountainRangeCountLabel.positionAtLeft(50);
  mountainRangeCountLabel.positionDownTo(&mountainRangeMaxLenghtLabel, 50);

  firstPassHillChanceLabel.positionAtLeft(50);
  firstPassHillChanceLabel.positionDownTo(&mountainRangeCountLabel, 50);

  secondPassHillChanceLabel.positionAtLeft(50);
  secondPassHillChanceLabel.positionDownTo(&firstPassHillChanceLabel, 50);

  forestChanceLabel.positionAtLeft(50);
  forestChanceLabel.positionDownTo(&secondPassHillChanceLabel, 50);

  riverChanceLabel.positionAtLeft(50);
  riverChanceLabel.positionDownTo(&forestChanceLabel, 50);

  /*mapWidthLabel.setPosition(sf::Vector2f(50.0f, 50.0f));
  mapHeightLabel.setPosition(sf::Vector2f(50.0f, 100.0f));
  landmassCountLabel.setPosition(sf::Vector2f(50.0f, 150.0f));
  landmassSizeLabel.setPosition(sf::Vector2f(50.0f, 200.0f));
  landToWaterChanceLabel.setPosition(sf::Vector2f(50.0f, 250.0f));;
  waterToLandChanceLabel.setPosition(sf::Vector2f(50.0f, 300.0f));;
  mountainRangeMaxLenghtLabel.setPosition(sf::Vector2f(50.0f, 350.0f));;
  mountainRangeCountLabel.setPosition(sf::Vector2f(50.0f, 400.0f));;
  firstPassHillChanceLabel.setPosition(sf::Vector2f(50.0f, 450.0f));;
  secondPassHillChanceLabel.setPosition(sf::Vector2f(50.0f, 500.0f));
  forestChanceLabel.setPosition(sf::Vector2f(50.0f, 550.0f));;
  riverChanceLabel.setPosition(sf::Vector2f(50.0f, 600.0f));;*/
}

void GameSettings::mouseInput(GameState& state, sf::Vector2i clickPosition)
{
  backButton.clickInput(clickPosition);
  startButton.clickInput(clickPosition);

  /*if(startButton.isClicked(clickPosition))
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
      startButton.positionAtRight(100);
      //startButton.setPosition(sf::Vector2f(1200.0f, 980.0f));
    }
  }*/
  /*else if(backButton.isClicked(clickPosition))
  {
    state = GameState::mainMenu;
  }*/
  //else
  //{
    for(std::size_t iii{ 0 }; iii < inputs.size(); ++iii)
    {
      inputs.at(iii).clickInput(clickPosition);
     
      //if(inputs.at(iii).isActive())
      if(inputs.at(iii).active)
      {
        activeInputId = iii;
        break;
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
  //}
}

void GameSettings::textInput(char input)
{
  for(auto& inputField : inputs)
  {
    //inputField.updateText(input);
    inputField.textEnteredInput(input);
  }
}
      
void GameSettings::arrowUpPressed()
{
  --activeInputId;
  for(auto& input : inputs)
  {
    //input.deactivate();
    input.active = false;
  }
  inputs.at(activeInputId).active = true;
  //inputs.at(activeInputId).activate();
}

void GameSettings::arrowRightPressed()
{
  ++activeInputId;
  for(auto& input : inputs)
  {
    //input.deactivate();
    input.active = false;
  }
  inputs.at(activeInputId).active = true;
  //inputs.at(activeInputId).activate();
}

void GameSettings::arrowDownPressed()
{
  ++activeInputId;
  for(auto& input : inputs)
  {
    //input.deactivate();
    input.active = false;
  }
  inputs.at(activeInputId).active = true;
  //inputs.at(activeInputId).activate();
}

void GameSettings::arrowLeftPressed()
{
  --activeInputId;
  for(auto& input : inputs)
  {
    //input.deactivate();
    input.active = false;
  }
  inputs.at(activeInputId).active = true;
  //inputs.at(activeInputId).activate();
}

void GameSettings::run(sf::RenderWindow& window)
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
    startButton.positionAtRight(100);
  }
  else
  {
    startButton.setText("fill all input fields");
    startButton.positionAtRight(100);
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)
  || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
  {
    for(auto& inputField : inputs)
    {
      //inputField.deactivate();
      inputField.active = false;
    }
  }

  startButton.draw(window);
  backButton.draw(window);
  for(auto& inputField : inputs)
  {
    inputField.draw(window);
  }
  mapWidthLabel.draw(window);
  mapHeightLabel.draw(window);
  landmassCountLabel.draw(window);
  landmassSizeLabel.draw(window);
  landToWaterChanceLabel.draw(window);
  waterToLandChanceLabel.draw(window);
  mountainRangeMaxLenghtLabel.draw(window);
  mountainRangeCountLabel.draw(window);
  firstPassHillChanceLabel.draw(window);
  secondPassHillChanceLabel.draw(window);
  forestChanceLabel.draw(window);
  riverChanceLabel.draw(window);
  /*window.draw(mapWidthLabel);
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
  window.draw(riverChanceLabel);*/
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
