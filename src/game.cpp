#include "game.h"
#include "map.h"
#include "textbutton.h"
#include "imagebutton.h"
#include "gamestate.h"
#include "gui.h"
#include "constant.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <filesystem>
  
  #include <iostream>

Game::Game(sf::Font& font)
  : pauseMenuLabel{ "Game paused", font, 32 },
    menuButton{ font, "Main menu", sf::Vector2f(300, 375), 24 },
    optionsButton{ font, "Options", sf::Vector2f(300, 425), 24 },
    saveGameButton{ font, "Save game", sf::Vector2f(300, 475), 24 },
    exitToDesktopButton{ font, "Exit to desktop", sf::Vector2f(300, 800), 24 },
    pauseButton{ &pauseButtonSprite, sf::Vector2f(10, 10), sf::Vector2f(30, 32) },
    unpauseButton{ &unpauseButtonSprite, sf::Vector2f(10, 10), sf::Vector2f(30, 32) },
    nodeNameLabel{ "", font, 24 },
    unitNameLabel{ "", font, 24 },
    unitHealth{ "", font, 16 },
    unitMovePoints{ "", font, 16 },
    nextTurnButton{ font, "Next turn", sf::Vector2f(1550, 950), 32 },
    backButton{ font, "back", sf::Vector2f(690, 790), 24 },
    saveButton{ font, "save", sf::Vector2f(1140, 790), 24 },
    saveSelect{ sf::Vector2f(690, 340), sf::Vector2f(550, 350), 50.0 },
    filenameInput{ font, "Enter save name", 24, sf::Vector2f(690, 270), InputType::text }
{
  //Pause menu setup
  shadeTexture.loadFromFile("texture/shade.png");
  shade.setTexture(shadeTexture);
  pauseButtonTexture.loadFromFile("texture/pause.png");
  pauseButtonSprite.setTexture(pauseButtonTexture);
  unpauseButtonTexture.loadFromFile("texture/unpause.png");
  unpauseButtonSprite.setTexture(unpauseButtonTexture);

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
  nodeWidgetBackground.setPosition(1420, 100); 
  nodeWidgetBackground.setFillColor(sf::Color::Black);
  nodeWidgetBackground.setOutlineColor(sf::Color::White);
  nodeWidgetBackground.setOutlineThickness(10);
  seaTerrainTexture.loadFromFile("texture/terrainsea.png");
  tundraTerrainTexture.loadFromFile("texture/terraintundra.png");
  desertTerrainTexture.loadFromFile("texture/terraindesert.png");
  grasslandTerrainTexture.loadFromFile("texture/terraingrass.png");
  tundraHillsTerrainTexture.loadFromFile("texture/terraintundrahills.png");
  desertHillsTerrainTexture.loadFromFile("texture/terraindeserthills.png");
  grasslandHillsTerrainTexture.loadFromFile("texture/terraingrasshills.png");
  mountainsTerrainTexture.loadFromFile("texture/terrainmountains.png");
  forestTerrainTexture.loadFromFile("texture/terrainforest.png");
  rainforestTerrainTexture.loadFromFile("texture/terrainrainforest.png");
  forestHillsTerrainTexture.loadFromFile("texture/terrainforesthills.png");
  rainforestHillsTerrainTexture.loadFromFile("texture/terrainrainforesthills.png");
  tundraRiverTerrainTexture.loadFromFile("texture/terraintundrariver.png");
  desertRiverTerrainTexture.loadFromFile("texture/terraindesertriver.png");
  grasslandRiverTerrainTexture.loadFromFile("texture/terraingrassriver.png");
  seaTerrain.setTexture(seaTerrainTexture);
  tundraTerrain.setTexture(tundraTerrainTexture);
  desertTerrain.setTexture(desertTerrainTexture);
  grasslandTerrain.setTexture(grasslandTerrainTexture);
  tundraHillsTerrain.setTexture(tundraHillsTerrainTexture);
  desertHillsTerrain.setTexture(desertHillsTerrainTexture);
  grasslandHillsTerrain.setTexture(grasslandHillsTerrainTexture);
  mountainsTerrain.setTexture(mountainsTerrainTexture);
  forestTerrain.setTexture(forestTerrainTexture);
  rainforestTerrain.setTexture(rainforestTerrainTexture);
  forestHillsTerrain.setTexture(forestHillsTerrainTexture);
  rainforestHillsTerrain.setTexture(rainforestHillsTerrainTexture);
  tundraRiverTerrain.setTexture(tundraRiverTerrainTexture);
  desertRiverTerrain.setTexture(desertRiverTerrainTexture);
  grasslandRiverTerrain.setTexture(grasslandRiverTerrainTexture);
  seaTerrain.setPosition(1470, 200);
  tundraTerrain.setPosition(1470, 200);
  desertTerrain.setPosition(1470, 200);
  grasslandTerrain.setPosition(1470, 200);
  tundraHillsTerrain.setPosition(1470, 200);
  desertHillsTerrain.setPosition(1470, 200);
  grasslandHillsTerrain.setPosition(1470, 200);
  mountainsTerrain.setPosition(1470, 200);
  forestTerrain.setPosition(1470, 200);
  rainforestTerrain.setPosition(1470, 200);
  forestHillsTerrain.setPosition(1470, 200);
  rainforestHillsTerrain.setPosition(1470, 200);
  tundraRiverTerrain.setPosition(1470, 200);
  desertRiverTerrain.setPosition(1470, 200);
  grasslandRiverTerrain.setPosition(1470, 200);
  terrainTest.setPosition(1470, 200);

  nodeNameLabel.setPosition(0, 125);

  //Unit widget setup
  unitWidgetBackground.setPosition(100, 780);
  unitWidgetBackground.setFillColor(sf::Color::Black);
  unitWidgetBackground.setOutlineColor(sf::Color::White);
  unitWidgetBackground.setOutlineThickness(10);

  unitNameLabel.setPosition(325, 805);
  unitHealth.setPosition(350, 855);
  unitHealth.setFillColor(sf::Color::Green);
  unitMovePoints.setPosition(350, 885);
  unitMovePoints.setFillColor(sf::Color(44, 234, 221));

  riflemenLargeTexture.loadFromFile("texture/riflemen_large.png");
  riflemenLarge.setTexture(riflemenLargeTexture);
  riflemenLarge.setPosition(125, 805);

  //Save menu setup
  saveMenuBackground.setPosition(660, 240);
  saveMenuBackground.setFillColor(sf::Color::Black);
  saveMenuBackground.setOutlineColor(sf::Color::White);
  saveMenuBackground.setOutlineThickness(10);
}

