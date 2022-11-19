#include "game.h"
#include "map.h"
#include "textbutton.h"
#include "imagebutton.h"
#include "faction.h"
#include "gamestate.h"
#include "gui.h"
#include "constant.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <dirent.h>

  #include <iostream>

Game::Game(sf::Font& font)
  : pauseMenuLabel{ "Game paused", font, 32 },
    menuButton{ font, "Main menu", sf::Vector2f(300, 375), 24 },
    optionsButton{ font, "Options", sf::Vector2f(300, 425), 24 },
    saveGameButton{ font, "Save game", sf::Vector2f(300, 475), 24 },
    exitToDesktopButton{ font, "Exit to desktop", sf::Vector2f(300, 800), 24 },
    pauseButton{ pauseButtonSprite.getSpritePointer(), sf::Vector2f(10, 10), sf::Vector2f(30, 32) },
    unpauseButton{ unpauseButtonSprite.getSpritePointer(), sf::Vector2f(10, 10), sf::Vector2f(30, 32) },
    nextTurnButton{ font, "Next turn", sf::Vector2f(1550, 950), 32 },
    backButton{ font, "back", sf::Vector2f(690, 790), 24 },
    saveButton{ font, "save", sf::Vector2f(1140, 790), 24 },
    saveSelect{ sf::Vector2f(690, 340), sf::Vector2f(550, 350), 50.0 },
    filenameInput{ font, "Enter save name", 24, sf::Vector2f(690, 270), InputType::text }
    /*turnCounter{"Turn 1", font, 24 },
    moneyCounter{"", font, 24 },
    foodCounter{"", font, 24 },
    woodCounter{"", font, 24 },
    stoneCounter{"", font, 24 },
    weaponsCounter{"", font, 24 }*/
{
  //Pause menu setup
  shadeTexture.loadFromFile("texture/shade.png");
  shade.setTexture(shadeTexture);
  /*pauseButtonTexture.loadFromFile("texture/pause.png");
  pauseButtonSprite.setTexture(pauseButtonTexture);
  unpauseButtonTexture.loadFromFile("texture/unpause.png");
  unpauseButtonSprite.setTexture(unpauseButtonTexture);*/
  pauseButtonSprite.load("texture/pause.png");
  unpauseButtonSprite.load("texture/unpause.png");

  pauseMenuBackground.setPosition(710, 250); 
  pauseMenuBackground.setFillColor(sf::Color::Black);
  pauseMenuBackground.setOutlineColor(sf::Color::White);
  pauseMenuBackground.setOutlineThickness(10);

  pauseMenuLabel.setPosition(0, 275);
  GUI::centerTextInField(pauseMenuLabel, pauseMenuBackground);
  GUI::centerTextInField(menuButton, pauseMenuBackground);
  GUI::centerTextInField(optionsButton, pauseMenuBackground);
  GUI::centerTextInField(saveGameButton, pauseMenuBackground);
  GUI::centerTextInField(exitToDesktopButton, pauseMenuBackground);

  //Node widget setup
  nodeWidget.positionAtTop(100);
  nodeWidget.positionAtRight(100);

  nodeName.setFont(font);
  nodeName.positionAtTop(25);

  nodeImage.positionDownTo(&nodeName, 50);
  
  seaTerrain.load("texture/terrainsea.png");
  tundraTerrain.load("texture/terraintundra.png");
  desertTerrain.load("texture/terraindesert.png");
  grasslandTerrain.load("texture/terraingrass.png");
  tundraHillsTerrain.load("texture/terraintundrahills.png");
  desertHillsTerrain.load("texture/terraindeserthills.png");
  grasslandHillsTerrain.load("texture/terraingrasshills.png");
  mountainsTerrain.load("texture/terrainmountains.png");
  forestTerrain.load("texture/terrainforest.png");
  rainforestTerrain.load("texture/terrainrainforest.png");
  forestHillsTerrain.load("texture/terrainforesthills.png");
  rainforestHillsTerrain.load("texture/terrainrainforesthills.png");
  tundraRiverTerrain.load("texture/terraintundrariver.png");
  desertRiverTerrain.load("texture/terraindesertriver.png");
  grasslandRiverTerrain.load("texture/terraingrassriver.png");

  //Building widget setup
  buildingWidget.positionAtRight(100);
  buildingWidget.positionDownTo(&nodeWidget, 100);

  buildingName.setFont(font);
  buildingName.positionAtTop(25);

  underConstructionLabel.setFont(font);
  underConstructionLabel.positionDownTo(&buildingName, 25);

  //Unit widget setup
  unitWidget.positionAtBottom(100);
  unitWidget.positionAtLeft(100);

  riflemenLarge.load("texture/riflemen_large.png");
  unitImage.setImage(&riflemenLarge);
  
  unitImage.positionAtTop(25);
  unitImage.positionAtLeft(25);

  unitName.setFont(font);
  unitName.positionAtTop(25);
  unitName.positionRightTo(&unitImage, 25);

  unitHealth.setFont(font);
  unitHealth.positionDownTo(&unitName, 50);
  unitHealth.positionRightTo(&unitImage, 25);

  unitMovePoints.setFont(font);
  unitMovePoints.positionDownTo(&unitHealth, 50);
  unitMovePoints.positionRightTo(&unitImage, 25);
  
  //Save menu setup
  saveMenuBackground.setPosition(660, 240);
  saveMenuBackground.setFillColor(sf::Color::Black);
  saveMenuBackground.setOutlineColor(sf::Color::White);
  saveMenuBackground.setOutlineThickness(10);

  //Yields widget setup
  yieldWidget.setPosition(sf::Vector2f(0, 0));

  moneyIconSprite.load("texture/iconmoney.png");
  foodIconSprite.load("texture/iconfood.png");
  woodIconSprite.load("texture/iconwood.png");
  stoneIconSprite.load("texture/iconstone.png");
  weaponsIconSprite.load("texture/iconweapons.png");

  turnCounter.setFont(font);
  turnCounter.setText("Turn 1");
  turnCounter.positionAtTop(14);
  turnCounter.positionAtLeft(70);
 
  moneyCounter.setFont(font);
  moneyCounter.setText(std::to_string(map.getFactions().at(0).getMoney()));
  moneyCounter.positionRightTo(&turnCounter, 70);
  moneyCounter.positionAtTop(14);

  moneyIcon.setImage(&moneyIconSprite);
  moneyIcon.positionRightTo(&moneyCounter, 10);
  moneyIcon.positionAtTop(10);

  foodCounter.setFont(font);
  foodCounter.setText(std::to_string(map.getFactions().at(0).getFood()));
  foodCounter.positionRightTo(&moneyIcon, 50);
  foodCounter.positionAtTop(14);

  foodIcon.setImage(&foodIconSprite);
  foodIcon.positionRightTo(&foodCounter, 10);
  foodIcon.positionAtTop(10);

  woodCounter.setFont(font);
  woodCounter.setText(std::to_string(map.getFactions().at(0).getWood()));
  woodCounter.positionRightTo(&foodIcon, 50);
  woodCounter.positionAtTop(14);

  woodIcon.setImage(&woodIconSprite);
  woodIcon.positionRightTo(&woodCounter, 10);
  woodIcon.positionAtTop(10);

  stoneCounter.setFont(font);
  stoneCounter.setText(std::to_string(map.getFactions().at(0).getStone()));
  stoneCounter.positionRightTo(&woodIcon, 50);
  stoneCounter.positionAtTop(14);

  stoneIcon.setImage(&stoneIconSprite);
  stoneIcon.positionRightTo(&stoneCounter, 10);
  stoneIcon.positionAtTop(10);

  weaponsCounter.setFont(font);
  weaponsCounter.setText(std::to_string(map.getFactions().at(0).getWeapons()));
  weaponsCounter.positionRightTo(&stoneIcon, 50);
  weaponsCounter.positionAtTop(14);

  weaponsIcon.setImage(&weaponsIconSprite);
  weaponsIcon.positionRightTo(&weaponsCounter, 10);
  weaponsIcon.positionAtTop(10);

  /*yieldWidgetBackground.setPosition(0, 0);
  yieldWidgetBackground.setFillColor(sf::Color::Black);
  yieldWidgetBackground.setOutlineColor(sf::Color::White);
  yieldWidgetBackground.setOutlineThickness(10); 
  turnCounter.setPosition(sf::Vector2f(70, 14));
  moneyIconTexture.loadFromFile("texture/iconmoney.png");
  foodIconTexture.loadFromFile("texture/iconfood.png");
  woodIconTexture.loadFromFile("texture/iconwood.png");
  stoneIconTexture.loadFromFile("texture/iconstone.png");
  weaponsIconTexture.loadFromFile("texture/iconweapons.png");
  moneyIcon.setTexture(moneyIconTexture);
  foodIcon.setTexture(foodIconTexture);
  woodIcon.setTexture(woodIconTexture);
  stoneIcon.setTexture(stoneIconTexture);
  weaponsIcon.setTexture(weaponsIconTexture);
  moneyCounter.setString(std::to_string(map.getFactions().at(0).getMoney()));
  foodCounter.setString(std::to_string(map.getFactions().at(0).getFood()));
  woodCounter.setString(std::to_string(map.getFactions().at(0).getWood()));
  stoneCounter.setString(std::to_string(map.getFactions().at(0).getStone()));
  weaponsCounter.setString(std::to_string(map.getFactions().at(0).getWeapons()));
  moneyIcon.setPosition(sf::Vector2f(250, 10));
  moneyCounter.setPosition(sf::Vector2f(290, 14));
  foodIcon.setPosition(sf::Vector2f(390, 10));
  foodCounter.setPosition(sf::Vector2f(430, 14));
  woodIcon.setPosition(sf::Vector2f(530, 10));
  woodCounter.setPosition(sf::Vector2f(570, 14));
  stoneIcon.setPosition(sf::Vector2f(670, 10));
  stoneCounter.setPosition(sf::Vector2f(710, 14));
  weaponsIcon.setPosition(sf::Vector2f(810, 10));
  weaponsCounter.setPosition(sf::Vector2f(850, 14));*/
}

