#include "game.h"
#include "map.h"
#include "textbutton.h"
#include "gamestate.h"
#include <SFML/Graphics.hpp>

Game::Game(sf::Font& font)
  : pauseMenuLabel{ "Game paused", font, 20 },
    menuButton{ font, "Main menu", sf::Vector2f(300, 175), 20 }
{
  shadeTexture.loadFromFile("texture/shade.png");
  shade.setTexture(shadeTexture);

  pauseMenuBackground.setPosition(250, 100); 
  pauseMenuBackground.setFillColor(sf::Color::Black);
  pauseMenuBackground.setOutlineColor(sf::Color::White);
  pauseMenuBackground.setOutlineThickness(10);

  pauseMenuLabel.setPosition(300, 125);
}

void Game::mouseInput(GameState& state, sf::RenderWindow& window, sf::Vector2i clickPosition)
{
  if(!paused)
  {
    map.switchNodeTerrain();
  }

  if(paused && menuButton.isClicked(clickPosition))
  {
    state = GameState::mainMenu;
    paused = false;
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
  
  if(!paused)
  {
    if(mousePosition.x < 10)
    {
      mapView.move(-scrollSpeed * timeElapsed, 0);
    }
    else if(mousePosition.x > 790)
    {
      mapView.move(scrollSpeed * timeElapsed, 0);
    }
  
    if(mousePosition.y < 10)
    {
      mapView.move(0.0, -scrollSpeed * timeElapsed);
    }
    else if(mousePosition.y > 590)
    {
      mapView.move(0.0, scrollSpeed * timeElapsed);
    }
  }
  
  map.selectNodes(window.mapPixelToCoords(sf::Mouse::getPosition(window)), 
                  sf::Vector2f(mapView.getCenter().x - 400.0f, mapView.getCenter().y - 300.0f));
  
  window.clear();
  
  window.setView(mapView);
  map.draw(window);
  
  window.setView(guiView);
  if(paused)
  {
    window.draw(shade);
    window.draw(pauseMenuBackground); 
    window.draw(pauseMenuLabel); 
    menuButton.draw(window); 
  }
  window.display();
}

void Game::regenerateMap(int width, int height, int landmassCount, int landmassSize)
{
  map.regenerate(width, height, landmassCount, landmassSize);
}