void Game::mouseInput(GameState& state, sf::RenderWindow& window, sf::Vector2i clickPosition, sf::Font& font)
{
  switch(mode)
  {
    case DisplayMode::game:
      if(nextTurnButton.isClicked(clickPosition))
      {
        map.nextTurn();
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

        nodeNameLabel.setString(map.getSelectedNodeName());
        GUI::centerTextInField(nodeNameLabel, nodeWidgetBackground);
        unitNameLabel.setString(map.getSelectedUnit().getName());

        if(map.getSelectedUnit().getFaction() == 0)
        {
          unitNameLabel.setFillColor(sf::Color::Blue);
        }
        else
        {
          unitNameLabel.setFillColor(sf::Color::Red);
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
        int buttonCounter{ 0 };
        for(auto& file : std::filesystem::directory_iterator("saves/"))
        {
          std::string filename{ file.path().u8string() };
          filename.erase(filename.begin(),
                         filename.begin() + filename.find_first_of("/") + 1);
          filename.erase(filename.begin() + filename.find_last_of("."),
                         filename.end());
          saveSelect.addButton(font, filename,
                               sf::Vector2f(690, 340 + buttonCounter * 50.0f), 24);
          ++buttonCounter;
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
        //map is saved
        map.saveToFile("saves/" + filenameInput.getText() + ".json");

        mode = DisplayMode::pauseMenu;
        textInputUnclicked = true;
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

  double zoomLevel{ mapView.getSize().x / Constant::windowWidth };

  //Update
  switch(mode)
  {
    case DisplayMode::game:
  //if(!paused)
  //{
      if(mousePosition.x < 10)
      {
        mapView.move(-Constant::scrollSpeed * timeElapsed * zoomLevel, 0);
      }
      else if(mousePosition.x > Constant::windowWidth - 10)
      {
        mapView.move(Constant::scrollSpeed * timeElapsed * zoomLevel, 0);
      }
  
      if(mousePosition.y < 10)
      {
        mapView.move(0.0, -Constant::scrollSpeed * timeElapsed * zoomLevel);
      }
      else if(mousePosition.y > Constant::windowHeight - 10)
      {
        mapView.move(0.0, Constant::scrollSpeed * timeElapsed * zoomLevel);
      }
  //}
    case DisplayMode::pauseMenu:
    case DisplayMode::saveMenu:
      
  
  unitHealth.setString("Health: "
                     + std::to_string(map.getSelectedUnit().getHealth()) 
                     + "/" 
                     + std::to_string(map.getSelectedUnit().getMaxHealth()));
  unitMovePoints.setString("Move points: "
                         + std::to_string(map.getSelectedUnit().getMovePoints()) 
                         + "/" 
                         + std::to_string(map.getSelectedUnit().getMaxMovePoints()));
  break;
  }
  
  //Draw
  window.setView(mapView);
  map.draw(window, 
           sf::Vector2f(mapView.getCenter().x - mapView.getSize().x / 2,
                        mapView.getCenter().y - mapView.getSize().y / 2), 
           zoomLevel);

  window.setView(guiView);
  if(nodeNameLabel.getString() != "")
  {
    window.draw(nodeWidgetBackground);
    window.draw(nodeNameLabel);

    if(nodeNameLabel.getString() == "Sea")
    {
        window.draw(seaTerrain);
    }
    else if(nodeNameLabel.getString() == "Tundra")
    {
        window.draw(tundraTerrain);
    }
    else if(nodeNameLabel.getString() == "Desert")
    {
        window.draw(desertTerrain);
    }
    else if(nodeNameLabel.getString() == "Grassland")
    {
        window.draw(grasslandTerrain);
    }
    else if(nodeNameLabel.getString() == "Tundra hills")
    {
        window.draw(tundraHillsTerrain);
    }
    else if(nodeNameLabel.getString() == "Desert hills")
    {
        window.draw(desertHillsTerrain);
    }
    else if(nodeNameLabel.getString() == "Grassland hills")
    {
        window.draw(grasslandHillsTerrain);
    }
    else if(nodeNameLabel.getString() == "Mountains")
    {
        window.draw(mountainsTerrain);
    }
    else if(nodeNameLabel.getString() == "Forest")
    {
        window.draw(forestTerrain);
    }
    else if(nodeNameLabel.getString() == "Rainforest")
    {
        window.draw(rainforestTerrain);
    }
    else if(nodeNameLabel.getString() == "Forest hills")
    {
        window.draw(forestHillsTerrain);
    }
    else if(nodeNameLabel.getString() == "Rainforest hills")
    {
        window.draw(rainforestHillsTerrain);
    }
    else if(nodeNameLabel.getString() == "Tundra river")
    {
        window.draw(tundraRiverTerrain);
    }
    else if(nodeNameLabel.getString() == "Desert river")
    {
        window.draw(desertRiverTerrain);
    }
    else if(nodeNameLabel.getString() == "Grassland river")
    {
        window.draw(grasslandRiverTerrain);
    }
  }
  
  if(unitNameLabel.getString() != "")
  {
    window.draw(unitWidgetBackground);
    window.draw(unitNameLabel);
    window.draw(unitHealth);
    window.draw(unitMovePoints);

    if(unitNameLabel.getString() == "Riflemen")
    {
      window.draw(riflemenLarge);
    }
  }

  nextTurnButton.draw(window);

  //if(paused)
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