void Game::mouseInput(GameState& state, sf::RenderWindow& window, sf::Vector2i clickPosition, sf::Font& font)
{
  switch(mode)
  {
    case DisplayMode::game:
      if(nextTurnButton.isClicked(clickPosition))
      {
        map.nextTurn();
        /*turnCounter.setString("Turn " + std::to_string(map.getTurn() + 1));
        moneyCounter.setString(std::to_string(map.getFactions().at(0).getMoney()));
        foodCounter.setString(std::to_string(map.getFactions().at(0).getFood()));
        woodCounter.setString(std::to_string(map.getFactions().at(0).getWood()));
        stoneCounter.setString(std::to_string(map.getFactions().at(0).getStone()));
        weaponsCounter.setString(std::to_string(map.getFactions().at(0).getWeapons()));*/
        turnCounter.setText("Turn " + std::to_string(map.getTurn() + 1));
        moneyCounter.setText(std::to_string(map.getFactions().at(0).getMoney()));
        foodCounter.setText(std::to_string(map.getFactions().at(0).getFood()));
        woodCounter.setText(std::to_string(map.getFactions().at(0).getWood()));
        stoneCounter.setText(std::to_string(map.getFactions().at(0).getStone()));
        weaponsCounter.setText(std::to_string(map.getFactions().at(0).getWeapons()));
      }
      else if(pauseButton.isClicked(clickPosition))
      {
        mode = DisplayMode::pauseMenu;
      }
      else
      {
        sf::Vector2i posCartesian{ 
          map.getClickedNode(
            window.mapPixelToCoords(sf::Mouse::getPosition(window)),    
                                    sf::Vector2f((mapView.getCenter().x 
                                    - mapView.getSize().x / 2), 
                                    (mapView.getCenter().y 
                                    - mapView.getSize().y / 2)),
                                    mapView.getSize().x 
                                    / Constant::windowWidth) };

        HexVector newPos{ posCartesian };
        map.moveUnits(newPos);

        map.selectNodesAndUnits(
          window.mapPixelToCoords(sf::Mouse::getPosition(window)), 
                                  sf::Vector2f((mapView.getCenter().x 
                                  - mapView.getSize().x / 2), 
                                  (mapView.getCenter().y 
                                  - mapView.getSize().y / 2)),
                                  mapView.getSize().x / Constant::windowWidth);

        nodeName.setText(map.getSelectedNodeName());
        nodeName.centerHorizontally();
        
        buildingName.setText(map.getSelectedBuilding().getName());
        buildingName.centerHorizontally();

        if(map.getSelectedBuilding().getFaction() == 0)
        {
          buildingName.setTextColor(sf::Color::Blue);
        }
        else
        {
          buildingName.setTextColor(sf::Color::Red);
        }
        
        if(!map.getSelectedBuilding().completed)
        {
          underConstructionLabel.setText("(under construction)");
          underConstructionLabel.centerHorizontally();
        }
        else
        {
          underConstructionLabel.setText("");
        }
        
        unitName.setText(map.getSelectedUnit().getName());

        if(map.getSelectedUnit().getFaction() == 0)
        {
          unitName.setTextColor(sf::Color::Blue);
        }
        else
        {
          unitName.setTextColor(sf::Color::Red);
        }
      }
    break;

    case DisplayMode::pauseMenu:
      if(menuButton.isClicked(clickPosition))
      {
        state = GameState::mainMenu;
        mode = DisplayMode::game;
      }
      else if(optionsButton.isClicked(clickPosition))
      {
        state = GameState::options;
      }
      else if(saveGameButton.isClicked(clickPosition))
      {
        mode = DisplayMode::saveMenu;

        //filename list is updated
        saveSelect.getButtons().clear();
        int buttonCounter{ 0 };

        DIR *dir;
        struct dirent *diread;
        if((dir = opendir("./saves")) != nullptr)
        {
          while((diread = readdir(dir)) != nullptr)
          {
            std::string filename{ diread->d_name };

            if(filename.at(0) != '.')
            {
              filename.erase(filename.begin(),
                             filename.begin() + filename.find_first_of("/") + 1);
              filename.erase(filename.begin() + filename.find_last_of("."),
                             filename.end());
              saveSelect.addButton(font, filename,
                                   sf::Vector2f(690, 340 + buttonCounter * 50.0f), 24);
              ++buttonCounter;
            }
          }
          closedir(dir);
        }
        else
        {
          perror("opendir");
          std::cout << "directory not opened or something\n";
        }
      }
      else if(unpauseButton.isClicked(clickPosition))
      {
        mode = DisplayMode::game;
      }
      else if(exitToDesktopButton.isClicked(clickPosition))
      {
        window.close();
      }
    break;

    case DisplayMode::saveMenu:
      if(backButton.isClicked(clickPosition))
      {
        mode = DisplayMode::pauseMenu;
      }
      else if(saveButton.isClicked(clickPosition))
      {
        if(filenameInput.getText() != "" 
        && filenameInput.getText() != "Enter save name")
        {
          saveButton.setPosition(1140, 790);
          saveButton.setText("save");
          
          //map is saved
          map.saveToFile("saves/" + filenameInput.getText() + ".json");
          
          mode = DisplayMode::pauseMenu;
          textInputUnclicked = true;
        }
        else
        {
          saveButton.setPosition(885, 790);
          saveButton.setText("choose filename");
        }
      }
      else
      {
        if(filenameInput.clickInput(clickPosition)
        && textInputUnclicked)
        {
          textInputUnclicked = false;
          filenameInput.setText("");
        }

        saveSelect.clickInput(clickPosition);

        for(auto& button : saveSelect.getButtons())
        {
          if(button.isClicked(clickPosition))
          {
            textInputUnclicked = true;
            filenameInput.setText(button.getText());
          }
        }
      }
    break;
  }
}

