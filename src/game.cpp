#include "game.h"
#include "map.h"
#include "textbutton.h"
#include "gamestate.h"
#include "gui.h"
#include <SFML/Graphics.hpp>

    #include <iostream>

Game::Game(sf::Font& font)
  : pauseMenuLabel{ "Game paused", font, 30 },
    menuButton{ font, "Main menu", sf::Vector2f(300, 350), 24 },
    optionsButton{ font, "Options", sf::Vector2f(300, 425), 24 },
    nodeNameLabel{ "", font, 20 }
{
  shadeTexture.loadFromFile("texture/shade.png");
  shade.setTexture(shadeTexture);

  pauseMenuBackground.setPosition(710, 250); 
  pauseMenuBackground.setFillColor(sf::Color::Black);
  pauseMenuBackground.setOutlineColor(sf::Color::White);
  pauseMenuBackground.setOutlineThickness(10);

  pauseMenuLabel.setPosition(0, 275);
  GUI::centerTextInField(pauseMenuLabel, pauseMenuBackground);
  GUI::centerTextInField(menuButton, pauseMenuBackground);
  GUI::centerTextInField(optionsButton, pauseMenuBackground);

  nodeWidgetBackground.setPosition(1520, 100); 
  nodeWidgetBackground.setFillColor(sf::Color::Black);
  nodeWidgetBackground.setOutlineColor(sf::Color::White);
  nodeWidgetBackground.setOutlineThickness(10);

  nodeNameLabel.setPosition(0, 125);
}

void Game::mouseInput(GameState& state, sf::RenderWindow& window, sf::Vector2i clickPosition)
{
  if(!paused)
  {
    map.switchNodeTerrain();
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
  double scrollSpeed{ 500.0 };

  double zoomLevel{ mapView.getSize().x / 800 };

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
  
  map.selectNodes(window.mapPixelToCoords(sf::Mouse::getPosition(window)), 
                  sf::Vector2f(mapView.getCenter().x - 400.0f, mapView.getCenter().y - 300.0f));
  nodeNameLabel.setString(map.getSelectedNodeName());
  GUI::centerTextInField(nodeNameLabel, nodeWidgetBackground);

  window.clear();
  
  window.setView(mapView);
  map.draw(window);

  window.setView(guiView);
  if(nodeNameLabel.getString() != "")
  {
    window.draw(nodeWidgetBackground);
    window.draw(nodeNameLabel);
  }
  if(paused)
  {
    window.draw(shade);
    window.draw(pauseMenuBackground); 
    window.draw(pauseMenuLabel); 
    menuButton.draw(window);
    optionsButton.draw(window);
  }
  window.display();
}

void Game::regenerateMap(int width, int height, int landmassCount, int landmassSize)
{
  map.regenerate(width, height, landmassCount, landmassSize);
}
