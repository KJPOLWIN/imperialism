#include "game.h"
#include "map.h"
#include "textbutton.h"
#include "imagebutton.h"
#include "gamestate.h"
#include "gui.h"
#include <SFML/Graphics.hpp>

    #include <iostream>

Game::Game(sf::Font& font)
  : pauseMenuLabel{ "Game paused", font, 30 },
    menuButton{ font, "Main menu", sf::Vector2f(300, 375), 24 },
    optionsButton{ font, "Options", sf::Vector2f(300, 425), 24 },
    exitToDesktopButton{ font, "Exit to desktop", sf::Vector2f(300, 800), 24 },
    pauseButton{ &pauseButtonSprite, sf::Vector2f(10, 10), sf::Vector2f(30, 30) },
    unpauseButton{ &unpauseButtonSprite, sf::Vector2f(10, 10), sf::Vector2f(30, 30) },
    nodeNameLabel{ "", font, 20 },
    unitNameLabel{ "", font, 20 }
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

  nodeWidgetBackground.setPosition(1520, 100); 
  nodeWidgetBackground.setFillColor(sf::Color::Black);
  nodeWidgetBackground.setOutlineColor(sf::Color::White);
  nodeWidgetBackground.setOutlineThickness(10);

  nodeNameLabel.setPosition(0, 125);

  unitWidgetBackground.setPosition(100, 780);
  unitWidgetBackground.setFillColor(sf::Color::Black);
  unitWidgetBackground.setOutlineColor(sf::Color::White);
  unitWidgetBackground.setOutlineThickness(10);

  unitNameLabel.setPosition(125, 805);
}

void Game::mouseInput(GameState& state, sf::RenderWindow& window, sf::Vector2i clickPosition)
{
  if(!paused)
  {
    sf::Vector2i posCartesian{ map.getClickedNode(window.mapPixelToCoords(sf::Mouse::getPosition(window)),    
                                              sf::Vector2f((mapView.getCenter().x - mapView.getSize().x / 2), 
                                                           (mapView.getCenter().y - mapView.getSize().y / 2)),
                                              mapView.getSize().x / 1920) };
    HexVector newPos{ posCartesian.x, posCartesian.y };
    map.moveUnits(newPos);
    

    map.selectNodesAndUnits(window.mapPixelToCoords(sf::Mouse::getPosition(window)), 
                            sf::Vector2f((mapView.getCenter().x - mapView.getSize().x / 2), 
                                         (mapView.getCenter().y - mapView.getSize().y / 2)),
                            mapView.getSize().x / 1920);
    nodeNameLabel.setString(map.getSelectedNodeName());
    GUI::centerTextInField(nodeNameLabel, nodeWidgetBackground);
    unitNameLabel.setString(map.getSelectedUnitName());
    //map.switchNodeTerrain();

    if(pauseButton.isClicked(clickPosition))
    {
      paused = true;
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

  //std::cout << zoomLevel << "\n";
  
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
  
  //map.selectNodesAndUnits(window.mapPixelToCoords(sf::Mouse::getPosition(window)), 
  //                        sf::Vector2f((mapView.getCenter().x - mapView.getSize().x / 2), 
  //                                     (mapView.getCenter().y - mapView.getSize().y / 2)),
  //                        mapView.getSize().x / 1920);
  //nodeNameLabel.setString(map.getSelectedNodeName());
  //GUI::centerTextInField(nodeNameLabel, nodeWidgetBackground);

  //unitNameLabel.setString(map.getSelectedUnitName());

  window.clear();
  
  window.setView(mapView);
  map.draw(window);

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
  }

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
  window.display();
}

void Game::regenerateMap(int width, int height, int landmassCount, int landmassSize)
{
  map.regenerate(width, height, landmassCount, landmassSize);
}