void Game::holdInput(sf::Vector2i clickPosition)
{
  saveSelect.holdInput(clickPosition);
}

void Game::scrollInput(double direction)
{
  if(mode == DisplayMode::game)
  {
    double zoomLevel{ mapView.getSize().x / Constant::windowWidth };
    if(direction > 0 && zoomLevel >= maxZoom)
    {
      mapView.zoom(0.5);
    }
    else if(direction < 0 && zoomLevel <= minZoom)
    { 
      mapView.zoom(2);
    }
  }
  else if(mode == DisplayMode::saveMenu)
  {
    saveSelect.scroll(direction);
  }
}

void Game::textInput(char input)
{
  if(mode == DisplayMode::saveMenu)
  {
    filenameInput.updateText(input);
  }
}

void Game::switchPause()
{
  if(mode == DisplayMode::game) 
  {
    mode = DisplayMode::pauseMenu;
  }
  else 
  {
    mode = DisplayMode::game;
  }
}

void Game::run(sf::RenderWindow& window, double timeElapsed)
{
  sf::Vector2i mousePosition{ sf::Mouse::getPosition(window) };

  const int scrollSensitivity{ 30 };
  double zoomLevel{ mapView.getSize().x / Constant::windowWidth };

  //Update
  switch(mode)
  {
    case DisplayMode::game:
      if(mousePosition.x < scrollSensitivity)
      {
        mapView.move(-Constant::scrollSpeed * timeElapsed * zoomLevel, 0);
      }
      else if(mousePosition.x > Constant::windowWidth - scrollSensitivity)
      {
        mapView.move(Constant::scrollSpeed * timeElapsed * zoomLevel, 0);
      }
  
      if(mousePosition.y < scrollSensitivity)
      {
        mapView.move(0.0, -Constant::scrollSpeed * timeElapsed * zoomLevel);
      }
      else if(mousePosition.y > Constant::windowHeight - scrollSensitivity)
      {
        mapView.move(0.0, Constant::scrollSpeed * timeElapsed * zoomLevel);
      }
    case DisplayMode::pauseMenu:
    case DisplayMode::saveMenu:
      
      unitHealth.setText("Health: "
                       + std::to_string(map.getSelectedUnit().getHealth()) 
                       + "/" 
                       + std::to_string(map.getSelectedUnit().getMaxHealth()));
      /*unitMovePoints.setString("Move points: "
                       + std::to_string(map.getSelectedUnit().getMovePoints()) 
                       + "/" 
                       + std::to_string(map.getSelectedUnit().getMaxMovePoints()));*/
      unitMovePoints.setText("Move points: "
                       + std::to_string(map.getSelectedUnit().getMovePoints()) 
                       + "/" 
                       + std::to_string(map.getSelectedUnit().getMaxMovePoints()));
    break;
  }
  
  //Draw
  //Map
  window.setView(mapView);
  map.draw(window, 
           sf::Vector2f(mapView.getCenter().x - mapView.getSize().x / 2,
                        mapView.getCenter().y - mapView.getSize().y / 2), 
           zoomLevel);

  //GUI
  window.setView(guiView);
  //Yields widget
  yieldWidget.draw(window);
  /*window.draw(yieldWidgetBackground);
  window.draw(turnCounter);
  window.draw(moneyIcon);
  window.draw(moneyCounter);
  window.draw(foodIcon);
  window.draw(foodCounter);
  window.draw(woodIcon);
  window.draw(woodCounter);
  window.draw(stoneIcon);
  window.draw(stoneCounter);
  window.draw(weaponsIcon);
  window.draw(weaponsCounter);*/

  //Node widget
  if(nodeName.getText() != "")
  {
    if(nodeName.getText() == "Sea")
    {
      nodeImage.setImage(&seaTerrain);
    }
    else if(nodeName.getText() == "Tundra")
    {
      nodeImage.setImage(&tundraTerrain);
    }
    else if(nodeName.getText() == "Desert")
    {
      nodeImage.setImage(&desertTerrain);
    }
    else if(nodeName.getText() == "Grassland")
    {
      nodeImage.setImage(&grasslandTerrain);
    }
    else if(nodeName.getText() == "Tundra hills")
    {
      nodeImage.setImage(&tundraHillsTerrain);
    }
    else if(nodeName.getText() == "Desert hills")
    {
      nodeImage.setImage(&desertHillsTerrain);
    }
    else if(nodeName.getText() == "Grassland hills")
    {
      nodeImage.setImage(&grasslandHillsTerrain);
    }
    else if(nodeName.getText() == "Mountains")
    {
      nodeImage.setImage(&mountainsTerrain);
    }
    else if(nodeName.getText() == "Forest")
    {
      nodeImage.setImage(&forestTerrain);
    }
    else if(nodeName.getText() == "Rainforest")
    {
      nodeImage.setImage(&rainforestTerrain);
    }
    else if(nodeName.getText() == "Forest hills")
    {
      nodeImage.setImage(&forestHillsTerrain);
    }
    else if(nodeName.getText() == "Rainforest hills")
    {
      nodeImage.setImage(&rainforestHillsTerrain);
    }
    else if(nodeName.getText() == "Tundra river")
    {
      nodeImage.setImage(&tundraRiverTerrain);
    }
    else if(nodeName.getText() == "Desert river")
    {
      nodeImage.setImage(&desertRiverTerrain);
    }
    else if(nodeName.getText() == "Grassland river")
    {
      nodeImage.setImage(&grasslandRiverTerrain);
    }

    nodeImage.centerHorizontally();
    
    nodeWidget.draw(window);
  }

  //Building widget
  if(buildingName.getText() != "")
  {
    buildingWidget.draw(window);
  }
  
  //Unit widget
  if(unitName.getText() != "")
  {
    unitWidget.draw(window);
  }

  nextTurnButton.draw(window);

  if(mode == DisplayMode::pauseMenu)
  {
    window.draw(shade);
    window.draw(pauseMenuBackground); 
    window.draw(pauseMenuLabel); 
    menuButton.draw(window);
    optionsButton.draw(window);
    saveGameButton.draw(window);
    unpauseButton.draw(window);
    exitToDesktopButton.draw(window);
  }
  else if(mode == DisplayMode::game)
  {
    pauseButton.draw(window);
  }
  else if(mode == DisplayMode::saveMenu)
  {
    window.draw(shade);
    window.draw(saveMenuBackground);
    saveSelect.draw(window);
    backButton.draw(window);
    saveButton.draw(window);
    filenameInput.draw(window);
  }
}

void Game::regenerateMap(int width, int height, 
                         int landmassCount, int landmassSize,
                         double landToWaterChance, double waterToLandChance,
                         int mountainRangeMaxLenght, int mountainRangeCountP,
                         double firstPassHillChance, double secondPassHillChance,
                         double forestChance,
                         double riverChance)
{
  mapView = sf::View(sf::FloatRect(0, 0, Constant::windowWidth, Constant::windowHeight));
  map.regenerate(width, height, 
                 landmassCount, landmassSize,
                 landToWaterChance,  waterToLandChance,
                 mountainRangeMaxLenght,  mountainRangeCountP,
                 firstPassHillChance,  secondPassHillChance,
                 forestChance,
                 riverChance);
}

void Game::loadMapFromFile(std::string filename)
{
  mapView = sf::View(sf::FloatRect(0, 0, Constant::windowWidth, Constant::windowHeight));
  map.loadFromFile(filename);
}
