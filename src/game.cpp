#include "game.h"
#include "map.h"
#include "textbutton.h"
#include "imagebutton.h"
#include "gamestate.h"
#include "gui.h"
#include <SFML/Graphics.hpp>

    #include <iostream>

Game::Game(sf::Font& font)
  : pauseMenuLabel{ "Game paused", font, 32 },
    menuButton{ font, "Main menu", sf::Vector2f(300, 375), 24 },
    optionsButton{ font, "Options", sf::Vector2f(300, 425), 24 },
    exitToDesktopButton{ font, "Exit to desktop", sf::Vector2f(300, 800), 24 },
    pauseButton{ &pauseButtonSprite, sf::Vector2f(10, 10), sf::Vector2f(30, 32) },
    unpauseButton{ &unpauseButtonSprite, sf::Vector2f(10, 10), sf::Vector2f(30, 32) },
    nodeNameLabel{ "", font, 24 },
    unitNameLabel{ "", font, 24 },
    unitHealth{ "", font, 16 },
    unitMovePoints{ "", font, 16 },
    nextTurnButton{ font, "Next turn", sf::Vector2f(1550, 950), 32 }
{
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
  GUI::centerTextInField(exitToDesktopButton, pauseMenuBackground);

  nodeWidgetBackground.setPosition(1420, 100); 
  nodeWidgetBackground.setFillColor(sf::Color::Black);
  nodeWidgetBackground.setOutlineColor(sf::Color::White);
  nodeWidgetBackground.setOutlineThickness(10);

  nodeNameLabel.setPosition(0, 125);

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

}

void Game::mouseInput(GameState& state, sf::RenderWindow& window, sf::Vector2i clickPosition)
{
  if(!paused)
  {
    if(nextTurnButton.isClicked(clickPosition))
    {
      map.nextTurn();
    }
    else if(pauseButton.isClicked(clickPosition))
    {
      paused = true;
    }
    else
    {
      sf::Vector2i posCartesian{ map.getClickedNode(window.mapPixelToCoords(sf::Mouse::getPosition(window)),    
                                                 sf::Vector2f((mapView.getCenter().x - mapView.getSize().x / 2), 
                                                              (mapView.getCenter().y - mapView.getSize().y / 2)),
                                                 mapView.getSize().x / 1920) };
      HexVector newPos{ posCartesian };
      map.moveUnits(newPos);

      map.selectNodesAndUnits(window.mapPixelToCoords(sf::Mouse::getPosition(window)), 
                              sf::Vector2f((mapView.getCenter().x - mapView.getSize().x / 2), 
                                           (mapView.getCenter().y - mapView.getSize().y / 2)),
                              mapView.getSize().x / 1920);
      nodeNameLabel.setString(map.getSelectedNodeName());
      GUI::centerTextInField(nodeNameLabel, nodeWidgetBackground);
      unitNameLabel.setString(map.getSelectedUnit().getName());
      /*unitHealth.setString("Health: "
                         + std::to_string(map.getSelectedUnit().getHealth()) 
                         + "/" 
                         + std::to_string(map.getSelectedUnit().getMaxHealth()));
      unitMovePoints.setString("Move points: "
                             + std::to_string(map.getSelectedUnit().getMovePoints()) 
                             + "/" 
                             + std::to_string(map.getSelectedUnit().getMaxMovePoints()));*/
    }
  }
  else
  {
    if(menuButton.isClicked(clickPosition))
    {
      state = GameState::mainMenu;
      paused = false;
    }
    else if(optionsButton.isClicked(clickPosition))
    {
      state = GameState::options;
    }
    else if(unpauseButton.isClicked(clickPosition))
    {
      paused = false;
    }
    else if(exitToDesktopButton.isClicked(clickPosition))
    {
      window.close();
    }
  }
}

void Game::scrollInput(double direction)
{
  if(direction > 0)
  {
    mapView.zoom(0.5);
  }
  else
  {
    mapView.zoom(2);
  }

}

void Game::switchPause()
{
  paused = !paused;
}

void Game::run(sf::RenderWindow& window, double timeElapsed)
{
  sf::Vector2i mousePosition{ sf::Mouse::getPosition(window) };
  double scrollSpeed{ 1000.0 };

  double zoomLevel{ mapView.getSize().x / 1920 };

  if(!paused)
  {
    if(mousePosition.x < 10)
    {
      mapView.move(-scrollSpeed * timeElapsed * zoomLevel, 0);
    }
    else if(mousePosition.x > 1910)
    {
      mapView.move(scrollSpeed * timeElapsed * zoomLevel, 0);
    }
  
    if(mousePosition.y < 10)
    {
      mapView.move(0.0, -scrollSpeed * timeElapsed * zoomLevel);
    }
    else if(mousePosition.y > 1070)
    {
      mapView.move(0.0, scrollSpeed * timeElapsed * zoomLevel);
    }
  }
      
  
  unitHealth.setString("Health: "
                     + std::to_string(map.getSelectedUnit().getHealth()) 
                     + "/" 
                     + std::to_string(map.getSelectedUnit().getMaxHealth()));
  unitMovePoints.setString("Move points: "
                         + std::to_string(map.getSelectedUnit().getMovePoints()) 
                         + "/" 
                         + std::to_string(map.getSelectedUnit().getMaxMovePoints()));
  
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

  if(paused)
  {
    window.draw(shade);
    window.draw(pauseMenuBackground); 
    window.draw(pauseMenuLabel); 
    menuButton.draw(window);
    optionsButton.draw(window);
    unpauseButton.draw(window);
    exitToDesktopButton.draw(window);
  }
  else
  {
    pauseButton.draw(window);
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
  mapView = sf::View(sf::FloatRect(0, 0, 1920, 1080));
  map.regenerate(width, height, 
                 landmassCount, landmassSize,
                 landToWaterChance,  waterToLandChance,
                 mountainRangeMaxLenght,  mountainRangeCountP,
                 firstPassHillChance,  secondPassHillChance,
                 forestChance,
                 riverChance);
}
