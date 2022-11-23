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

Game::Game(sf::Font& font, GameState& state)
  : backButton{ font, "back", sf::Vector2f(690, 790), 24 },
    saveButton{ font, "save", sf::Vector2f(1140, 790), 24 },
    saveSelect{ sf::Vector2f(690, 340), sf::Vector2f(550, 350), 50.0 },
    filenameInput{ font, "Enter save name", 24, sf::Vector2f(690, 270), InputType::text }
{
  //Next turn button setup
  nextTurnButton.setFont(font);
  nextTurnButton.setText("Next turn");
  nextTurnButton.setFlag(GUIFlag::clickable);
  nextTurnButton.setFunction([this](){
        this->map.nextTurn();
        this->turnCounter.setText("Turn " + std::to_string(this->map.getTurn() + 1));
        this->moneyCounter.setText(std::to_string(this->map.getFactions().at(0).getMoney()));
        this->foodCounter.setText(std::to_string(this->map.getFactions().at(0).getFood()));
        this->woodCounter.setText(std::to_string(this->map.getFactions().at(0).getWood()));
        this->stoneCounter.setText(std::to_string(this->map.getFactions().at(0).getStone()));
        this->weaponsCounter.setText(std::to_string(this->map.getFactions().at(0).getWeapons()));
      });
  nextTurnButton.positionAtBottom(100);
  nextTurnButton.positionAtRight(100);

  //Pause menu setup
  shade.load("texture/shade.png");

  pauseMenu.centerInMaster();

  pauseMenuLabel.setFont(font);
  pauseMenuLabel.setText("game paused");
  pauseMenuLabel.positionAtTop(25);
  pauseMenuLabel.centerHorizontally();

  menuButton.setFont(font);
  menuButton.setText("main menu");
  menuButton.setFlag(GUIFlag::clickable);
  menuButton.setFunction([&state, this](){
        state = GameState::mainMenu;
        this->mode = DisplayMode::game;
      });
  menuButton.positionDownTo(&pauseMenuLabel, 75);
  menuButton.centerHorizontally();

  optionsButton.setFont(font);
  optionsButton.setText("options");
  optionsButton.setFlag(GUIFlag::clickable);
  optionsButton.setFunction([&state](){
        state = GameState::options;
      });
  optionsButton.positionDownTo(&menuButton, 50);
  optionsButton.centerHorizontally();

  saveGameButton.setFont(font);
  saveGameButton.setText("save game");
  saveGameButton.setFlag(GUIFlag::clickable);
  saveGameButton.setFunction([this, &font](){
        this->mode = DisplayMode::saveMenu;
        
        //filename list is updated
        this->saveSelect.getButtons().clear();
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
      });
  saveGameButton.positionDownTo(&optionsButton, 50);
  saveGameButton.centerHorizontally();

  exitToDesktopButton.setFont(font);
  exitToDesktopButton.setText("exit to desktop");
  exitToDesktopButton.setFlag(GUIFlag::clickable);
  exitToDesktopButton.setFunction([&state](){
        state = GameState::exit;
      });
  exitToDesktopButton.positionDownTo(&saveGameButton, 50);
  exitToDesktopButton.centerHorizontally();

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

  pauseButtonSprite.load("texture/pause.png");
  pauseButtonSprite.setTextureRect(0, 0, 30, 30);
  moneyIconSprite.load("texture/iconmoney.png");
  foodIconSprite.load("texture/iconfood.png");
  woodIconSprite.load("texture/iconwood.png");
  stoneIconSprite.load("texture/iconstone.png");
  weaponsIconSprite.load("texture/iconweapons.png");

  pauseButton.setImage(&pauseButtonSprite);
  pauseButton.setFlag(GUIFlag::clickable);
  pauseButton.setFunction([this](){
        this->switchPause();
      });
  pauseButton.positionAtTop(10);
  pauseButton.positionAtLeft(10);

  turnCounter.setFont(font);
  turnCounter.setText("Turn 1");
  turnCounter.positionAtTop(14);
  turnCounter.positionRightTo(&pauseButton, 50);
 
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
}

void Game::mouseInput(sf::RenderWindow& window, sf::Vector2i clickPosition, sf::Font& font)
{
  pauseButton.clickInput(clickPosition);
  
  switch(mode)
  {
    case DisplayMode::game:
      nextTurnButton.clickInput(clickPosition);
        
      map.moveUnits(
        HexVector(map.getClickedNode(
          window.mapPixelToCoords(
            sf::Mouse::getPosition(window)),    
            sf::Vector2f((mapView.getCenter().x 
                          - mapView.getSize().x / 2), 
                         (mapView.getCenter().y 
                          - mapView.getSize().y / 2)),
                         mapView.getSize().x 
                         / Constant::windowWidth)));

      map.selectNodesAndUnits(
        window.mapPixelToCoords(sf::Mouse::getPosition(window)), 
                                sf::Vector2f((mapView.getCenter().x 
                                - mapView.getSize().x / 2), 
                                (mapView.getCenter().y 
                                - mapView.getSize().y / 2)),
                                mapView.getSize().x / Constant::windowWidth);

      nodeName.setText(map.getSelectedNodeName());
      nodeName.centerHorizontally();
        
      buildingName.setText(map.getSelectedBuilding()
                              .getName());
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
    break;

    case DisplayMode::pauseMenu:
      pauseMenu.clickInput(clickPosition);
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
    this->pauseButton.getImagePointer()
                      ->setTextureRect(0, 30, 30, 30);
  }
  else 
  {
    mode = DisplayMode::game;
    this->pauseButton.getImagePointer()
                      ->setTextureRect(0, 0, 30, 30);
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
    shade.draw(window);
    pauseMenu.draw(window);
  }
  else if(mode == DisplayMode::saveMenu)
  {
    shade.draw(window);
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
